#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>

namespace GraderApplication {

   class DuplicateFound : public std::exception {
      public:
      const char *what() const throw() {
         return "Duplicate Found: ";
      }
   };

   class WeightSummation : public std::exception {
      public:
      const char *what() const throw() {
         return "Weight summation is out of bounds";
      }
   };

   class DataLength : public std::exception {
      public:
      const char *what() const throw() {
         return "Data entry length does not match";
      }
   };
};


#endif
