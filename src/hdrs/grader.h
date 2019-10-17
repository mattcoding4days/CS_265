#ifndef GRADER_H
#define GRADER_H

#include "student.h"

namespace GraderProgram
{
   class Grader : public BaseSchema, public StudentSchema
   {
   public:
      Grader();

   };
};

#endif
