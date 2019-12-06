/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/base.h"
#include "../hdr/customExceptions.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>

namespace GraderApplication {
   BaseData::BaseData(void)
      : dataLineLength(0)
        , totalLineCount(0)
        , currentLine("")
        , currentFilePos(0)
        , title("")
        , category("")
        , maxMark("")
        , weight("")

   {
      /* Init vectors */
      titleContainer.reserve(1);
      categoryContainer.reserve(1);
      maxMarkContainer.reserve(1);
      weightContainer.reserve(1);
   }

   void BaseData::errorPrint(const char *a)
   {
      std::cerr << "\nERROR: " << a << std::endl;
      std::cerr << "\nOffending line number: "
         << this->getFileLineCount() << std::endl;
      std::cerr << "Offending content: " 
         << this->getCurrentLine() << std::endl;

      exit (EXIT_FAILURE);
   }

   int BaseData::getTotalHeaderCount() const { return this->totalHeaderCount; }


   void BaseData::incrementHeaderCount() { (this->totalHeaderCount)++; }


   int BaseData::getDataLength() const { return this->dataLineLength; }


   void BaseData::setDataLength(int _length)
   {
      try {
         if (this->dataLineLength == 0) {
            /* This is the first time we are setting the data */
            this->dataLineLength = _length;
         }
         else if (this->dataLineLength == _length) {
            /* Our lengths match, all is well in the galaxy, do nothing */
         } else {
            /* Our lengths do not match, cannot compute data correctly
             * throw and end program
             * */
            throw DataLength();
         }

      } catch (DataLength &e) {
         errorPrint(e.what());
      }
   }


   std::string BaseData::getCurrentLine() const { return this->currentLine; }


   void BaseData::setCurrentLine(const std::string _currentLine)
   {
      if (!(_currentLine.empty())) {
         this->currentLine = _currentLine;
      }
   }


   int BaseData::getFileLineCount() const { return this->totalLineCount; }


   void BaseData::incrementFileLineCount() { (this->totalLineCount)++; }


   std::streampos BaseData::getCurrentFilePosition() const { return this->currentFilePos; }


   void BaseData::setCurrentFilePos(std::ifstream &f) { this->currentFilePos = f.tellg(); }


   std::string BaseData::getTitle() const { return this->title; }


