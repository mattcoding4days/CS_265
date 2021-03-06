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
  private:
    /* NOTE: Documentation
     * Copy Constructor
     * we dont want this called
     * force the move constructor to be called
     */
    Container(const Container &) = delete;

    /*NOTE: Documentation
     * Copy Assignment
     * we also dont want this being called
     * */
    Container& operator=(const Container &) = delete;

  public:
    int numStudents;
    StudentVector student;
    StudentVector error;
    StudentVector wdr;


    /* NOTE: Documentation
     * Explicit Constructor
     * Only takes one argument to reserve
     * the correct amount of space required to hold
     * all students
     */
    Container(int _x);


    /* NOTE: Documentation
     * Destructor
     */
    ~Container(void);


    /*NOTE: Documentation
     * Move Constructor
     * */
    Container(Container &&);


    /*NOTE: Documentation
     * Move Assignment
     * */
    Container& operator=(Container &&);
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
int countStudentLines(const EvaluationData &);


/* NOTE: Documentation
 * load our vector of student objects
 * */
void loadStudentContainers(EvaluationData &, Container &);


/* NOTE: Documentation
 * Search for student by specified name
 * */
StudentData searchStudent(const Container &, const std::string &);


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
void outputStudent(const Container &);
void outputStudent(const StudentData &);


/* NOTE: Documentation
 * Output all students who are withdrawn
 * */
void outputWDR(const Container &);


/* NOTE: Documentation
 * Output all the student error lines that were
 * perserved allong the way
 * */
void outputError(const Container &);


/* NOTE: Documentation
 * Clean up the temp file
 * we have been operating on
 */
void sanitize(void);


#endif
