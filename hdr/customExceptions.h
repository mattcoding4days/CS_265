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
};


#endif
