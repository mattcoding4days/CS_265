/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/customExceptions.h"
#include "../hdr/student.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraderApplication {
   /* temp file for storing students that have already
    * been processed
    * */
   static const std::string TEMP_FILE = "temp.txt";

   StudentData::StudentData(void)
      : name ("")
        , gradesContainer({0})
        , finalGrade(0.0)
        , letterGrade("")

        { }


   void StudentData::sanitize(void) const { std::system("rm temp.txt"); }


   std::string StudentData::getName() const { return this->name; }


   void StudentData::setName(const std::string &_name) { this->name = _name; }


   float StudentData::getGrades(int &itr) { return this->gradesContainer[itr]; }


   void StudentData::setGrades( const int &itr, const float &_grade)
   {
      if ( itr <= this->getDataLength() ) { 
         this->gradesContainer[itr] = _grade;
      }
      else {
         std::cerr << "Iterator is out of bounds" << std::endl;
      }
   }


   float StudentData::getFinalGrade() const { return this->finalGrade; }

   void StudentData::setFinalGrade(const float &_finalGrade)
   { 
      this->finalGrade = _finalGrade; 
   }


   std::string StudentData::getLetterGrade() const { return this->letterGrade; }

   void StudentData::setLetterGrade(const std::string &_letterGrade) 
   { 
      this->letterGrade = _letterGrade;
   }


   void StudentData::printStudentObject()
   {
      /* method used mainly for debugging purposes */
      std::cout << this->getName() << " ";
      for ( int i = 0; i < this->getDataLength(); ++i ) {
         std::cout << this->getGrades(i) << " ";
      }
      std::cout << std::endl;
   }


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
                  for (int i = 0; i < this->getDataLength(); ++i) {
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
      }
      else {
         std::cerr << "File does not exist: " << file << std::endl;
         return false;                                             
      }
      datafile.close();
      return true;
   }


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
      // the file did not exist, which means
      // this is the first student we are reading infile
      return isProcessed;
   }


   bool StudentData::testForFileExistance(const std::string &file)
   {
      /* Test if grader has already created or temp file */
      bool doesExist = false;
      std::ifstream infile(file);
      if ( infile.good() ) {
         infile.close();
         doesExist = true;
         return doesExist;
      }
      return doesExist;
   }


   void StudentData::processStudent(const std::string &process)
   {
      /* only append to the file, dont trample over old data */
      std::fstream outFile(TEMP_FILE, std::fstream::in
            | std::fstream::out
            | std::fstream::app);
      if ( outFile.good() ) {
         outFile << process << std::endl;
         outFile.close();
      }
      else {
         std::cerr << "Debug MSG: Could not open file to process student" << std::endl;
      }
   }
};
