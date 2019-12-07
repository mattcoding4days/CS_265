/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/customExceptions.h"
#include "../hdr/student.h"
#include <algorithm>
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
        , finalGrade(0.0)
        , letterGrade("")
        , isWDR(false)

      {
         gradesContainer.reserve(1); 
      }


   void StudentData::errorPrint(const char *a)
   {
      std::cerr << "\nERROR: " << a << std::endl;
      std::cerr << "\nOffending line number: "
         << this->getFileLineCount() << std::endl;
      std::cerr << "Offending content: " 
         << this->getCurrentLine() << '\n' << std::endl;
   }
   

   void StudentData::sanitize(void) const { std::system("rm temp.txt"); }


   std::string StudentData::getName() const { return this->name; }


   void StudentData::setName(std::string &_name)
   {
      try {
         if (isAlphaNumeric(_name)) {
            std::cout << "Name is alphanumeric" << std::endl;
            this->name = _name; 
         }
         else {
            this->name = "";
            throw StudentIDNonAlphaNumeric();
         }

      } catch (StudentIDNonAlphaNumeric &e) {
         errorPrint(e.what());
      }
   }


   float StudentData::getGrades(int &itr) { return this->gradesContainer[itr]; }


   void StudentData::setGrades(std::string &_grade)
   {
      try {
         if (isDigits(_grade)) {
            float temp = stringTofloat(_grade);
            this->gradesContainer.emplace_back(temp);
            /* Check only the entered grades to see if max mark is exceeded */
            for (std::size_t i = 0; i < this->gradesContainer.size(); ++i) {
               if (this->gradesContainer[i] > this->getMaxMarkContainer(i)) {
                  std::cout << "\nStudent mark: " << this->gradesContainer[i]
                     << " :: Max Mark: " << this->getMaxMarkContainer(i) << std::endl; 
                  throw StudentMarkExceedsMaxMark();
               }
            }
         }
         else { 
            std::string n_grade = convert_toupper(_grade);
            if (n_grade == WDRN) {
               this->setIsStudentWDR(true);
            } else {
               throw FailStringFloatConversion(); 
            }
         }
      } catch (FailStringFloatConversion &e) {
         errorPrint(e.what());
      } catch (StudentMarkExceedsMaxMark &e) {
         errorPrint(e.what());
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

   bool StudentData::getIsStudentWDR() const { return this->isWDR; }


   void StudentData::setIsStudentWDR(bool _isWDR) { this->isWDR = _isWDR; }


   void StudentData::printStudentObject()
   {
      /* method used mainly for debugging purposes */
      std::cout << this->getName() << " ";
      for ( int i = 0; i < this->getDataLength(); ++i ) {
         std::cout << this->getGrades(i) << " ";
      }
      std::cout << std::endl;
   }


   bool StudentData::loadStudentFile(const std::string &file)
   {
      try {
         std::ifstream datafile(file);
         if ( datafile.is_open() ) {
            datafile.seekg(this->getCurrentFilePosition());
            std::string line;
            while ( std::getline(datafile, line) ) {
               if (!line.empty()) {
                  std::cout << "Current Line: " << line << std::endl;
                  std::cout << "Current file pos: " << this->getCurrentFilePosition() << std::endl;
                  this->setCurrentLine(line);
                  this->stripComments(line);

                  if ( ! (this->isStudentProcessed(line)) ) {
                     this->processStudent(line);

                     std::string sId("");
                     std::string sMarks("");

                     std::stringstream ss(line);
                     ss >> sId;
                     this->setName(sId);
                     /* After trying to set the name, if it fails
                      * due to nonNumeric, we need to test that here
                      * so we can end this function and not read in the
                      * grades for the failed id. 
                      * if the name is still empty after trying to 
                      * set it, we know it failed. end and update file position
                      * and total line count
                      * */

                     if (this->getName().empty()) {
                        this->setCurrentFilePos(datafile);
                        this->incrementFileLineCount();
                        datafile.close();
                        return true;
                     } else {
                        int i = 0;
                        while (ss >> sMarks) {
                           this->setGrades(sMarks);
                           i++;
                        }
                        /* Set datalength checks if the length is the
                         * same as the evaluation data length */
                        this->setDataLength(i);
                     }

                     // only process one line at a time, update file position
                     this->setCurrentFilePos(datafile);
                     this->incrementFileLineCount();
                     datafile.close();
                     std::cout << "Closing file" << std::endl;
                     return true;
                  }
                  /* The line was found in the temp.txt file, and has already
                   * been processed, repeat the process
                   * */
               }
               std::cout << "Line is empty" << std::endl;
            }
         } else { throw std::logic_error("*** File Not Found: "); }
      } catch (std::logic_error &e) {
         std::cerr << e.what() << file << std::endl;
      }
      return false;
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
      std::ofstream outFile(TEMP_FILE, std::fstream::app);
      if ( outFile.good() ) {
         // write only the student id, which should be the first
         // index of the line
         outFile << process[0] << std::endl;
         outFile.close();
      }
      else {
         std::cerr << "Debug MSG: Could not open file to process student" << std::endl;
      }
   }


   bool StudentData::isAlphaNumeric(std::string &s)
   {
      std::string::size_type i = 0;
      while ( (i < s.length()) ) {
         if (! (std::isalnum(s[i])) ) {
            return false;
         } 
         ++i;
      }
      return true;
   }


   std::string StudentData::convert_toupper(std::string s)
   {
      std::transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c) {return std::toupper(c);}
            );
      return s; // shouldnt reach here
   }
};
