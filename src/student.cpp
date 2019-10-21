#include "hdr/student.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraderApplication
{
   const std::string TEMP_FILE = "temp.txt";


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
    * */ 
   inline void StudentData::setGrades( const u_int &itr, const float &_grade)
   {
      if ( itr <= this->getContainerSize() )
      { 
         this->gradesContainer[itr] = _grade;
      }
      else {
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
      for ( u_int i = 0; i < theContainer.size(); ++i )
      {
         std::cout << theContainer[i] << "  ";
      }
      std::cout << std::endl;
   }


   /* XXX: Documentaion
    * */
   void StudentData::printStudentObject() const
   {
      std::cout << this->getName() << " ";
      for ( u_int i = 0; i < this->getContainerSize() ; ++i )
      {
         std::cout << this->getGrades(i) << " ";
      }
      std::cout << std::endl;
   }


   /* XXX: Documentaion
    * */
   bool StudentData::loadDataFile(const std::string &file)
   {
      std::ifstream datafile(file);
      
      if ( datafile.good() ) {
         std::string line;
         while ( std::getline(datafile, line) )
         {
            std::cout << "\nCurrent Line: " << line << "\n\n";
            char firstC = '\0';
            firstC = line[0];
            std::cout << "Debug MSG: checking if lower" << std::endl;
            if ( (std::islower(firstC)) && firstC != COMM && firstC != WS )
            {
               std::cout << "Debug MSG: Checking if: " << line << " is processed" << std::endl;
               if ( ! (this->isStudentProcessed(line)) )
               {
                  this->processStudent(line);
                  std::cout << "Debug MSG: Finished Processing Student-->  "
                            << line << std::endl;
                  std::string sName("");
                  float mark = 0.0;
                  std::stringstream ss(line);
                  ss >> sName;
                  this->setName(sName);
                  for (u_int i = 0; i < this->getContainerSize(); ++i)
                  {
                     ss >> mark;
                     this->setGrades(i, mark);
                  }
                  // only process one line at a time
                  datafile.close();
                  return true;
               }
               else {
                  std::cout << "Debug MSG: Student: " << line << " is NOT processed" << std::endl;
               }
            }
         }
      }
      else {
        std::cerr << "File does not exist: " << file << std::endl;
        return false;                                             
      }
      datafile.close();
      return true;
   }


   /* XXX: Documentaion
    * Will return true if string from data file matches
    * a line in temp file, which means we already read
    * that student in.
    * else return false
    * */
   bool StudentData::isStudentProcessed(const std::string &lineToCompare)
   {
      std::string tempLine("");
      // test if the file exists
      if ( this->testForFileExistance(TEMP_FILE) )
      {
         std::ifstream tempFile(TEMP_FILE);
         while ( std::getline(tempFile, tempLine) )
         {
            if ( lineToCompare == tempLine )
            {
               std::cout << "isStudentProcessed: Found in File " << lineToCompare << '\n';
               tempFile.close();
               return true;
            }
            //else {
            //   std::cout << "Debug MSG: Line: " << lineToCompare << " didnt match\n";
            //}
         }
      }
      else {
         // the file did not exist, which means
         // this is the first student we are reading infile
         std::cout << "Debug MSG: File does not exist" << std::endl;
      }
      return false;
   }


   /* XXX: Documentaion
    * only test to see if the temp file has been created
    * */
   bool StudentData::testForFileExistance(const std::string &file)
   {
      std::ifstream infile(file);
      if ( infile.good() )
      {
         infile.close();
         return true;
      }
      return false;
   }


   /* XXX: Documentaion
    * */
   void StudentData::processStudent(const std::string &process)
   {
      // only append to file
      std::fstream outFile(TEMP_FILE, std::fstream::in | std::fstream::out | std::fstream::app);
      if ( outFile.good() )
      {
         outFile << process << std::endl;
         std::cout << "processStudent(): Wrote: " << process << " to temp.txt" << std::endl;
         outFile.close();
      }
      else {
         std::cerr << "Debug MSG: Could not open file to process student" << std::endl;
      }
   }
};
