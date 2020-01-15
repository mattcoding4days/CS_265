#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include "../hdr/utillity.hpp"

namespace GraderApplication
{

   Utillity::Utillity(void)
      : currentLine("")
   { }


   Utillity::Utillity(Utillity &&src) noexcept
      : currentLine(src.currentLine)
   {
      /* Ownership has changed, reset original object */
      src.currentLine = "";
   }


   Utillity::Utillity(const Utillity &src)
      : currentLine(src.currentLine)
   { }


   Utillity& Utillity::operator=(Utillity &&src) noexcept
   {
      /* Pessimistic self assignment check */
      if (this == &src)
      {
         return *this;
      }

      /* Move the member */
      currentLine = src.currentLine;

      /* reset old object, ownership has chaged */
      src.currentLine = "";

      return *this;
   }


   Utillity& Utillity::operator=(const Utillity &src)
   {
      /* Pessimistic self assignment check */
      if (this == &src)
      {
         return *this;
      }

      currentLine = src.currentLine;

      return *this;
   }


   std::string Utillity::currentLineContent(void) const { return this->currentLine; }


   void Utillity::setCurrentLineContent(const std::string &_currentLine)
   {
      if (!(_currentLine.empty()))
      {
         this->currentLine = _currentLine;
      }
   }


   void Utillity::stripComments(std::string &line)
   {
      std::size_t found = line.find(COMM);
      if (found != std::string::npos)
      {
         line.erase(found, std::string::npos);
      }
   }


   bool Utillity::isDigits(std::string &s)
   {
      return s.find_first_not_of("0123456789.") == std::string::npos;
   }


   float Utillity::stringTofloat(const std::string &s)
   {
      float tempconvert = 0;
      std::stringstream streamVar(s);
      try
      {
         streamVar >> tempconvert;
         if (streamVar.fail())
         {
            throw StreamConversionFailure();
         }
      }
      catch (StreamConversionFailure &e)
      {
         std::cerr << e.what() << std::endl;
      }
      // will only return upon success
      return tempconvert;
   }


   float Utillity::vecSummation(std::vector<float> &s)
   {
      float tempFinalGrade = 0;
      return accumulate(s.begin(), s.end(), tempFinalGrade);
   }


   bool Utillity::isAlphaNumeric(std::string &s)
   {
      std::string::size_type i = 0;
      while ( (i < s.length()) )
      {
         if (! (std::isalnum(s[i])) )
         {
            return false;
         }
         ++i;
      }
      return true;
   }


   std::string Utillity::convert_toupper(std::string &s)
   {
      std::transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c) { return std::toupper(c); }
            );
      return s;
   }
};
