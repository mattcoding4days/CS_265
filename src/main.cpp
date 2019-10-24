#include "student.cpp"
#include "base.cpp"
#include <vector>

using namespace GraderApplication;
using stuContainer = std::vector<StudentData>;


const std::string DATA = "../test/official.txt";

int main()
{
   int amount = 4;
   stuContainer s;
   s.reserve(amount);
   
   for ( int i = 0; i < amount; ++i ) {
      StudentData student;
      student.loadDataFile(DATA);
      s.emplace_back(student);
   }

   std::cout << "\n\n";
   for ( const auto &itr: s ) {
      itr.printStudentObject();
   }
   return 0;
}
