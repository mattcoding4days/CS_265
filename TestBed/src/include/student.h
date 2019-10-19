#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <array>


const int LEN = 8;

class StudentData
{
private:
   std::string name;
   std::array <float, LEN> gradesContainer;

public:
   /* Default Constructor */
   StudentData(void);
   
   inline std::string getName() const;
   inline void setName(const std::string &);
     
   inline float getGrades(const int &) const;
   inline void setGrades(const int &, const float&);
   inline u_int getContainerSize() const;

   void printStudentPair(const std::string &, std::array <float, LEN>) const;
   void printStudentObject() const;
   bool loadDataFile(const std::string &);
};

#endif
