#ifndef STUDENT_H
#define STUDENT_H

#include "settings.h"
#include <array>

namespace GraderApplication {
   class StudentData {
   private:
      static const int stuContainerSize = LEN;
      std::string name;
      std::array <float, stuContainerSize> gradesContainer;

   public:
      /* XXX: Documentation
       * */
      StudentData(void);
      

      /* XXX: Documentation
       * */
      std::string getName() const;
      void setName(const std::string &);
       

      /* XXX: Documentation
       * */
      float getGrades(const int &) const;
      void setGrades(const int &, const float&);
      

      /* XXX: Documentation
       * */
      int getContainerSize() const;


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
