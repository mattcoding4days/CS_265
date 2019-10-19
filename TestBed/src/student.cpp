#include "include/student.h"
#include <iostream>
#include <fstream>
#include <sstream>


StudentData::StudentData(void)
   : name ("")
   , gradesContainer({0})
{ }

inline std::string StudentData::getName() const
{
   return this->name;
}

inline void StudentData::setName(const std::string &_name)
{
   this->name = _name;
}

inline float StudentData::getGrades(const int &itr) const
{
   return this->gradesContainer[itr]; 
}

inline void StudentData::setGrades( const int& itr, const float& _grade)
{
   if ( itr > -1 ) { 
      this->gradesContainer[itr] = _grade;
   } else {
      std::cerr << "Iterator must be greater than 0" << std::endl;
   }
}

inline u_int StudentData::getContainerSize() const
{
   return gradesContainer.size();
}

void StudentData::printStudentPair(const std::string &tempName,
                                   std::array <float, LEN> tempContainer ) const
{
   std::cout << tempName << " : ";
   for ( u_int i = 0; i < tempContainer.size(); ++i ) {
      std::cout << tempContainer[i] << "  ";
   }
   std::cout << std::endl;
}

void StudentData::printStudentObject() const
{
   std::cout << this->getName() << " ";
   for ( u_int i = 0; i < this->getContainerSize() ; ++i ) {
      std::cout << this->getGrades(i) << " ";
   }
   std::cout << std::endl;
}

bool StudentData::loadDataFile(const std::string &file)
{
   std::string line;
   std::ifstream datafile(file);
   
   if (datafile.good()) {
      while (std::getline(datafile, line)) {
         if (! (line.empty()) ) {
            char firstC = '\0';
            firstC = line[0];
            if (! (std::isupper(firstC)) && firstC != '#' && firstC != ' ') {
               std::string sName("");
               std::array<float, LEN> mark;
               std::stringstream ss(line);
               ss >> sName;
               this->setName(sName);
               for (u_int i = 0; i < mark.size(); ++i) {
                  ss >> mark[i];
                  this->setGrades(i, mark[i]);
               }
            }
         }
      }
   } else {
      std::cerr << "File does not exist: " << file << std::endl;
      return false;
   }
   return true;
}
