#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include <exception>
#include <string>

namespace GraderApplication
{

   class DuplicateFound : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Duplicate Found ***";
         }
   };


   class WeightSummation : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Weight summation is out of bounds ***";
         }
   };


   class DataLength : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Evaluation data length does not match *** [eg]: "
               " corrupted or non-standardized data";
         }
   };


   class FailStringFloatConversion : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Could not convert string to float due to corrupted data ***";
         }
   };


   class StreamConversionFailure : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Stringstream failed to convert string to float ***";
         }
   };


   class StudentIDNonAlphaNumeric : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Student-id is non alphanumeric ::: Line discarded ***";
         }
   };


   class StudentNotFound : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Student ID was not found: ";
         }
   };


   class StudentMarkExceedsMaxMark : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** The Students Mark exceeds the maximum possible mark ***";
         }
   };


   class StudentDataLengthError : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** The amount of student grades does not match the evaluation length ***";
         }
   };


   class StudentIDEmpty : public std::exception
   {
      public:
         const char *what() const throw()
         {
            return "*** Student id field empty ***";
         }
   };
};

#endif
