#ifndef STUDENT_H
#define STUDENT_H

#include "base.h"

namespace GraderProgram
{
   class StudentSchema
   {
   protected:
      std::string name;
      std::array <float, MAX> grades;
   public:
      StudentSchema();
      
      void outputStudentPair(const std::string &, std::array <float, MAX>);
   };
};

#endif
