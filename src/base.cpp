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
      : title("")
      , titleContainer({""})
      , category("")
      , categoryContainer({""})
      , maxMark("")
      , maxMarkContainer({0})
      , weight("")
      , weightContainer({0})
   { }

   int BaseData::getMaxLength() const
   {
      return this->maxLength;
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
      for (int i = 0; i < this->getMaxLength(); ++i)
      {
         std::cout << this->getTitleContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the category */ 
      std::cout << this->getCategory() << " : ";
      for (int i = 0; i < this->getMaxLength(); ++i)
      {
         std::cout << this->getCategoryContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the maxMark */ 
      std::cout << this->getMaxMark() << " : ";
      for (int i = 0; i < this->getMaxLength(); ++i)
      {
         std::cout << this->getMaxMarkContainer(i) << " "; 
      }
      std::cout << std::endl;

      /* get the weight */ 
      std::cout << this->getWeight() << " : ";
      for (int i = 0; i < this->getMaxLength(); ++i)
      {
         std::cout << this->getWeightContainer(i) << " "; 
      }
      std::cout << std::endl;
   }


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
                  for (int i = 0; i < this->getMaxLength(); ++i)
                  {
                     ss >> sTemp;
                     this->setTitleContainer(i, sTemp);
                  }
                  break;

                  case CATEGORY :
                  ss >> sTemp;
                  this->setCategory(sTemp);
                  for (int i = 0; i < this->getMaxLength(); ++i)
                  {
                     ss >> sTemp;
                     this->setCategoryContainer(i, sTemp);
                  }
                  break;

                  case MAXMARK :
                  ss >> sTemp;
                  this->setMaxMark(sTemp);
                  for (int i = 0; i < this->getMaxLength(); ++i)
                  {
                     ss >> fTemp;
                     this->setMaxMarkContainer(i, fTemp);
                  }
                  break;

                  case WEIGHT :
                  ss >> sTemp;
                  this->setWeight(sTemp);
                  for (int i = 0; i < this->getMaxLength(); ++i)
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
