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
   inline std::string BaseData::getTitle() const
   { 
      return this->title;
   }
   inline void BaseData::setTitle(const std::string &_title)
   { 
      this->title = _title;
   }


   /* XXX: Documentation
    * Accessor:  */
   inline std::string BaseData::getTitleContainer(const int &itr) const 
   { 
      return this->titleContainer[itr];
   }
   inline void BaseData::setTitleContainer(const u_int &itr, const std::string &_sub)
   { 
      this->titleContainer[itr] = _sub;
   } 


   /* XXX: Documentation
    * Accessor:  */
   inline std::string BaseData::getCategory() const
   {
      return this->category;
   }
   inline void BaseData::setCategory(const std::string &_category)
   {
      this->category = _category;
   }


   /* XXX: Documentation
    * Accessor:  */
   inline std::string BaseData::getCategoryContainer(const int &itr)
   {
      return this->categoryContainer[itr];
   }
   inline void BaseData::setCategoryContainer(const u_int &itr, const std::string &_sub)
   {
      this->categoryContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * Accessor:  */
   inline std::string BaseData::getMaxMark() const
   {
      return this->maxMark;
   }
   inline void BaseData::setMaxMark(const std::string &_maxMark)
   {
      this->maxMark = _maxMark;
   }

   
   /* XXX: Documentation
    * Accessor:  */
   inline float BaseData::getMaxMarkContainer(const int &itr)
   {
      return this->maxMarkContainer[itr];
   }
   inline void BaseData::setMaxMarkContainer(const u_int &itr, const float &_sub)
   {
      this->maxMarkContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * Accessor:  */
   inline std::string BaseData::getWeight() const
   {
      return this->weight;
   }
   inline void BaseData::setWeight(const std::string &_weight)
   {
      this->weight = _weight;
   }

   /* XXX: Documentation
    * Accessor:  */
   inline float BaseData::getWeightContainer(const int &itr)
   {
      return this->weightContainer[itr];
   }
   inline void BaseData::setWeightContainer(const u_int &itr, const float &_sub)
   {
      this->weightContainer[itr] = _sub;
   }


   /* XXX: Documentation
    * */
   void BaseData::printBaseStringPair(const std::string &fTemp, std::array<std::string, LEN> &sTemp)
   {
      std::cout << fTemp << " : ";
      for ( int i = 0; i < LEN; ++i )
      {
         std::cout << sTemp[i] << " ";
      }
      std::cout << std::endl;
   }

   
   /* XXX: Documentation
    * */
   void BaseData::printBaseStringFloat(const std::string &fTemp, std::array<float, LEN> &sTemp)
   {
      std::cout << fTemp << " : ";
      for ( int i = 0; i < LEN; ++i )
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
                  for (u_int i = 0; i < LEN; ++i)
                  {
                     ss >> sTemp;
                     this->setTitleContainer(i, sTemp);
                  }
                  break;

                  case CATEGORY :
                  ss >> sTemp;
                  this->setCategory(sTemp);
                  for (u_int i = 0; i < LEN; ++i)
                  {
                     ss >> sTemp;
                     this->setCategoryContainer(i, sTemp);
                  }
                  break;

                  case MAXMARK :
                  ss >> sTemp;
                  this->setMaxMark(sTemp);
                  for (u_int i = 0; i < LEN; ++i)
                  {
                     ss >> fTemp;
                     this->setMaxMarkContainer(i, fTemp);
                  }
                  break;

                  case WEIGHT :
                  ss >> sTemp;
                  this->setWeight(sTemp);
                  for (u_int i = 0; i < LEN; ++i)
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
