#ifndef GRADER_H
#define GRADER_H

#include "student.h"
#include <vector>

class Grader
{
private:
   std::vector<StudentData> studentContainer;

public:
   /* default constructor */
   Grader();
   void loadVector(const std::string &, const float &);
   void loadFile(const std::string &);
   void showStudentVector() const;
};


#endif
