#ifndef BASE_H
#define BASE_H

#include <string>
#include <array>


namespace GraderProgram
{
   /* constants */
   const int MAX = 8;
   const std::string FILE_PATH = "../../resource/test.txt";

   enum Delimiters
   { 
      WHITESPC = ' ', 
      COMM = '#' 
   };

   class BaseSchema
   {
   protected:
      std::string titleBase;
      std::array <std::string, MAX> title;
      std::string categoryBase;
      std::array <std::string, MAX> category;
      std::string maxMarkBase;
      std::array <float, MAX> maxMark;
      std::string weightBase;
      std::array <float, MAX> weight;
   public:
      BaseSchema();
      void outputStringPair(const std::string &, std::array <std::string, MAX>);

      void outputStringFloatPair(const std::string &, std::array <float, MAX>);
   };
};

#endif
