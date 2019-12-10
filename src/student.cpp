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
   StudentData::StudentData(void)
      : name ("")
        , totalGrade(0.0)
        , letterGrade("")
        , isWDR(false)
        , isError(false)
        , errorDefinition("")

   {
      gradesContainer.reserve(1);
      calculatedGradesContainer.reserve(1);
   }

   void StudentData::errorPreserve(std::string &e)
   {
      /* The offending line data will have already been set 
       * in the loadStudent method with currentLine
       * */
      this->setIsError(true);
      this->setErrorDefinition(e);
   }


   std::string StudentData::getName() const { return this->name; }


   void StudentData::setName(std::string &_name)
   {
      try {
         if (isAlphaNumeric(_name)) {
            this->name = _name; 
         }
         else {
            throw StudentIDNonAlphaNumeric();
         }
      } catch (StudentIDNonAlphaNumeric &e) {
         std::string onError(e.what());
         this->errorPreserve(onError);
      } 
   }

   int StudentData::getStudentDataLen() const { return this->studentDataLength; }


   void StudentData::setStudentDataLen(int _length, int eval)
   {
      try {
         if (_length == eval) {
            this->studentDataLength = _length;
         }
         else {
            /* Our lengths do not match, cannot compute data correctly
             * throw and end program
             * */
            throw StudentDataLengthError();
         }

      } catch (StudentDataLengthError &e) {
         std::string onError(e.what());
         this->errorPreserve(onError);
      }
   }


   float StudentData::getGrades(int &itr) { return this->gradesContainer[itr]; }


   void StudentData::setGrades(std::string &_grade, std::vector<float> &tMax)
   {
      try {
         /* Check if string is infact a digit */
         if (isDigits(_grade)) {
            float temp = stringTofloat(_grade);
            this->gradesContainer.emplace_back(temp);
            /* Check if a mark is larger than max mark */
            int size = this->gradesContainer.size();
            for (int i = 0; i < size; i++ ) {
               if (this->gradesContainer[i] > tMax[i] 
                     && !(this->getIsStudentWDR())) {
                  throw StudentMarkExceedsMaxMark();
               }
            }
         }
         else { 
            /* if it is not a digit, convert to uppercase and
             * and check if it is WDR, if not throw error
             * */
            std::string n_grade = convert_toupper(_grade);
            if (n_grade == WDRN) {
               this->setIsStudentWDR(true);
            }
            else {
               throw FailStringFloatConversion(); 
            }
         }
      } catch (FailStringFloatConversion &e) {
         std::string onError(e.what());
         errorPreserve(onError);
      } catch (StudentMarkExceedsMaxMark &e) {
         std::string onError(e.what());
         errorPreserve(onError);
      }
   }

   float StudentData::getCalculatedGrades(int &itr) { return this->calculatedGradesContainer[itr]; }


   void StudentData::setCalculatedGrades(std::vector<float> &calcMarks) 
   {
      for (std::size_t i = 0; i < calcMarks.size(); ++i) {
         this->calculatedGradesContainer.emplace_back(calcMarks[i]);
      }
   }


   float StudentData::getTotalGrade() const { return this->totalGrade; }


   void StudentData::setTotalGrade(const float _totalGrade) { this->totalGrade += _totalGrade; }


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


   bool StudentData::loadStudentFile(const std::string &file,
         const std::streampos &updatedFilePosition,
         int updateLinePosition, int evalLength,
         std::vector<float> &tempMaxMark)
   {
      try {
         std::ifstream datafile(file);
         if ( datafile.is_open() ) {
            datafile.seekg(updatedFilePosition);
            this->incrementFileLineCount(updateLinePosition);
            std::string line("");
            while ( std::getline(datafile, line)) {
               /* if the line is empty skip it,
                * by immediatley restarting the 
                * control loop with the continue keyword
                * */
               if (line.empty()) { continue; }
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
                   * If the name setter failed it would have reported 
                   * to errorPreserve which would have switched
                   * the isError variable to true, check for that here
                   * */

                  if (this->getIsError()) {
                     this->setCurrentFilePos(datafile);
                     datafile.close();
                     return true;
                  } else {
                     int i = 0;
                     while (ss >> sMarks) {
                        this->setGrades(sMarks, tempMaxMark);
                        if (!(this->getIsError())) {
                           i++;
                        } else {
                           /* Setting the grades failed */
                           this->setCurrentFilePos(datafile);
                           datafile.close();
                           return true;
                        }
                     }

                     /* Set datalength checks if the length is the
                      * same as the evaluation data length */
                     this->setStudentDataLen(i, evalLength);
                     // only process one line at a time, update file position
                     this->setCurrentFilePos(datafile);
                     datafile.close();
                     return true;
                  }
               }
               /* A duplicate student was found, 
                * throw for error preserving purposes
                * */
               this->setCurrentFilePos(datafile);
               throw DuplicateFound();

            }
         } else { throw std::logic_error("*** File Not Found: "); }
      } catch (std::logic_error &e) {
         std::cerr << e.what() << file << std::endl;
         exit(EXIT_FAILURE);
      } catch (DuplicateFound &e) {
         std::string onError(e.what());
         this->errorPreserve(onError);
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
