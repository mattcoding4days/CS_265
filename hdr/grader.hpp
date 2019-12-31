#ifndef GRADER_HPP
#define GRADER_HPP

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
struct Containers
{
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
        Containers(int _x) : numStudents (_x)
        {
            student.reserve(numStudents);
            error.reserve(1);
            wdr.reserve(1);
        }

        /* NOTE: Documentation
         * Default constructor
         * should not be needed,
         * but just incase for convenience
         */
        Containers(void) : numStudents (1)
        {
            student.reserve(numStudents);
            error.reserve(numStudents);
            wdr.reserve(numStudents);
        }

        ~Containers(void) { /* Uneeded */ }
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


#endif
