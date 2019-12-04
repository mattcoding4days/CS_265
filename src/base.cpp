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
      : headerLength(0)
      , totalLineCount(0)
      , title("")
      , titleContainer({""})
      , category("")
      , categoryContainer({""})
      , maxMark("")
      , maxMarkContainer({0})
      , weight("")
      , weightContainer({0})

   { /* Not needed */  }


   int BaseData::getTotalHeaderCount() const { return this->totalHeaderCount; }


   int BaseData::getHeaderLength() const { return this->headerLength; }
   

   void BaseData::setHeaderLength(const int _length)
   {
      /* set an acceptable inclusive bound */
      if (_length > 0 && _length < 20) {
         this->headerLength = _length;
      } else {
         std::cerr << "Header length out of bounds\n"; 
      }
   }


   int BaseData::getCurrentLineCount() const { return this->totalLineCount; }


   void BaseData::setCurrentLineCount(const int _count)
   {
      /* set an acceptable inclusive bound */
      if (_count >= 0 && _count <= 200) {
         this->totalLineCount += _count;
      } else {
         std::cerr << "File is too large\n"; 
      }
   }


   std::string BaseData::getTitle() const { return this->title; }


   void BaseData::setTitle(const std::string &_title) 
   {
      try {
         if ( this->getTitle().empty() ) { 
            this->title = _title; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _title << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   std::string BaseData::getTitleContainer(int &itr) const { return this->titleContainer[itr]; }


   void BaseData::setTitleContainer(const std::string &_sub)
   {
      try {
         for (int i = 0; i < this->getHeaderLength(); ++i) {
            if (this->titleContainer[i] == _sub) {
               throw DuplicateFound();
            }
         }
      } catch(DuplicateFound &e) {
         std::cerr << e.what() << _sub << " <- already in title container\n";
         exit(EXIT_FAILURE);
      }
      /* if no exception is thrown insert the value */
      this->titleContainer.emplace_back(_sub);
   } 


   std::string BaseData::getCategory() const { return this->category; }


   void BaseData::setCategory(const std::string &_category) 
   { 
      try {
         if ( this->getCategory().empty() ) { 
            this->category = _category; 
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _category << " is already set" << std::endl;
         exit (EXIT_FAILURE);
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
         if ( this->getMaxMark().empty() ) { 
            this->maxMark = _maxMark;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _maxMark << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   float BaseData::getMaxMarkContainer(int &itr) { return this->maxMarkContainer[itr]; }


   void BaseData::setMaxMarkContainer(const float &_sub)
   {
      this->maxMarkContainer.emplace_back(_sub);
   }


   std::string BaseData::getWeight() const { return this->weight; }


   void BaseData::setWeight(const std::string &_weight)
   {
      try {
         if ( this->getWeight().empty() ) { 
            this->weight = _weight;
         }
         else {
            throw DuplicateFound();
         }
      } catch (DuplicateFound &e) {
         std::cerr << e.what() << _weight << " is already set" << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   float BaseData::getWeightContainer(int &itr) { return this->weightContainer[itr]; }


   /*FIXME: Think of a better way to check for summation miscalculation */
   void BaseData::setWeightContainer(const float &_sub)
   {
      try {
         /* Make sure weights do not add up above 100 
          * or are negative numbers going below 0
          * */
         float summation = 0;
         accumulate(this->weightContainer.begin(),
               this->weightContainer.end(), summation);

         if ( (summation >= 100) || (summation < 0) || (summation + _sub > 100) ) {
            throw WeightSummation();
         }
         else {
            this->weightContainer.emplace_back(_sub);
         }
      } catch(WeightSummation &e) {
         std::cerr << e.what() << std::endl;
         exit (EXIT_FAILURE);
      }
   }


   void BaseData::printBaseObject(void)
   {
      /* get the title */ 
      std::cout << this->getTitle() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getTitleContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the category */ 
      std::cout << this->getCategory() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getCategoryContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the maxMark */ 
      std::cout << this->getMaxMark() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getMaxMarkContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the weight */ 
      std::cout << this->getWeight() << " : ";
      for (int i = 0; i < this->getHeaderLength(); ++i) {
         std::cout << this->getWeightContainer(i) << " "; 
      }
      std::cout << std::endl;
   }


   bool BaseData::loadBaseData(const std::string &file)
   {
      std::ifstream inFile(file);
      std::string line("");
      if (inFile.good()) {
         while (std::getline(inFile, line)) {
            if (!(line.empty())) {
               std::string keyword("");
               std::string sTemp("");
               std::stringstream ss(line);
               ss >> keyword;

               if (keyword == TITLE) {
                  this->setTitle(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> sTemp;
                     this->setTitleContainer(sTemp);
                  }
               }
               else if (keyword == CATEGORY) {
                  this->setCategory(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> sTemp;
                     this->setCategoryContainer(sTemp);
                  }
               }
               else if (keyword == MAXMARK) {
                  this->setMaxMark(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     float fTemp = 0;
                     ss >> fTemp;
                     this->setMaxMarkContainer(fTemp);
                  }
               }
               else if (keyword == WEIGHT) {
                  this->setWeight(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     float fTemp = 0;
                     ss >> fTemp;
                     this->setWeightContainer(fTemp);
                  }
               } 
            }
         }
      }
      inFile.close();
      return true;
   }
   
   void BaseData::stripComments(std::string &line)
   {
      std::size_t found = line.find(COMM);
      if (found != std::string::npos) {
         line.erase(found, std::string::npos);
      } else {
         std::cout << "No comment found in this line" << std::endl;
      }
   }

   int BaseData::findEvaluationLenth(std::string &)
   {
      return 1;
   }
};
