#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>
#include <string>

namespace GraderApplication {

   class DuplicateFound : public std::exception {
      public:
      const char *what() const throw() {
         return "\n\t*** Duplicate Found: ";
      }
   };

   class WeightSummation : public std::exception {
      public:
      const char *what() const throw() {
         return "\n\t*** Weight summation is out of bounds";
      }
   };

   class DataLength : public std::exception {
      public:
      const char *what() const throw() {
         return "\n\t*** Base evaluation data length does not match";
      }
   };

   class FailStringFloatConversion : public std::exception {
      public:
      const char *what() const throw() {
         return "\n\t*** Could not convert string to float due to corrupted data: ";
      }
   };

   class StreamConversionFailure : public std::exception {
      public:
      const char *what() const throw() {
         return "\n\t*** Stringstream failed to convert string to float: ";
      }
   };
};

#endif
