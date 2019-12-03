#ifndef BASE_H
#define BASE_H

#include "settings.h"
#include <array>

namespace GraderApplication
{
   /* BaseData is responsible for all prelim data
    * found before the students themselves.
    * constisting of mainly getters and setters
    * so it is easy to access the private members
    * through the derived class Grader
    * */
   class BaseData
   {
   private:
      /* intitialzing an in class consant, so I wont have to
       * change LEN in a bunch of different positions if I want
       * want to modify it or use something else
       * */
      static const int maxLength = LEN;
      std::string title;
      std::array <std::string, maxLength> titleContainer;
      std::string category;
      std::array <std::string, maxLength> categoryContainer;
      std::string maxMark;
      std::array <float, maxLength> maxMarkContainer;
      std::string weight;
      std::array <float, maxLength> weightContainer;
   public:
      /* XXX: Documentation
       * Simple default constructor
       * */
      BaseData(void);

      /* XXX: Documentation
       * Accessor: getter for max length
       * */
      int getMaxLength() const; 


      /* XXX: Documentation
       * Accessor: getter and setter for title
       * */
      std::string getTitle() const; 
      void setTitle(const std::string &); 


      /* XXX: Documentation
       * Accessor: getter and setter for title container
       * */
      std::string getTitleContainer(int &) const;
      void setTitleContainer(const int &, const std::string &);


      /* XXX: Documentation
       * Accessor: getter and setter for category
       * */
      std::string getCategory() const;
      void setCategory(const std::string &);


      /* XXX: Documentation
       * Accessor: getter and setter for category container
       * */
      std::string getCategoryContainer(int &);
      void setCategoryContainer(const int &, const std::string &);


      /* XXX: Documentation
       * Accessor: getter and setter for maxmark 
       * */
      std::string getMaxMark() const;
      void setMaxMark(const std::string &);

      
      /* XXX: Documentation
       * Accessor:  getter and setter for maxmark container
       * */
      float getMaxMarkContainer(int &);
      void setMaxMarkContainer(const int &, const float &);


      /* XXX: Documentation
       * Accessor: getter and setter for weight
       * */
      std::string getWeight() const;
      void setWeight(const std::string &);

      /* XXX: Documentation
       * Accessor: getter and setter for weight container
       * */
      float getWeightContainer(int &);
      void setWeightContainer(const int &, const float &);
      
      
      /* XXX: Documentation
       * Mainly for debugging and testing purposes,
       * prints the entire object after data is parsed
       * and read in
       * */
      void printBaseObject(void);


      /* XXX: Documentation
       * Load only preliminary data from file:
       * reads data based on first character matches
       * from a predefined enumerator in settings.h
       * */
      bool loadBaseData(const std::string &);
      
   };
};

#endif