   void BaseData::setTitle(const std::string &_title) 
   {
      try {
         if ( this->title.empty() ) { 
            this->title = _title; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         errorPrint(e.what());
      }
   }


   std::string BaseData::getTitleContainer(int &itr) const { return this->titleContainer[itr]; }


   void BaseData::setTitleContainer(const std::string &_sub)
   {
      try {
         for (int i = 0; i < this->getDataLength(); ++i) {
            if (this->titleContainer[i] == _sub) {
               throw DuplicateFound();
            }
         }
         /* if no exception is thrown insert the value */
         this->titleContainer.emplace_back(_sub);
      } catch(DuplicateFound &e) {
         errorPrint(e.what());
      }
   } 


   std::string BaseData::getCategory() const { return this->category; }


   void BaseData::setCategory(const std::string &_category) 
   { 
      try {
         if ( this->category.empty() ) { 
            this->category = _category; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         errorPrint(e.what());
      }
   }


   std::string BaseData::getCategoryContainer(int &itr) { return this->categoryContainer[itr]; }


   void BaseData::setCategoryContainer(const std::string &_sub)
   {
      this->categoryContainer.emplace_back(_sub);
   }


   std::string BaseData::getMaxMark() const { return this->maxMark; }


   void BaseData::setMaxMark(const std::string &_maxMark)
   {
      try {
         if ( this->maxMark.empty() ) { 
            this->maxMark = _maxMark;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         errorPrint(e.what());
      }
   }


   float BaseData::getMaxMarkContainer(int &itr) { return this->maxMarkContainer[itr]; }


   void BaseData::setMaxMarkContainer(std::string &_sub)
   {
      try {
         if (isDigits(_sub)) {
            float temp = stringTofloat(_sub);
            this->maxMarkContainer.emplace_back(temp);
         }
         else { throw FailStringFloatConversion(); }

      } catch (FailStringFloatConversion &e) {
         errorPrint(e.what());
      }
   }


   std::string BaseData::getWeight() const { return this->weight; }


   void BaseData::setWeight(const std::string &_weight)
   {
      try {
         if ( this->weight.empty() ) { 
            this->weight = _weight;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         errorPrint(e.what());
      }
   }


   float BaseData::getWeightContainer(int &itr) { return this->weightContainer[itr]; }


   void BaseData::setWeightContainer(std::string &_sub)
   {
      float total;
      try {
         if (isDigits(_sub)) {
            float temp = stringTofloat(_sub);
            this->weightContainer.emplace_back(temp);
         }
         else { throw FailStringFloatConversion(); }

         std::size_t tempCompare = this->getDataLength();
         if (this->weightContainer.size() == tempCompare) {
            /* if the container size is equal to the line length
             * we know all grades have been read in, which means
             * it is safe to sum them all up and test the total
             * */
            std::vector<float> Fvec = this->weightContainer;
            total = vecSummation(Fvec);
            if (total != 100) { 
               throw WeightSummation();
            }
         }
      } catch (FailStringFloatConversion &e) {
         errorPrint(e.what());
      } catch (WeightSummation &e) {
         errorPrint(e.what());
      }
   }


   void BaseData::printBaseObject(void)
   {
      /* get the title */ 
      std::cout << this->getTitle() << " : ";
      for (int i = 0; i < this->getDataLength(); ++i) {
         std::cout << this->getTitleContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the category */ 
      std::cout << this->getCategory() << " : ";
      for (int i = 0; i < this->getDataLength(); ++i) {
         std::cout << this->getCategoryContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the maxMark */ 
      std::cout << this->getMaxMark() << " : ";
      for (int i = 0; i < this->getDataLength(); ++i) {
         std::cout << this->getMaxMarkContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the weight */ 
      std::cout << this->getWeight() << " : ";
      for (int i = 0; i < this->getDataLength(); ++i) {
         std::cout << this->getWeightContainer(i) << " "; 
      }
      std::cout << std::endl;
   }


   bool BaseData::loadBaseData(const std::string &file)
   {
      try {
         std::ifstream inFile(file);
         std::string line("");
         if (inFile.good()) {
            while (std::getline(inFile, line)) {
               /* record the current line for error purposes */
               this->setCurrentLine(line);
               this->stripComments(line);

               std::string keyword("");
               std::string sTemp("");
               std::stringstream ss(line);

               ss >> keyword;
               if (keyword == TITLE) {
                  this->setTitle(keyword);
                  this->incrementHeaderCount();
                  int i = 0;
                  while(ss >> sTemp) {
                     this->setTitleContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setDataLength(i);
               }

               else if (keyword == CATEGORY) {
                  this->setCategory(keyword);
                  this->incrementHeaderCount();
                  int i = 0;
                  while(ss >> sTemp) {
                     this->setCategoryContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setDataLength(i);
               }

               else if (keyword == MAXMARK) {
                  this->setMaxMark(keyword);
                  this->incrementHeaderCount();
                  int i = 0;
                  while(ss >> sTemp) {
                     this->setMaxMarkContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setDataLength(i);
               }

               else if (keyword == WEIGHT) {
                  this->setWeight(keyword);
                  this->incrementHeaderCount();
                  int i = 0;
                  while(ss >> sTemp) {
                     this->setWeightContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setDataLength(i);
               }
               /* we read a line so increment the count */
               this->incrementFileLineCount();

               /* HEADER_MAX is the only defined constant, and only variable
                * that would be called "hard-coded", but as files should have
                * some standardization, I figured it would be alright to have
                * this comparison to be 
                * */
               if (this->getTotalHeaderCount() == HEADER_MAX) {
                  this->setCurrentFilePos(inFile);
                  inFile.close();
                  return true;
               }
            }
         } else { throw std::logic_error("*** Can't Open File: "); }
      } catch (std::logic_error &e) {
         std::cerr << e.what() << file << std::endl;;
      }
      return true;
   }


   void BaseData::stripComments(std::string &line)
   {
      std::size_t found = line.find(COMM);
      if (found != std::string::npos) {
         line.erase(found, std::string::npos);
      }
   }


   bool BaseData::isDigits(std::string &s)
   {
      return s.find_first_not_of("0123456789.") == std::string::npos; 
   }


   float BaseData::stringTofloat(const std::string &s)
   {
      float tempconvert = 0;
      std::stringstream streamVar(s);
      try {
         streamVar >> tempconvert;
         if (streamVar.fail()) {
            throw StreamConversionFailure();
         }
      } catch (StreamConversionFailure &e) {
         errorPrint(e.what());
      }
      // will only return upon success
      return tempconvert;
   }


   float BaseData::vecSummation(std::vector<float> &s)
   {
      float tempFinalGrade = 0;
      return accumulate(s.begin(), s.end(), tempFinalGrade);
   }
};
