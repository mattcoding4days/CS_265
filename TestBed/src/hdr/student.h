#ifndef STUDENT_H
#define STUDENT_H

#include "settings.h"
#include <array>

namespace GraderApplication
{
   class StudentData
   {
   private:
      std::string name;
      std::array <float, LEN> gradesContainer;

   public:
      /* XXX: Documentation
       * */
      StudentData(void);
      

      /* XXX: Documentation
       * */
      inline std::string getName() const;
      inline void setName(const std::string &);
       

      /* XXX: Documentation
       * */
      inline float getGrades(const int &) const;
      inline void setGrades(const u_int &, const float&);
      

      /* XXX: Documentation
       * */
      inline u_int getContainerSize() const;


      /* XXX: Documentation
       * */
      void printStudentPair(const std::string &, std::array <float, LEN> &) const;
      

      /* XXX: Documentation
       * */
      void printStudentObject() const;
      

      /* XXX: Documentation
       * */
      bool loadDataFile(const std::string &);


      /* XXX: Documentation
       * */
      bool isStudentProcessed(const std::string &);


      /* XXX: Documentation
       * */
      bool testForFileExistance(const std::string &);


      /* XXX: Documentation
       * */
      void processStudent(const std::string &);
   };
};
#endif
