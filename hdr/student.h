#ifndef STUDENT_H
#define STUDENT_H

#include "base.h"
#include "settings.h"
#include <vector>

namespace GraderApplication {
   /* For every occurance of a valid student line
    * in the given file a student object will be created
    * and stored in a corresponding vector of the same type
    * defined and handled from the grader class. 
    *
    * This class is equiped with the proper getters and setters
    * so all private data can easily be accessed and manipulated
    * from inheriting classes.
    * */ 
   class StudentData : public BaseData {
      private:
         std::string name;
         std::vector <float> gradesContainer;
         float finalGrade;
         std::string letterGrade;

      public:
         /* XXX: Documentation
          * default constructor
          * */
         StudentData(void);

         /* XXX: Documentation
          * getters and setters for name
          * TODO: rename to studentId
          * */
         std::string getName() const;
         void setName(const std::string &);

         /* XXX: Documentation
          * getters and setters for grades container
          * */
         float getGrades(int &);
         void setGrades(const int &, const float&);

         /* XXX: Documentation
          * getter and setter for the final grade
          * obtained by the student
          * */
         float getFinalGrade() const;
         void setFinalGrade(const float &);

         /* XXX: Documentation
          * getters and setters for the Letter
          * grader obtained by the student
          * */
         std::string getLetterGrade() const;
         void setLetterGrade(const std::string &);

         /* XXX: Documentation
          * A debug and testing method, prints a
          * raw student object, meant to be used by
          * a ranged for loop
          * */
         void printStudentObject();

         /* XXX: Documentation
          * Deletes the temp.txt file created
          * after all data is read in, currently
          * uses std::system to spawn a new shell
          * and run the rm command. Quick way for now
          * TODO: Learn how to delete files using only C++
          * */
         void sanitize(void) const;

         /* XXX: Documentation
          * Main load method, does the majority of the
          * simple parsing, checks only the first character
          * of each line, will disregaurd, whitespace, comments
          * and uppercase characters, since this method is only
          * concerned with grabbing students. the basedata, countstudents,
          * methods are based off this one.
          *
          * Since this file loads onlu ONE line at a time, every time it is
          * reopened from a for loop, the reading begins at the beginning of the file
          * every time, I solved this issue by creating a temp file, and saving the 
          * previous student read in to the studentvector, if the student is found in 
          * temp.text, we dont read it in and skip to the next.
          * This method depends on a few helper functions to help in that task
          * */
         bool loadDataFile(const std::string &);

         /* XXX: Documentation
          * Helper method for loadDataFile, checks if student is found
          * in temp file by string comparison, returns true or false
          * */
         bool isStudentProcessed(const std::string &);


         /* XXX: Documentation
          * first test for tempfile existance, if it doesnt we havnt
          * read the file at all yet
          * */
         bool testForFileExistance(const std::string &);

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
