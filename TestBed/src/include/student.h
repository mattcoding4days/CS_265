#ifndef STUDENT_H
#define STUDENT_H

#include "settings.h"
#include <array>


class StudentData
{
private:
   std::string name;
   std::array <float, LEN> gradesContainer;

public:
   /* XXX: Documentaion
    * */
   StudentData(void);
   
   /* XXX: Documentaion
    * */
   inline std::string getName() const;
   
   /* XXX: Documentaion
    * */
   inline void setName(const std::string &);
     
   /* XXX: Documentaion
    * */
   inline float getGrades(const int &) const;
   
   /* XXX: Documentaion
    * */
   inline void setGrades(const u_int &, const float&);
   
   /* XXX: Documentaion
    * */
   inline u_int getContainerSize() const;

   /* XXX: Documentaion
    * */
   void printStudentPair(const std::string &, std::array <float, LEN> &) const;
   
   /* XXX: Documentaion
    * */
   void printStudentObject() const;
   
   /* XXX: Documentaion
    * */
   bool loadDataFile(const std::string &);
};

#endif
