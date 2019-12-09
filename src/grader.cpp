/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/grader.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <iterator>

namespace GraderApplication
{
   Grader::Grader(int _numberOfStudents, const std::string &_dataFile)
      : numberOfStudents(_numberOfStudents)
        , dataFile(_dataFile)
   {
      studentContainer.reserve(numberOfStudents);    
   }


   int Grader::getNumOfStudents(void) const { return this->numberOfStudents; }


   std::string Grader::getDataFile() const { return this->dataFile; }


   void Grader::loadVector(void)
   {
      std::string file = this->getDataFile();
      std::streampos currpos = this->getCurrentFilePosition();
      int lineCount = this->getFileLineCount();

      for ( int i = 0; i < this->getNumOfStudents(); ++i ) {
         StudentData student;
         student.loadStudentFile(file, currpos, (lineCount + i));
         // Update currpos before student goes out of scope and is destoyed
         currpos = student.getCurrentFilePosition();               

         studentContainer.emplace_back(student);
      }
   }


   void Grader::showStudentVector(void) 
   {
      std::cout << "\nStudent Data Before Processing\n";
      for ( auto &itr: studentContainer)
      {
         itr.printStudentObject();
      }
   }


   void Grader::makeGrades(void)
   {
      for ( int i = 0; i < this->getNumOfStudents(); ++i ) {  
         /* create temp vector to hold only the grades
          * so we can work with them easier, use reserve
          * and emplace_back for speed.
          * */
         std::vector<float> tempGradeContainer;
         tempGradeContainer.reserve(this->getDataLength());
         float tempValue = 0.0;
         for ( int j = 0; j < this->getDataLength(); ++j ) {
            /* first calculate singular grades (mark * weight) / maxmark
             * and store one at a time into vector
             * */
            tempValue = this->subGradeComputation(i, j);
            tempGradeContainer.emplace_back(tempValue);
         }
         /* add all subgrades together for our final grade */
         float finalGrade = this->vecSummation(tempGradeContainer);
         /* use precision stream to round to hundreths place after summation
          * to retain as much accuracy as possible
          * */
         std::cout << std::fixed << std::setprecision(2);
         /* Use our wonderful getters and setters */
         studentContainer[i].setFinalGrade(finalGrade);
         std::string letter = assignLetterGrade(finalGrade);
         studentContainer[i].setLetterGrade(letter);
      }
   }


   float Grader::subGradeComputation(int i, int j)
   {
      return ( studentContainer[i].getGrades(j) 
            * this->getWeightContainer(j) ) / this->getMaxMarkContainer(j);
   }


   std::string Grader::assignLetterGrade(float grade)
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
      return "Grade went wrong";
   }


   void Grader::outputFinal(void)
   {
      /* use setw and left, right for nice tabular aligned output
       * of data
       * */
      for (StudentVector::iterator i = studentContainer.begin();
            i != studentContainer.end(); ++i) {
         /* Print out only the computations where no errors were thrown */
         if (!(i->getIsError())) {
            std::cout << std::setw(15) << std::left << i->getName()
               << std::setw(10) << std::left << i->getFinalGrade()
               << std::setw(5)  << std::left << i->getLetterGrade()
               << std::endl;
         }
      }
   }


   void Grader::sanitize(void) const { std::system(SANITIZE); }
};
