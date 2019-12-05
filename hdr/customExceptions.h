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
         return "Base evaluation data length does not match";
      }
   };

   class FailStringFloatConversion : public std::exception {
      public:
      const char *what() const throw() {
         return "Could not convert string to float due to corrupted data: ";
      }
   };

   class StreamConversionFailure : public std::exception {
      public:
      const char *what() const throw() {
         return "Stringstream failed to convert string to float: ";
      }
   };
};


#endif
