#ifndef BASE_H
#define BASE_H

#include "settings.h"
#include <array>
#include <vector>

namespace GraderApplication {
   /* BaseData is responsible for all prelim data
    * found before the students themselves.
    * constisting of mainly getters and setters
    * so it is easy to access the private members
    * through the derived class Grader
    * */
   class BaseData {
   private:
      static const int totalHeaderCount = HEADER_MAX;
      int headerLength;
      int totalLineCount;
      std::string title;
      std::vector <std::string> titleContainer;
      std::string category;
      std::vector <std::string> categoryContainer;
      std::string maxMark;
      std::vector <float> maxMarkContainer;
      std::string weight;
      std::vector <float> weightContainer;

   public:
      /* XXX: Documentation
       * Default constructor
       * */
      BaseData(void);
      
      /* XXX: Documentation
       * Return the total header count of 4
       * defined in settings.h
       * */
      int getTotalHeaderCount() const;
      
      /* XXX: Documentation
       * Accessor: getter and setter for length of header data
       * */
      int getHeaderLength() const; 
      void setHeaderLength(const int);

      /* XXX: Documentation
       * Accessor: getter and setter for totalLineCount 
       * */
      int getCurrentLineCount() const;
      void setCurrentLineCount(const int);
      

      /* XXX: Documentation
       * Accessor: getter and setter for title
       * */
      std::string getTitle() const; 
      void setTitle(const std::string &); 

      /* XXX: Documentation
       * Accessor: getter and setter for title container
       * */
      std::string getTitleContainer(int &) const;
      void setTitleContainer(const std::string &);

      /* XXX: Documentation
       * Accessor: getter and setter for category
       * */
      std::string getCategory() const;
      void setCategory(const std::string &);

      /* XXX: Documentation
       * Accessor: getter and setter for category container
       * */
      std::string getCategoryContainer(int &);
      void setCategoryContainer(const std::string &);

      /* XXX: Documentation
       * Accessor: getter and setter for maxmark 
       * */
      std::string getMaxMark() const;
      void setMaxMark(const std::string &);

      /* XXX: Documentation
       * Accessor:  getter and setter for maxmark container
       * */
      float getMaxMarkContainer(int &);
      void setMaxMarkContainer(const float &);

      /* XXX: Documentation
       * Accessor: getter and setter for weight
       * */
      std::string getWeight() const;
      void setWeight(const std::string &);

      /* XXX: Documentation
       * Accessor: getter and setter for weight container
       * */
      float getWeightContainer(int &);
      void setWeightContainer(const float &);
      
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
      
      /* XXX: Documentation
       * Strip all comments from the line that is passed
       * */
      void stripComments(std::string &);

      /* XXX: Documentation
       * Find the length of the header data
       * */
      int findEvaluationLenth(std::string &);

   };
};

#endif
