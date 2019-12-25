/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/evaluation.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

namespace GraderApplication
{
   EvaluationData::EvaluationData(void)
      : dataFile("")
      , totalHeaderCount(0)
      , dataLineLength(0)
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

   void EvaluationData::errorPrint(const char *a)
   {
      std::cerr << "\nERROR: " << a << std::endl;
      std::cerr << "\nOffending line number: "
                << this->getFileLineCount() << std::endl;
      std::cerr << "Offending content: " 
                << this->getCurrentLine() << std::endl;

      exit (EXIT_FAILURE);
   }

   
   int EvaluationData::totalEvaluationCount() const { return this->totalHeaderCount; }


   void EvaluationData::incrementHeaderCount() { (this->totalHeaderCount)++; }


   int EvaluationData::evaluationDataLength() const { return this->dataLineLength; }


   void EvaluationData::setEvaluationDataLength(int _length)
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


   std::string EvaluationData::currentReadLine() const { return this->currentLine; }


   void EvaluationData::setCurrentReadLine(const std::string _currentLine)
   {
      if (!(_currentLine.empty())) {
         this->currentLine = _currentLine;
      }
   }


   int EvaluationData::fileLineCount() const { return this->totalLineCount; }


   void EvaluationData::incrementFileLineCount(int _x)
   {
      this->totalLineCount += _x;
   }


   std::streampos EvaluationData::currentFilePosition() const { return this->currentFilePos; }


   void EvaluationData::setCurrentFilePos(std::ifstream &f) { this->currentFilePos = f.tellg(); }


   std::string EvaluationData::evaluationTitle() const { return this->title; }


   void EvaluationData::setEvaluationTitle(const std::string &_title)
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


   std::string EvaluationData::evaluationTitleContainer(int &itr) const { return this->titleContainer[itr]; }


   void EvaluationData::setEvaluationTitleContainer(const std::string &_sub)
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


   std::string EvaluationData::getCategory() const { return this->category; }


   void EvaluationData::setCategory(const std::string &_category)
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


   std::string EvaluationData::getCategoryContainer(int &itr) { return this->categoryContainer[itr]; }


   void EvaluationData::setCategoryContainer(const std::string &_sub)
   {
      /* Nothing much to check here */
      this->categoryContainer.emplace_back(_sub);

   }


   std::string EvaluationData::getMaxMark() const { return this->maxMark; }


   void EvaluationData::setMaxMark(const std::string &_maxMark)
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


   float EvaluationData::getMaxMarkContainer(std::size_t itr) { return this->maxMarkContainer[itr]; }


   void EvaluationData::setMaxMarkContainer(std::string &_sub)
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


   std::string EvaluationData::getWeight() const { return this->weight; }


   void EvaluationData::setWeight(const std::string &_weight)
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


   float EvaluationData::getWeightContainer(int &itr) { return this->weightContainer[itr]; }


   void EvaluationData::setWeightContainer(std::string &_sub)
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


   void EvaluationData::loadEvaluationData(const std::string &file)
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
               this->incrementFileLineCount(1);

               if (this->getTotalHeaderCount() == HEADER_MAX) {
                  this->setCurrentFilePos(inFile);
                  inFile.close();
               }
            }
         } else { throw std::logic_error("*** File Not Found: "); }
      } catch (std::logic_error &e) {
         std::cerr << e.what() << file << std::endl;
      }
   }
};
