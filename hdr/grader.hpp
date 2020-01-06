#ifndef GRADER_HPP
#define GRADER_HPP

#include <iterator>
#include "../hdr/evaluation.hpp"
#include "../hdr/student.hpp"

using namespace GraderApplication;

/* Change template mess, for readabillity */
using StudentVector = std::vector<StudentData>;


/* NOTE: Documentation
 * Since Most of the code in grader.cc
 * will be written in a procedural style
 * utilizing all other classes. Objects will
 * need to be passed around alot, it will be
 * simpler to pass around a structure of all the
 * typedef'd student vector containers, than trying
 * to pass all 3 of them as parameters into the same
 * function
 */
struct Container
{
    public:
        int numStudents;
        StudentVector student;
        StudentVector error;
        StudentVector wdr;
        StudentVector::iterator i;

        /* NOTE: Documentation
         * Explicit Constructor
         * Only takes one argument to reserve
         * the correct amount of space required to hold
         * all students
         */
        Container(int _x);

        ~Container(void) { /* Uneeded */ }
};


/* NOTE: Documentation
 * countStudentLines: Is meant to only count lines
 * that include student names
 *
 * The function uses a BaseData obj to load
 * the evaluation data first, so it can accurately
 * jump to only the student data. thus resulting
 * in an accurate ammount of students
 * */
int countStudentLines(EvaluationData &);


/* NOTE: Documentation
* load our vector of student objects
* */
void loadStudentContainers(EvaluationData &, Container &);


/* NOTE: Documentation
* Search for student by specified name
* */
StudentData searchStudent(Container &, const std::string &);


/* NOTE: Documentation
* the meat of this class, 2 C style for loops.
* depends on a few helper functions
* to properly perform computations on the grade data
* */
void makeGrades(EvaluationData &e, Container &c);


/* NOTE: Documentation
* Helper method of makeGrades, takes in standard i, j
* C style for loop integers, so it can calculate all grades
* for each student, against the weight and maxmark
*
* Called from within makeGrades inner for loop since it needs
* to calculate an array being stored in a vector
* */
float subGradeComputation(EvaluationData &, Container &, int , int );


/* NOTE: Documentation
* makes a call to macro routines in settings.h
* to decide the range of the grade to match it to
* a lettergrade representation held in the Echelon
* struct also defined in settings.h
*
* called from makeGrades outer forloop
* */
std::string assignLetterGrade(float);


/* NOTE: Documentation
* Final output method after all grades, are computed,
* rounded, and stored in StudentContainer Vector
*
* Overloaded to output single student
* */
void outputStudent(Container &);
void outputStudent(StudentData &);


/* NOTE: Documentation
* Output all students who are withdrawn
* */
void outputWDR(Container &);


/* NOTE: Documentation
* Output all the student error lines that were
* perserved allong the way
* */
void outputError(Container &);


/* NOTE: Documentation
* Clean up the temp file
* we have been operating on
*/
void sanitize(void);


#endif
