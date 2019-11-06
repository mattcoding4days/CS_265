#include "hdr/base.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraderApplication
{
   /* XXX: Documentation
    * */
   BaseData::BaseData(void)
      : title("")
      , titleContainer({""})
      , category("")
      , categoryContainer({""})
      , maxMark("")
      , maxMarkContainer({0})
      , weight("")
      , weightContainer({0})
   { }

   /* XXX: Documentation
    * Accessor:  */
   int BaseData::getBaseContainerSize() const
   {
      return this->baseContainerSize;
   }

   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getTitle() const
   { 
      return this->title;
   }
   void BaseData::setTitle(const std::string &_title)
   { 
      this->title = _title;
   }


   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getTitleContainer(const int &itr) const 
   { 
      return this->titleContainer[itr];
   }
   void BaseData::setTitleContainer(const int &itr, const std::string &_sub)
   { 
      this->titleContainer[itr] = _sub;
   } 


   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getCategory() const
   {
      return this->category;
   }
   void BaseData::setCategory(const std::string &_category)
   {
      this->category = _category;
   }


   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getCategoryContainer(const int &itr)
   {
      return this->categoryContainer[itr];
   }
   void BaseData::setCategoryContainer(const int &itr, const std::string &_sub)
   {
      this->categoryContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getMaxMark() const
   {
      return this->maxMark;
   }
   void BaseData::setMaxMark(const std::string &_maxMark)
   {
      this->maxMark = _maxMark;
   }

   
   /* XXX: Documentation
    * Accessor:  */
   float BaseData::getMaxMarkContainer(const int &itr)
   {
      return this->maxMarkContainer[itr];
   }
   void BaseData::setMaxMarkContainer(const int &itr, const float &_sub)
   {
      this->maxMarkContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * Accessor:  */
   std::string BaseData::getWeight() const
   {
      return this->weight;
   }
   void BaseData::setWeight(const std::string &_weight)
   {
      this->weight = _weight;
   }

   /* XXX: Documentation
    * Accessor:  */
   float BaseData::getWeightContainer(const int &itr)
   {
      return this->weightContainer[itr];
   }
   void BaseData::setWeightContainer(const int &itr, const float &_sub)
   {
      this->weightContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * */
   void BaseData::printBaseStringPair(const std::string &fTemp,
             std::array<std::string, baseContainerSize> &sTemp)
   {
      std::cout << fTemp << " : ";
      for ( int i = 0; i < this->getBaseContainerSize(); ++i )
      {
         std::cout << sTemp[i] << " ";
      }
      std::cout << std::endl;
   }

   
   /* XXX: Documentation
    * */
   void BaseData::printBaseStringFloat(const std::string &fTemp,
             std::array<float, baseContainerSize> &sTemp)
   {
      std::cout << fTemp << " : ";
      for ( int i = 0; i < this->getBaseContainerSize(); ++i )
      {
         std::cout << sTemp[i] << " ";
      }
      std::cout << std::endl;
   }


   /* XXX: Documentation
    * Load only preliminary data from file:  */
   bool BaseData::loadBaseData(const std::string &file)
   {
      std::ifstream inFile(file);
      std::string line("");
      if (inFile.good())
      {
         while (std::getline(inFile, line))
         {
            if (!(line.empty()))
            {
               char firstC = line[0];
               std::stringstream ss(line);
               float fTemp = 0;
               std::string sTemp("");
               switch(firstC)
               {
                  case TITLE :
                  ss >> sTemp;
                  this->setTitle(sTemp);
                  for (int i = 0; i < this->getBaseContainerSize(); ++i)
                  {
                     ss >> sTemp;
                     this->setTitleContainer(i, sTemp);
                  }
                  break;

                  case CATEGORY :
                  ss >> sTemp;
                  this->setCategory(sTemp);
                  for (int i = 0; i < this->getBaseContainerSize(); ++i)
                  {
                     ss >> sTemp;
                     this->setCategoryContainer(i, sTemp);
                  }
                  break;

                  case MAXMARK :
                  ss >> sTemp;
                  this->setMaxMark(sTemp);
                  for (int i = 0; i < this->getBaseContainerSize(); ++i)
                  {
                     ss >> fTemp;
                     this->setMaxMarkContainer(i, fTemp);
                  }
                  break;

                  case WEIGHT :
                  ss >> sTemp;
                  this->setWeight(sTemp);
                  for (int i = 0; i < this->getBaseContainerSize(); ++i)
                  {
                     ss >> fTemp;
                     this->setWeightContainer(i, fTemp);
                  }
                  break;
               }
            }
         }
      }
      else {
         std::cerr << "Error opening " << file << std::endl;
      }

      inFile.close();
      return true;
   }
};
