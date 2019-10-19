#ifndef GRADER_H
#define GRADER_H

#include "student.h"
#include <vector>


class Grader : public StudentData
{
private:
   std::vector<StudentData> studentContainer;

public:
   /* default constructor */
   Grader(void);
   void loadVector(const std::string &, const float &);
   void loadFile(const std::string &);
   void showStudentVector() const;
};


#endif
