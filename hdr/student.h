#ifndef STUDENT_H
#define STUDENT_H

#include "utillity.h"
#include <vector>

namespace GraderApplication
{
   /* XXX: Documentation
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
         int studentDataLength;
         float totalGrade;
         std::string letterGrade;
         bool isWDR;
         bool isError;
         std::string errorDefinition;

      public:
         /* XXX: Documentation
          * Default Constuctor
          * */
         StudentData(void);

         /* XXX: Documentation
          * Error preserve will be called whenever something
          * fails for any StudentData evaluations.
          * Instead of printing out and closing the program,
          * we will simply preserve all relevent errors for
          * the particular student line, to be printed out
          * when the program finishes running
          */
         void errorPreserve(std::string &);

         /* XXX: Documentation
          * getters and setters for name
          * */
         std::string getName() const;
         void setName(std::string &);

         /* XXX: Documentation
          * getters and setters for length of student
          * data, wich also takes the length from 
          * the evaluation data for comparison
          * purposes
          * */
         int getStudentDataLen() const;
         void setStudentDataLen(int, int);

         /* XXX: Documentation
          * getters and setters for grades container
          * */
         float getGrades(int &);
         void setGrades(std::string &, std::vector<float> &);

         /* XXX: Documentation
          * getters and setters for the container
          * that will hold the resulting grades after
          * calculation (mark * weight) / max mark
          * */
         float getCalculatedGrades(int &);
         void setCalculatedGrades(std::vector<float> &);

         /* XXX: Documentation
          * getter and setter for the final grade
          * and all subsequent category marks
          * */
         float getTotalGrade() const;
         void setTotalGrade(const float );

         /* XXX: Documentation
          * getters and setters for the Letter
          * grader obtained by the student
          * */
         std::string getLetterGrade() const;
         void setLetterGrade(const std::string &);

         /* XXX: Documentation
          * getters and setters to switch 
          * WDR to true
          * */
         bool getIsStudentWDR() const;
         void setIsStudentWDR(bool);

         /* XXX: Documentation
          * getters and setters to record
          * whether something went wrong with
          * parsing a certain student.
          * This flag will be set to true if
          * any reading errorsa occur, and will be
          * used went computing the final grades and 
          * printing to stdout
          * */
         bool getIsError() const;
         void setIsError(bool);

         /* XXX: Documentation
          * Store the error definition
          * from out custom exceptions 
          * */
         std::string getErrorDefinition(void) const;
         void setErrorDefinition(const std::string &);

         /* XXX: Documentation
          * Main method for Student Class, it uses the
          * file position set from BaseHeader class, 
          * to skip right to where the students section is.
          *
          * The method its self is very similar to how loadBaseData
          * works in the BaseHeader Class
          * */
         bool loadStudentFile(const std::string &, const std::streampos &,
               int, int, std::vector<float> &);

         /* XXX: Documentation
          * Helper method for loadDataFile, checks if student is found
          * in temp file by string comparison, returns true or false
          * */
         bool isStudentProcessed(const std::string &);

         /* XXX: Documentation
          * first test for tempfile existence, if it doesnt we havnt
          * read the file at all yet
          * */
         bool testForFileExistence(const std::string &);

         /* XXX: Documentation
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
