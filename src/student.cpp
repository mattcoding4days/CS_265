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

   StudentData::StudentData(void)
        : name ("")
        , finalGrade(0.0)
        , letterGrade("")
        , isWDR(false)
        , isError(false)
        , errorDefinition("")

      {
         gradesContainer.reserve(1); 
      }


   void StudentData::errorPrint(std::string &a)
   {
      this->setIsError(true);
      std::cerr << "\nERROR: " << a << std::endl;
      std::cerr << "\nOffending line number: "
         << this->getFileLineCount() << std::endl;
      std::cerr << "Offending content: " 
         << this->getCurrentLine() << '\n' << std::endl;
   }
   

   std::string StudentData::getName() const { return this->name; }


   void StudentData::setName(std::string &_name)
   {
      try {
         if (isAlphaNumeric(_name)) {
            this->name = _name; 
         }
         else {
            std::cout << "Name: " << _name << " is not alphanumeric" << std::endl;
            this->name = "";
            throw StudentIDNonAlphaNumeric();
         }

      } catch (StudentIDNonAlphaNumeric &e) {
         std::string onError(e.what());
         errorPrint(onError);
      }
   }


   float StudentData::getGrades(int &itr) { return this->gradesContainer[itr]; }


   void StudentData::setGrades(std::string &_grade)
   {
      try {
         if (isDigits(_grade)) {
            float temp = stringTofloat(_grade);
            this->gradesContainer.emplace_back(temp);
            /* Check if a mark is larger than max mark */

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
         std::string onError(e.what());
         errorPrint(onError);
      } 
   }


   float StudentData::getFinalGrade() const { return this->finalGrade; }


   void StudentData::setFinalGrade(const float &_finalGrade) { this->finalGrade = _finalGrade; }


   std::string StudentData::getLetterGrade() const { return this->letterGrade; }


   void StudentData::setLetterGrade(const std::string &_letterGrade) { this->letterGrade = _letterGrade; }


   bool StudentData::getIsStudentWDR() const { return this->isWDR; }


   void StudentData::setIsStudentWDR(bool _isWDR) { this->isWDR = _isWDR; }


   bool StudentData::getIsError() const { return this->isError; }


   void StudentData::setIsError(bool _isError) { this->isError = _isError; }


   std::string StudentData::getErrorDefinition(void) const { return this->errorDefinition; }


   void StudentData::setErrorDefinition(const std::string &e)
   {
      if (!e.empty()) {
         this->errorDefinition = e;
      } else {
         std::cerr << "\nError Definition is empty!\n" << std::endl;
      }
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


   bool StudentData::loadStudentFile(const std::string &file,
      const std::streampos &updatedFilePosition, int updateLinePosition)
   {
      try {
         std::ifstream datafile(file);
         if ( datafile.is_open() ) {
            datafile.seekg(updatedFilePosition);
            this->incrementFileLineCount(updateLinePosition);
            std::string line;
            while ( std::getline(datafile, line) ) {
               if (!line.empty()) {
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
                        std::cout << "Name is empty" << std::endl;
                        this->setCurrentFilePos(datafile);
                        this->incrementFileLineCount(1);
                        return false;
                        
                     } else {
                        std::cout << "Setting grades" << std::endl;
                        int i = 0;
                        while (ss >> sMarks) {
                           this->setGrades(sMarks);
                           i++;
                        }
                        /* Set datalength checks if the length is the
                         * same as the evaluation data length */
                        this->setDataLength(i);
                     }
                     std::cout << "Did not close after if " << std::endl;
                     // only process one line at a time, update file position
                     this->setCurrentFilePos(datafile);
                     this->incrementFileLineCount(1);
                     datafile.close();
                     return true;
                  }
                  /* The line was found in the temp.txt file, and has already
                   * been processed, repeat the process
                   * */
               }
            }
         } else { throw std::logic_error("*** File Not Found: "); }
      } catch (std::logic_error &e) {
         std::cerr << e.what() << file << std::endl;
         exit(EXIT_FAILURE);
      }
      return false;
   }


   bool StudentData::isStudentProcessed(const std::string &lineToCompare)
   {
      bool isProcessed = false;
      std::string tempLine("");
      // test if the file exists
      if ( this->testForFileExistence(TEMPFILE) ) {
         std::ifstream tempFile(TEMPFILE);
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


   bool StudentData::testForFileExistence(const std::string &file)
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
      std::ofstream outFile(TEMPFILE, std::fstream::app);
      if ( outFile.good() ) {
         // write only the student id, which should be the first
         // index of the line
         outFile << process << std::endl;
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
            [](unsigned char c) { return std::toupper(c); }
            );
      return s;
   }
};
