/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include "../hdr/base.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraderApplication
{
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
   { }

   int BaseData::getTotalHeaderCount() const
   {
      return this->totalHeaderCount;
   }

   int BaseData::getHeaderLength() const
   {
      return this->headerLength;
   }
   
   void BaseData::setHeaderLength(const int _length)
   {
      /* set an acceptable inclusive bound */
      if (_length > 0 && _length < 20) {
         this->headerLength = _length;
      } else {
         std::cerr << "Header length out of bounds\n"; 
      }
   }

   int BaseData::getCurrentLineCount() const
   {
      return this->totalLineCount;
   }

   void BaseData::setCurrentLineCount(const int _count)
   {
      /* set an acceptable inclusive bound */
      if (_count >= 0 && _count <= 200) {
         this->totalLineCount += _count;
      } else {
         std::cerr << "File is too large\n"; 
      }
   }

   std::string BaseData::getTitle() const
   { 
      return this->title;
   }

   void BaseData::setTitle(const std::string &_title)
   {
      this->title = _title;
   }

   std::string BaseData::getTitleContainer(int &itr) const 
   { 
      return this->titleContainer[itr];
   }

   void BaseData::setTitleContainer(const int &itr, const std::string &_sub)
   { 
      this->titleContainer[itr] = _sub;
   } 

   std::string BaseData::getCategory() const
   {
      return this->category;
   }

   void BaseData::setCategory(const std::string &_category)
   {
      this->category = _category;
   }

   std::string BaseData::getCategoryContainer(int &itr)
   {
      return this->categoryContainer[itr];
   }

   void BaseData::setCategoryContainer(const int &itr, const std::string &_sub)
   {
      this->categoryContainer[itr] = _sub;
   }

   std::string BaseData::getMaxMark() const
   {
      return this->maxMark;
   }

   void BaseData::setMaxMark(const std::string &_maxMark)
   {
      this->maxMark = _maxMark;
   }

   float BaseData::getMaxMarkContainer(int &itr)
   {
      return this->maxMarkContainer[itr];
   }

   void BaseData::setMaxMarkContainer(const int &itr, const float &_sub)
   {
      this->maxMarkContainer[itr] = _sub;
   }

   std::string BaseData::getWeight() const
   {
      return this->weight;
   }

   void BaseData::setWeight(const std::string &_weight)
   {
      this->weight = _weight;
   }


   float BaseData::getWeightContainer(int &itr)
   {
      return this->weightContainer[itr];
   }

   void BaseData::setWeightContainer(const int &itr, const float &_sub)
   {
      this->weightContainer[itr] = _sub;
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
               float fTemp = 0;
               std::stringstream ss(line);
               ss >> keyword;

               if (keyword == TITLE) {
                  this->setTitle(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> sTemp;
                     this->setTitleContainer(i, sTemp);
                  }
               }
               else if (keyword == CATEGORY) {
                  this->setCategory(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> sTemp;
                     this->setCategoryContainer(i, sTemp);
                  }
               }
               else if (keyword == MAXMARK) {
                  this->setMaxMark(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> fTemp;
                     this->setMaxMarkContainer(i, fTemp);
                  }
               }
               else if (keyword == WEIGHT) {
                  this->setWeight(keyword);
                  for (int i = 0; i < this->getHeaderLength(); ++i) {
                     ss >> fTemp;
                     this->setWeightContainer(i, fTemp);
                  }
               } 
               else {
                  std::cerr << "KeyWord: " << keyword << " not found" << std::endl;
               }
            }
         }
      }
      inFile.close();
      return true;
   }
};
