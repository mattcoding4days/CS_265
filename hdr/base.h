#ifndef BASE_H
#define BASE_H

#include "utillity.h"
#include <fstream>
#include <vector>

namespace GraderApplication
{
   /* XXX: Documentation
    * BaseData is responsible for all prelim data
    * it also houses alot of base functionality for 
    * student and grader which derive from it.
    * BaseData adopts the getter setter strategy
    * so the derived classes can easily use alot of
    * the core functionality built in. It also provides
    * a standardized way to access attributes accross the
    * program, as well as the setters serving as the funnel
    * for error checking, which makes domain constraints on 
    * the methods themselves simple and concise
    * */
   class BaseData : public Utillity
   {
      private:
         std::string dataFile;
         int totalHeaderCount;
         int dataLineLength;
         int totalLineCount;
         std::string currentLine;
         std::streampos currentFilePos;
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
          * error print will in all output from 
          * exceptions for BaseData class only
          * */
         void errorPrint (const char *);

         /* XXX: Documentation
          * Return the total header count
          * This will be used to compare against
          * the HEADER_MAX macro of 4 so we know
          * when the max has been read in
          * */
         int getTotalHeaderCount() const;
         void incrementHeaderCount();

         /* XXX: Documentation
          * Accessor: getter and setter
          * For the actual length of the evaluation data
          * This is only what is stored in the vector
          * not the datas associated Key
          * */
         int getDataLength() const; 
         void setDataLength(int);

         /* XXX: Documentation
          * Accessor: getter and setter
          * stores the current line we read in,
          * this is mainly for the error reporing
          * */
         std::string getCurrentLine() const;
         void setCurrentLine(const std::string);

         /* XXX: Documentation
          * Accessor: getter and setter
          * This is to track line errors
          * */
         int getFileLineCount() const;
         void incrementFileLineCount(int);

         /* XXX: Documentation
          * Accessor: getter and setter
          * This is so the file position can be remembered
          * so the file can be closed and reopended by different
          * methods without have to read from the beginning of the file
          * */
         std::streampos getCurrentFilePosition() const;
         void setCurrentFilePos(std::ifstream &);

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
         float getMaxMarkContainer(std::size_t);
         void setMaxMarkContainer(std::string &);

         /* XXX: Documentation
          * Accessor: getter and setter for weight
          * */
         std::string getWeight() const;
         void setWeight(const std::string &);

         /* XXX: Documentation
          * Accessor: getter and setter for weight container
          * */
         float getWeightContainer(int &);
         void setWeightContainer(std::string &);

         /* XXX: Documentation
          * Load only preliminary data from file:
          * reads data based on first character matches
          * from a predefined enumerator in settings.h
          * */
         void loadBaseData(const std::string &);
   };
};

#endif
