#include "student.cpp"
#include <vector>

using stuContainer = std::vector<StudentData>;


const std::string DATA = "../resource/data.txt";



int main()
{
   stuContainer s;
   std::array<StudentData, 6> stu;

   for ( const auto &itr: s ) {
      itr.printStudentObject();
   }

   return 0;
}
