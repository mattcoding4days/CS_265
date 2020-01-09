#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>
#include "evaluation.hpp"
#include "utillity.hpp"


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
         float labScore;
         float assignScore;
         float midtermScore;
         float finalScore;
         float totalGrade;
         std::string letterGrade;
         bool isWDR;
         bool isError;
         std::string errorDef;
         int mlineCount;

      public:


         /* NOTE: Documentation
          * Default Constuctor
          * */
         StudentData(void);


         /* NOTE: Documentation
          * Default Deconstructor
          * */
         ~StudentData(void);


         /* NOTE: Documentation
          * Copy Constructor 
          * */
         StudentData(const StudentData &);


         /* NOTE: Documentation
          * Copy assignment
          * */
         StudentData& operator=(const StudentData &);

         
         /*
            Note: Documentation
            Move Constructor
            use noexcept for compiler optimizations
         */
         StudentData(StudentData &&) noexcept;


         /*
            Note: Documentation
            Overload the move assignment
            use noexcept for compiler optimizations
         */
         StudentData& operator=(StudentData&& ) noexcept;


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
         std::string studentName(void) const;
         void setStudentName(std::string &);


         /* NOTE: Documentation
          * getters and setters for grades container
          * */
         float studentGradesContainer(int &);
         void setStudentGradesContainer(std::string &, EvaluationData &);


         /* NOTE: Documentation
          * getters and setters for the container
          * that will hold the resulting grades after
          * calculation (mark * weight) / max mark
          * */
         float calculatedGrades(int);
         void setCalculatedGrades(std::vector<float> &);


         /* NOTE: Documentation
          * getters and setters for length of student
          * data, wich also takes the length from
          * the evaluation data for comparison
          * purposes
          * */
         int studentDataLength(void) const;
         void setStudentDataLength(int, int);


         /* NOTE: Documentation
          * Accessor methods for
          * the students accumulated
          * total lab scores
          * */
         float studentLabScore(void) const;
         void setStudentLabScore(float score);


         /* NOTE: Documentation
          * Accessor methods for
          * the students accumulated
          * assignment scores
          * */
         float studentAssignScore(void) const;
         void setStudentAssignScore(float score);


         /* NOTE: Documentation
          * Accessor methods for
          * the students accumulated
          * midterm scores
          * */
         float studentMidtermScore(void) const;
         void setStudentMidtermScore(float score);


         /* NOTE: Documentation
          * Accessor methods for
          * the students accumulated
          * final (test) score this should
          * only be one
          * */
         float studentFinalScore(void) const;
         void setStudentFinalScore(float score);


         /* NOTE: Documentation
          * getter and setter for the final grade
          * and all subsequent category marks
          * */
         float studentTotalGrade(void) const;
         void setStudentTotalGrade(const float );


         /* NOTE: Documentation
          * getters and setters for the Letter
          * grader obtained by the student
          * */
         std::string studentLetterGrade(void) const;
         void setStudentLetterGrade(const std::string &);


         /* NOTE: Documentation
          * getters and setters to
          * set error flag
          * */
         bool studentWDR(void) const;
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
         bool studentError(void) const;
         void setStudentError(bool);


         /* NOTE: Documentation
          * Store the error definition
          * from out custom exceptions 
          * */
         std::string errorDefinition(void) const;
         void setErrorDefinition(const std::string &);


         /* NOTE: Documentation
          * Update line count from evaluation
          * object
          * */
         int lineCount(void) const;
         void setLineCount(int _count);


         /* NOTE: Documentation
          * Main method for Student Class, it uses the
          * file position set from BaseHeader class, 
          * to skip right to where the students section is.
          *
          * The method its self is very similar to how loadBaseData
          * works in the BaseHeader Class
          * */
         bool loadStudents(EvaluationData &);

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
