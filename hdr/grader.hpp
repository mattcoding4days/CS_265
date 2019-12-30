#ifndef GRADER_HPP
#define GRADER_HPP

#include "../hdr/evaluation.hpp"
#include "../hdr/student.hpp"

using namespace GraderApplication;

/* Change template mess, for readabillity */
using StudentVector = std::vector<StudentData>;



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
