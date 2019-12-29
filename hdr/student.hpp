#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "utillity.hpp"
#include <vector>

namespace GraderApplication
{
   /* NOTE: Documentation
    * For every occurance of a valid student line
    * in the given file a student object will be created
    * and stored in a corresponding vector of the same type
    * defined and handled from the grader class. 
    * */ 
   class StudentData : public Utillity
   {
      private:
         std::string name;
         std::vector <float> gradesContainer;
         std::vector <float> calculatedGradesContainer;
         int studentDataLen;
         float totalGrade;
         std::string letterGrade;
         bool isWDR;
         bool isError;
         std::string errorDef;

      public:

         /* NOTE: Documentation
          * Default Constuctor
          * */
         StudentData(void);

         /* NOTE: Documentation
          * Error preserve will be called whenever something
          * fails for any StudentData evaluations.
          * Instead of printing out and closing the program,
          * we will simply preserve all relevent errors for
          * the particular student line, to be printed out
          * when the program finishes running
          */
         void errorPreserve(std::string &);

         /* NOTE: Documentation
          * getters and setters for name
          * */
         std::string studentName() const;
         void setStudentName(std::string &);

         /* NOTE: Documentation
          * getters and setters for length of student
          * data, wich also takes the length from 
          * the evaluation data for comparison
          * purposes
          * */
         int studentDataLength() const;
         void setStudentDataLength(int, int);

         /* NOTE: Documentation
          * getters and setters for grades container
          * */
         float studentGrades(int &);
         void setStudentGrades(std::string &, std::vector<float> &);

         /* NOTE: Documentation
          * getters and setters for the container
          * that will hold the resulting grades after
          * calculation (mark * weight) / max mark
          * */
         float calculatedGrades(int &);
         void setCalculatedGrades(std::vector<float> &);

         /* NOTE: Documentation
          * getter and setter for the final grade
          * and all subsequent category marks
          * */
         float studentTotalGrade() const;
         void setStudentTotalGrade(const float );

         /* NOTE: Documentation
          * getters and setters for the Letter
          * grader obtained by the student
          * */
         std::string studentLetterGrade() const;
         void setStudentLetterGrade(const std::string &);

         /* NOTE: Documentation
          * getters and setters to switch 
          * WDR to true
          * */
         bool studentWDR() const;
         void setStudentWDR(bool);

         /* NOTE: Documentation
          * getters and setters to record
          * whether something went wrong with
          * parsing a certain student.
          * This flag will be set to true if
          * any reading errorsa occur, and will be
          * used went computing the final grades and 
          * printing to stdout
          * */
         bool studentError() const;
         void setStudentError(bool);

         /* NOTE: Documentation
          * Store the error definition
          * from out custom exceptions 
          * */
         std::string errorDefinition(void) const;
         void setErrorDefinition(const std::string &);

         /* NOTE: Documentation
          * Main method for Student Class, it uses the
          * file position set from BaseHeader class, 
          * to skip right to where the students section is.
          *
          * The method its self is very similar to how loadBaseData
          * works in the BaseHeader Class
          * */
         bool loadStudentFile(const std::string &, const std::streampos &,
               int, int, std::vector<float> &);

         /* NOTE: Documentation
          * Helper method for loadDataFile, checks if student is found
          * in temp file by string comparison, returns true or false
          * */
         bool isStudentProcessed(const std::string &);

         /* NOTE: Documentation
          * first test for tempfile existence, if it doesnt we havnt
          * read the file at all yet
          * */
         bool testForFileExistence(const std::string &);

         /* NOTE: Documentation
          * after a student is read in to the studentvector, this
          * method writes said processed student to the temp file
          * then closes it, if the file doesnt exist yet it creates it.
          * it is careful to append students, and not trample previously
          * written data.
          * */
         void processStudent(const std::string &);
   };
};
#endif
