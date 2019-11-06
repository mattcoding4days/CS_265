#ifndef BASE_H
#define BASE_H

#include "settings.h"
#include <array>

namespace GraderApplication
{
   class BaseData
   {
   private:
      static const int baseContainerSize = LEN;
      std::string title;
      std::array <std::string, baseContainerSize> titleContainer;
      std::string category;
      std::array <std::string, baseContainerSize> categoryContainer;
      std::string maxMark;
      std::array <float, baseContainerSize> maxMarkContainer;
      std::string weight;
      std::array <float, baseContainerSize> weightContainer;
   public:
      /* XXX: Documentation
       * */
      BaseData(void);

      int getBaseContainerSize() const;

      /* XXX: Documentation
       * Accessor:  */
      std::string getTitle() const; 
      void setTitle(const std::string &); 


      /* XXX: Documentation
       * Accessor:  */
      std::string getTitleContainer(const int &) const;
      void setTitleContainer(const int &, const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      std::string getCategory() const;
      void setCategory(const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      std::string getCategoryContainer(const int &);
      void setCategoryContainer(const int &, const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      std::string getMaxMark() const;
      void setMaxMark(const std::string &);

      
      /* XXX: Documentation
       * Accessor:  */
      float getMaxMarkContainer(const int &);
      void setMaxMarkContainer(const int &, const float &);


      /* XXX: Documentation
       * Accessor:  */
      std::string getWeight() const;
      void setWeight(const std::string &);

      /* XXX: Documentation
       * Accessor:  */
      float getWeightContainer(const int &);
      void setWeightContainer(const int &, const float &);
      


      /* XXX: Documentation
       * */
      void printBaseStringPair(const std::string &, std::array<std::string, LEN> &);

      
      /* XXX: Documentation
       * */
      void printBaseStringFloat(const std::string &, std::array<float, LEN> &);


      /* XXX: Documentation
       * Load only preliminary data from file:  */
      bool loadBaseData(const std::string &);
      
   };
};

#endif
