#ifndef BASE_H
#define BASE_H

#include "settings.h"
#include <fstream>
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
          * exceptions
          * */
         virtual void errorPrint (const char *);

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
         void incrementFileLineCount();

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
          * search whole or decimal string representation
          * of a number, and return true if there is only
          * digits
          * */
         virtual bool isDigits(std::string &);

         /* XXX: Documentation
          * convert a string to a float with out the 
          * truncating limitations of stof
          * */
         float stringTofloat(const std::string &);

         /* XXX: Documentation
          * Summ all elements in array
          * */
         float vecSummation(std::vector<float> &);
   };
};

#endif
