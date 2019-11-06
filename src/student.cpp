#include "hdr/student.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraderApplication {

   const std::string TEMP_FILE = "temp.txt"; 
   /* XXX: Documentaion
    * */
   StudentData::StudentData(void)
      : name ("")
      , gradesContainer({0})
   { }


   /* XXX: Documentaion
    * */
   std::string StudentData::getName() const
   {
      return this->name;
   }


   /* XXX: Documentaion
    * */
   void StudentData::setName(const std::string &_name)
   {
      this->name = _name;
   }


   /* XXX: Documentaion
    * */
   float StudentData::getGrades(const int &itr) const
   {
      return this->gradesContainer[itr]; 
   }


   /* XXX: Documentaion
    * */ 
   void StudentData::setGrades( const int &itr, const float &_grade)
   {
      if ( itr > this->getContainerSize() || itr < 0 ) { 
         std::cerr << "Iterator is out of bounds" << std::endl;
      } else {
         this->gradesContainer[itr] = _grade;
      }
   }


   /* XXX: Documentaion
    * */
   int StudentData::getContainerSize() const
   {
      return this->stuContainerSize;
   }


   /* XXX: Documentaion
    * */
   void StudentData::printStudentPair(const std::string &theName,
                                      std::array <float, LEN> &theContainer ) const
   {
      std::cout << theName << " : ";
      for ( int i = 0; i < this->getContainerSize(); ++i ) {
         std::cout << theContainer[i] << "  ";
      }
      std::cout << std::endl;
   }


   /* XXX: Documentaion
    * */
   void StudentData::printStudentObject() const
   {
      std::cout << this->getName() << " ";
      for ( int i = 0; i < this->getContainerSize() ; ++i ) {
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
         while ( std::getline(datafile, line) ) {
            char firstC = '\0';
            firstC = line[0];
            if ( (std::islower(firstC)) && firstC != COMM && firstC != WS ) {
               if ( ! (this->isStudentProcessed(line)) ) {
                  this->processStudent(line);
                  std::string sName("");
                  float mark = 0.0;
                  std::stringstream ss(line);
                  ss >> sName;
                  this->setName(sName);
                  for (int i = 0; i < this->getContainerSize(); ++i) {
                     ss >> mark;
                     this->setGrades(i, mark);
                  }
                  // only process one line at a time
                  datafile.close();
                  return true;
               }
               /* The line was found in the temp.txt file, and has already
                * been processed, repeat the process
                * */
            }
         }
      } else {
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
      bool isProcessed = false;
      std::string tempLine("");
      // test if the file exists
      if ( this->testForFileExistance(TEMP_FILE) ) {
         std::ifstream tempFile(TEMP_FILE);
         while ( std::getline(tempFile, tempLine) ) {
            if ( lineToCompare == tempLine ) {
               tempFile.close();
               isProcessed = true;
               return isProcessed;
            }
         }
      }
      return isProcessed;
   }


   /* XXX: Documentaion
    * only test to see if the temp file has been created
    * */
   bool StudentData::testForFileExistance(const std::string &file)
   {
      bool doesExist = false;
      std::ifstream infile(file);
      if ( infile.good() ) {
         infile.close();
         doesExist = true;
         return doesExist;
      }
      return doesExist;
   }


   /* XXX: Documentaion
    * */
   void StudentData::processStudent(const std::string &process)
   {
      // only append to file
      std::fstream outFile(TEMP_FILE, std::fstream::in | std::fstream::out | std::fstream::app);
      if ( outFile.good() ) {
         outFile << process << std::endl;
         outFile.close();
      } else {
         std::cerr << "Debug MSG: Could not open file to process student" << std::endl;
      }
   }
};
