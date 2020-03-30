#ifndef UTILLITY_HPP
#define UTILLITY_HPP

#include <string>
#include <vector>
#include "customExceptions.hpp"
#include "settings.hpp"



namespace GraderApplication
{
  /* NOTE: Documentation
   * The Utillity class is just that, a collection
   * of methods that perform generic tasks, some are already
   * featured in the C standard or C++ standard library, but
   * have been made more robust for this projects specifications
   * */
  class Utillity
  {
    protected:
      std::string currentLine;

    public:

      /* NOTE: Documentation
         Default Constructor
         */
      Utillity(void);


      /*
NOTE: Documentation
Move Constructor
use noexcept for compiler optimizations
*/
      Utillity(Utillity &&) noexcept;


      /*
NOTE: Documentation
Copy Constructor
*/
      Utillity(const Utillity &);


      /*
NOTE: Documentation
Overload the move assignment
use noexcept for compiler optimizations
*/
      Utillity& operator=(Utillity &&) noexcept;


      /*
NOTE: Documentation
Copy assignment
*/
      Utillity& operator=(const Utillity &);


      /*
NOTE: Documentation
Accessor: getter and setter
stores the current line we read in,
this is mainly for the error reporing
*/
      std::string currentLineContent(void) const;
      void setCurrentLineContent(const std::string &);


      /*
NOTE: Documentation
Strip all comments from the line that is passed
*/
      void stripComments(std::string &);


      /*
NOTE: Documentation
search whole or decimal string representation
of a number, and return true if there is only
digits
*/
      bool isDigits(std::string &);


      /*
NOTE: Documentation
convert a string to a float with out the
truncating limitations of stof
*/
      float stringTofloat(const std::string &);


      /*
NOTE: Documentation
Summ all elements in array
*/
      float vecSummation(std::vector<float> &);


      /*
NOTE: Documentation
check if string is only alpha numeric
*/
      bool isAlphaNumeric(std::string &);


      /*
NOTE: Documentation
Convert a string to upper case
using transform, code comes from
cpp preference transform Documentation
*/
      std::string convert_toupper(std::string &);
  };
};

#endif
