#include "include/student.h"
#include <iostream>
#include <fstream>
#include <sstream>


/* XXX: Documentaion
 * */
StudentData::StudentData(void)
   : name ("")
   , gradesContainer({0})
{ }

/* XXX: Documentaion
 * */
inline std::string StudentData::getName() const
{
   return this->name;
}

/* XXX: Documentaion
 * */
inline void StudentData::setName(const std::string &_name)
{
   this->name = _name;
}

/* XXX: Documentaion
 * */
inline float StudentData::getGrades(const int &itr) const
{
   return this->gradesContainer[itr]; 
}

/* XXX: Documentaion
 * */ inline void StudentData::setGrades( const u_int &itr, const float &_grade)
{
   if ( itr <= this->getContainerSize() ) { 
      this->gradesContainer[itr] = _grade;
   } else {
      std::cerr << "Iterator is out of bounds" << std::endl;
   }
}

/* XXX: Documentaion
 * */
inline u_int StudentData::getContainerSize() const
{
   return gradesContainer.size();
}

/* XXX: Documentaion
 * */
void StudentData::printStudentPair(const std::string &theName,
                                   std::array <float, LEN> &theContainer ) const
{
   std::cout << theName << " : ";
   for ( u_int i = 0; i < theContainer.size(); ++i ) {
      std::cout << theContainer[i] << "  ";
   }
   std::cout << std::endl;
}

/* XXX: Documentaion
 * */
void StudentData::printStudentObject() const
{
   std::cout << this->getName() << " ";
   for ( u_int i = 0; i < this->getContainerSize() ; ++i ) {
      std::cout << this->getGrades(i) << " ";
   }
   std::cout << std::endl;
}

/* XXX: Documentaion
 * */
bool StudentData::loadDataFile(const std::string &file)
{
   std::string line;
   std::ifstream datafile(file);
   
   if (datafile.good()) {
      while (std::getline(datafile, line)) {
         if (! (line.empty()) ) {
            char firstC = '\0';
            firstC = line[0];
            if ( (std::islower(firstC)) && firstC != COMM && firstC != WS ) {
               std::string sName("");
               float mark = 0.0;
               std::stringstream ss(line);
               ss >> sName;
               this->setName(sName);
               for (u_int i = 0; i < this->getContainerSize(); ++i) {
                  ss >> mark;
                  this->setGrades(i, mark);
               }
            }
         }
      }
   } else {
      std::cerr << "File does not exist: " << file << std::endl;
      return false;
   }
   datafile.close();
   return true;
}
