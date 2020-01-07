#include <chrono>
#include <iomanip>
#include "../hdr/argparser.hpp"
#include "../hdr/grader.hpp"


/* Define container explicit constructor */
Container::Container(int _x) : numStudents(_x)
{
   student.reserve(numStudents);
   error.reserve(1);
   wdr.reserve(1);
}


/* NOTE: Documentation
 * Initialize main routine,
 * */
int main(int argc, char **argv)
{
   //auto start = std::chrono::system_clock::now();

   std::string inputFile("");
   std::string name("");
   ArgParse parser("-s");
   int numargsfilled = parser.parseArguments(argc, argv, inputFile, name);

   if (numargsfilled > 0)
   {
      EvaluationData eval(inputFile);
      eval.loadEvaluationData();
      int numStudents = countStudentLines(eval);
      Container container(numStudents);

      loadStudentContainers(eval, container);
      makeGrades(eval, container);

      if (numargsfilled == 1)
      {
         if (container.student.size() > 0) { outputStudent(container); }

         if (container.wdr.size() > 0) { outputWDR(container); }

         if (container.error.size() > 0) { outputError(container); }


         //auto end = std::chrono::system_clock::now();
         //std::chrono::duration<double> elapsed_seconds = end-start;
         //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
         //std::cout << std::ctime(&end_time);

         /* clean up the temp file  */
         sanitize();
      }
      /* Both arguments were filled */
      else if (numargsfilled == 2)
      {
         StudentData stu = searchStudent(container, name);
         outputStudent(stu);

         /* clean up the temp file  */
         sanitize();
      }
   }
   else
   {
      std::cerr << "Error parsing arguments" << std::endl;
      sanitize();
      exit (EXIT_FAILURE);
   }

   exit(EXIT_SUCCESS);
}


int countStudentLines(EvaluationData &e)
{
   std::streampos jump;
   jump = e.currentFilePosition();

   std::ifstream inFile(e.evaluationFile());
   inFile.seekg(jump);
   int numberOfLines = 0;
   std::string dummyLine("");

   if ( inFile.good() )
   {
      while ( std::getline( inFile, dummyLine ))
      {
         if (! ( dummyLine.empty()) ) { ++numberOfLines; }
      }
   }

   inFile.close();
   return numberOfLines;
}


void loadStudentContainers(EvaluationData &e, Container &c)
{
   for (int i = 0; i < c.numStudents; i++)
   {
      StudentData stu;
      stu.loadStudents(e);

      if (stu.studentError())
      {
         c.error.emplace_back(stu);
      }
      else if (stu.studentWDR())
      {
         stu.setStudentLetterGrade("WITHDRAWN");
         c.wdr.emplace_back(stu);
      }
      else
      {
         c.student.emplace_back(stu);
      }
   }
}


/* TODO: This function needs refactoring, there are better ways to acheive this
 * */
StudentData searchStudent(Container &c, const std::string &name)
{
   /* Check each container for the student name */
   bool found = false;
   for (int i = 0; i < c.numStudents; i++) {
      if (c.student.size() > 0 && c.student[i].studentName() == name)
      {
         return c.student[i];
      }

      else if (c.wdr.size() > 0 && c.wdr[i].studentName() == name)
      {
         return c.wdr[i];
      }

      else if (c.error.size() > 0 && c.error[i].studentName() == name)
      {
         return c.error[i];
      }
   }


   try
   {
      if (! (found) )
      {
         sanitize();
         throw StudentNotFound();
      }
   }
   catch (StudentNotFound &e)
   {
      std::cout << e.what() << name << std::endl;
      exit(EXIT_FAILURE);
   }
   /* Return the first student just to keep the compiler from
    * complaining, albeit should not actually ever reach here
    * because will have thrown and exited program if student is not
    * found
    * */
   return c.student[0];
}


void makeGrades(EvaluationData &e, Container &c)
{
   int stuSize = c.student.size();
   for ( int i = 0; i < stuSize; i++ )
   {
      // create temp vector
      std::vector<float> tempGradeContainer;
      tempGradeContainer.reserve(e.evaluationDataLength());

      float tempValue = 0;
      for ( int j = 0; j < e.evaluationDataLength(); j++ )
      {
         // first calculate single grades (mark * weight) / maxmark
         tempValue = subGradeComputation(e, c, i, j);
         tempGradeContainer.emplace_back(tempValue);

      }

      /* Accumulate category grades */
      for ( int k = 0; k < e.evaluationDataLength(); k++ )
      {
         float t = 0;
         if ( e.evaluationCategoryContainer(k) == "Lab" )
         {
            t = tempGradeContainer[k];
            c.student[i].setStudentLabScore(t);
         }
         else if (e.evaluationCategoryContainer(k) == "Assign")
         {
            t = tempGradeContainer[k];
            c.student[i].setStudentAssignScore(t);
         }
         else if (e.evaluationCategoryContainer(k) == "Midterm")
         {
            t = tempGradeContainer[k];
            c.student[i].setStudentMidtermScore(t);
        }
         else if (e.evaluationCategoryContainer(k) == "Final")
         {
            t = tempGradeContainer[k];
            c.student[i].setStudentFinalScore(t);
         }
      }

      c.student[i].setCalculatedGrades(tempGradeContainer);

      /* Add all subgrades together for final grade */
      float finalGrade = e.vecSummation(tempGradeContainer);

      /* Use a precision stream to round grades to hundreths place */
      std::cout << std::fixed << std::setprecision(2);

      c.student[i].setStudentTotalGrade(finalGrade);
      std::string letter = assignLetterGrade(finalGrade);
      c.student[i].setStudentLetterGrade(letter);

   }
}


