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
      inline std::string getTitle() const; 
      inline void setTitle(const std::string &); 


      /* XXX: Documentation
       * Accessor:  */
      inline std::string getTitleContainer(const int &) const;
      inline void setTitleContainer(const u_int &, const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      inline std::string getCategory() const;
      inline void setCategory(const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      inline std::string getCategoryContainer(const int &);
      inline void setCategoryContainer(const u_int &, const std::string &);


      /* XXX: Documentation
       * Accessor:  */
      inline std::string getMaxMark() const;
      inline void setMaxMark(const std::string &);

      
      /* XXX: Documentation
       * Accessor:  */
      inline float getMaxMarkContainer(const int &);
      inline void setMaxMarkContainer(const u_int &, const float &);


      /* XXX: Documentation
       * Accessor:  */
      inline std::string getWeight() const;
      inline void setWeight(const std::string &);

      /* XXX: Documentation
       * Accessor:  */
      inline float getWeightContainer(const int &);
      inline void setWeightContainer(const u_int &, const float &);


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
