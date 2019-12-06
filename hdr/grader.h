#ifndef GRADER_H
#define GRADER_H

#include "student.h"
#include <vector>

namespace GraderApplication {
   /* Change template mess, for readabillity */
   using StudentVector = std::vector<StudentData>;

   /* Grader will inherit from both main classes, 
    * utilizing the getters and setters to access, 
    * and manipulate the data to make my life easier.
    *
    * Utilizes the vector of objects approach rather
    * then a map or 2d array
    * */
   class Grader : public StudentData {
      private:
         int numberOfStudents;
         std::string dataFile;
         StudentVector studentContainer;
      public:
         /* XXX: Documentation
          * explicit constructor takes in number of students
          * found in from the count routine in main.cpp, and
          * the file name the user supplies
          * */
         Grader(int, const std::string &);

         /* XXX: Documentation
          * getter for number of students
          * so we can easily reserve space
          * in any temp vectors or arrays we
          * may need
          * */
         int getNumOfStudents(void) const;

         /* XXX: Documentation
          * getter for the datafile
          * */
         std::string getDataFile() const;

         /* XXX: Documentation
          * load our vector of student objects
          * */
         void loadVector(void);

         /* XXX: Documentation
          * A debug method, just shows the students
          * id and intial scores read in from the data file
          * */
         void showStudentVector(void);

         /* XXX: Documentation
          * the meat of this class, 2 C style for loops.
          * depends on a few helper functions
          * to properly perform computations on the grade data
          * */
         void makeGrades(void);

         /* XXX: Documentation
          * Helper method of makeGrades, takes in standard i, j
          * C style for loop integers, so it can calculate all grades
          * for each student, against the weight and maxmark
          *
          * Called from within makeGrades inner for loop since it needs
          * to calculate an array being stored in a vector
          * */
         float subGradeComputation(int , int );

         /* XXX: Documentation
          * after all sub grades have been calcluated,
          * gradeSummation adds them all up, one student at a time
          *
          * called from makeGrades outer for loop
          * */
         float gradeSummation(std::vector<float> &);

         /* XXX: Documentation
          * makes a call to macro routines in settings.h
          * to decide the range of the grade to match it to
          * a lettergrade representation held in the Echelon
          * struct also defined in settings.h
          *
          * called from makeGrades outer forloop
          * */
         std::string assignLetterGrade(float);

         /* XXX: Documentation
          * Final output method after all grades, are computed,
          * rounded, and stored in StudentContainer Vector
          * */
         void outputFinal(void);
   };
};

#endif
