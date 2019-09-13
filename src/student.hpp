#ifndef STUDENT_H
#define STUDENT_H

#include <string>

namespace Grades
{
   /* constants and typedefs */
   const std::string FILE_NAME("../resource/test.txt");
   typedef std::string BUFFER;

   class Student
   {
   private:
      std::string category;
      std::string title;
      std::string maxMark;
      std::string mark;
   public:
      // default constructor
      Student();
      
      // getters and setters
      const std::string& getCategory() const;
      void setCategory(const std::string&);

      const std::string& getTitle() const;
      void setTitle(const std::string&);

      const std::string& getMaxMark() const;
      void setMaxMark(const std::string&);

      const std::string& getMark() const;
      void setMark(const std::string&);

      /* TODO: Need to write some robust public methods for book keeping */
   };
};

#endif
