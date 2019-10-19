#include "student.cpp"
#include <vector>

using stuContainer = std::vector<StudentData>;


const std::string DATA = "../resource/data.txt";



int main()
{
   stuContainer s;
   s.reserve(2);
   
   StudentData stu1;
   StudentData stu2;


   float test = 1.2;
   stu1.setName("williamk");
   for ( u_int i = 0; i < stu1.getContainerSize(); ++i ) {
      stu1.setGrades(i, test);
      test++;
   }
   s.emplace_back(stu1);

   test = 1.3;
   stu2.setName("lenzTpaul");
   for ( u_int i = 0; i < stu2.getContainerSize(); ++i ) {
      stu2.setGrades(i, test);
      test++;
   }
   s.emplace_back(stu2);

   for ( const auto &itr: s ) {
      itr.printStudentObject();
   }

   return 0;
}
