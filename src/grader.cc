#include <chrono>
#include <iomanip>
#include "../hdr/argparser.hpp"
#include "../hdr/grader.hpp"



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

    if (numargsfilled == 1)
    {
        EvaluationData eval(inputFile);
        eval.loadEvaluationData();
        int numStudents = countStudentLines(eval);

        Container container(numStudents);
        loadStudentContainers(eval, container);
        makeGrades(eval, container);


        outputFinal(container);


        //outputWDR(container);
        //outputError(container);


        sanitize();

        //auto end = std::chrono::system_clock::now();
        //std::chrono::duration<double> elapsed_seconds = end-start;
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        //std::cout << std::ctime(&end_time);

    }
    else if (numargsfilled == 2)
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "File: " << inputFile << std::endl;
    }
    else
    {
        std::cout << "numargsfilled: " << numargsfilled << std::endl;
        std::cerr << "Something happened" << std::endl;
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


/* NOTE: Documentation
 * the meat of this class, 2 C style for loops.
 * depends on a few helper functions
 * to properly perform computations on the grade data
 * */
void makeGrades(EvaluationData &e, Container &c)
{
    for ( int i = 0; i < c.numStudents; i++ )
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


/* NOTE: Documentation
 * Helper method of makeGrades, takes in standard i, j
 * C style for loop iterators, so it can calculate all grades
 * for each student, against the weight and maxmark
 *
 * Takes EvaluationData object and Container obj for access
 * to needed data
 *
 * Called from within makeGrades inner for loop since it needs
 * to calculate an array being stored in a vector
 * */
float subGradeComputation(EvaluationData &e, Container &c, int i, int j)
{
    return (( c.student[i].studentGradesContainer(j)
              * e.evaluationWeightContainer(j) ) / e.evaluationMaxMarkContainer(j));
}


/* NOTE: Documentation
 * makes a call to macro routines in settings.h
 * to decide the range of the grade to match it to
 * a lettergrade representation held in the Echelon
 * struct also defined in settings.h
 *
 * called from makeGrades outer forloop
 * */
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
    return "Grade went wrong";
}


void outputFinal(Container &c)
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


void outputWDR(Container &c)
{
    for (c.i = c.error.begin(); c.i != c.error.end(); c.i++ )
    {
        if (c.i->studentWDR())
        {
            std::cout << c.i->studentName() << std::left << std::setw(5)
                      << c.i->studentLetterGrade() << std::endl;
        }
    }
}


void outputError(Container &c)
{
    for (c.i = c.error.begin(); c.i != c.error.end(); c.i++ )
    {
        if (c.i->studentError())
        {
            std::cerr << "\n\nOffending line: " << c.i->lineCount()
                      << "\nOffending content: " << c.i->currentLineContent()
                      << "\nError message: " << c.i->errorDefinition()
                      << std::endl;
        }
    }
}


void sanitize(void) { std::system(SANITIZE); }