float subGradeComputation(EvaluationData &e, Container &c, int i, int j)
{
   return (( c.student[i].studentGradesContainer(j)
            * e.evaluationWeightContainer(j) ) / e.evaluationMaxMarkContainer(j));
}


std::string assignLetterGrade(float grade)
{
   /* Call to settings.h for definitions, macro routines and
    * struct working together to assign grade
    * */
   Echelon echelon;
   if      ( IS_A_PLUS(grade)  )  { return echelon.high_A; }
   else if ( IS_A(grade)       )  { return echelon.mid_A;  }
   else if ( IS_A_MINUS(grade) )  { return echelon.low_A;  }
   else if ( IS_B_PLUS(grade)  )  { return echelon.high_B; }
   else if ( IS_B(grade)       )  { return echelon.mid_B;  }
   else if ( IS_B_MINUS(grade) )  { return echelon.low_B;  }
   else if ( IS_C_PLUS(grade)  )  { return echelon.high_C; }
   else if ( IS_C(grade)       )  { return echelon.mid_C;  }
   else if ( IS_C_MINUS(grade) )  { return echelon.low_C;  }
   else if ( IS_D(grade)       )  { return echelon.D;      }
   else if ( IS_F(grade)       )  { return echelon.F;      }

   // Enter debug state if we return this
   else { return "Grade went wrong"; }
}


void outputStudent(Container &c)
{
   std::cout << std::left << std::setw(10) << "Name"
      << std::left << std::setw(10) << "Lab"
      << std::left << std::setw(10) << "Assign"
      << std::left << std::setw(10) << "Midterm"
      << std::left << std::setw(10) << "Final"
      << std::left << std::setw(10) << "Total"
      << std::left << std::setw(10) << "Letter"
      << std::endl;


   for (c.i = c.student.begin(); c.i != c.student.end(); c.i++ )
   {
      std::cout << std::left << std::setw(10) << c.i->studentName()
         << std::left << std::setw(10) << c.i->studentLabScore()
         << std::left << std::setw(10) << c.i->studentAssignScore()
         << std::left << std::setw(10) << c.i->studentMidtermScore()
         << std::left << std::setw(10) << c.i->studentFinalScore()
         << std::left << std::setw(10) << c.i->studentTotalGrade()
         << std::left << std::setw(10) << c.i->studentLetterGrade()
         << std::endl;
   }
}


void outputStudent(StudentData &s)
{
   if (s.studentError())
   {
      std::cerr << "\n\nOffending line: " << s.lineCount()
         << "\nOffending content: " << s.currentLineContent()
         << "\nError message: " << s.errorDefinition()
         << std::endl;
   }

   else
   {
      std::cout << std::left << std::setw(10) << "Name"
         << std::left << std::setw(10) << "Lab"
         << std::left << std::setw(10) << "Assign"
         << std::left << std::setw(10) << "Midterm"
         << std::left << std::setw(10) << "Final"
         << std::left << std::setw(10) << "Total"
         << std::left << std::setw(10) << "Letter"
         << std::endl;

      if (s.studentWDR())
      {
         std::cout << std::left << std::setw(10) << s.studentName()
            << s.studentLetterGrade()
            << std::endl;
      }

      else
      {
         std::cout << std::left << std::setw(10) << s.studentName()
            << std::left << std::setw(10) << s.studentLabScore()
            << std::left << std::setw(10) << s.studentAssignScore()
            << std::left << std::setw(10) << s.studentMidtermScore()
            << std::left << std::setw(10) << s.studentFinalScore()
            << std::left << std::setw(10) << s.studentTotalGrade()
            << std::left << std::setw(10) << s.studentLetterGrade()
            << std::endl;
      }
   }
}


void outputWDR(Container &c)
{
   for (c.i = c.wdr.begin(); c.i != c.wdr.end(); c.i++ )
   {
      std::cout << std::left << std::setw(10) << c.i->studentName()
         << c.i->studentLetterGrade()
         << std::endl;
   }
}


void outputError(Container &c)
{
   for (c.i = c.error.begin(); c.i != c.error.end(); c.i++ )
   {
      Colors color;
      std::cerr << color.BRed << "\nError message: " << color.Reset
         << color.BWhite << c.i->errorDefinition() << color.Reset 
         << color.BYellow << "\nOffending line: " << color.Reset 
         << color.BWhite << c.i->lineCount() << color.Reset
         << color.BYellow << "\nOffending content: " << color.Reset 
         << color.BWhite << c.i->currentLineContent() << color.Reset
         << std::endl;
   }
}


void sanitize(void) { std::system(SANITIZE); }
