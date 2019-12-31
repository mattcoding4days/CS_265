#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include <fstream>
#include <vector>
#include "utillity.hpp"


namespace GraderApplication
{
   /* NOTE: Documentation
    * EvaluationData is responsible for all prelim data
    * it also houses alot of base functionality for 
    * student and grader which derive from it.
    * EvaluationData adopts the getter setter strategy
    * so the derived classes can easily use alot of
    * the core functionality built in. It also provides
    * a standardized way to access attributes accross the
    * program, as well as the setters serving as the funnel
    * for error checking, which makes domain constraints on 
    * the methods themselves simple and concise
    * */
   class EvaluationData: public Utillity
   {
      private:
         std::string dataFile;
         int totalHeaderCount;
         int dataLineLength;
         int totalLineCount;
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
         /* NOTE: Documentation
          * Explicit constructor
          * takes a filename string
          * as argument
          * */
         EvaluationData(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter for file name
          * */
         std::string evaluationFile(void) const;

         /* NOTE: Documentation
          * Return the total header count
          * This will be used to compare against
          * the HEADER_MAX macro of 4 so we know
          * when the max has been read in
          * */
         int totalEvaluationCount(void) const;
         void setTotalEvaluationCount(int);


         /* NOTE: Documentation
          * Accessor: getter and setter
          * For the actual length of the evaluation data
          * This is only what is stored in the vector
          * not the datas associated Key
          * */
         int evaluationDataLength(void) const;
         void setEvaluationDataLength(int);


         /* NOTE: Documentation
          * Accessor: getter and setter
          * This is to track line errors
          * */
         int fileLineCount(void) const;
         void setFileLineCount(int);


         /* NOTE: Documentation
          * Accessor: getter and setter
          * This is so the file position can be remembered
          * so the file can be closed and reopended by different
          * methods without have to read from the beginning of the file
          * */
         std::streampos currentFilePosition(void) const;
         void setCurrentFilePosition(std::ifstream &);


         /* NOTE: Documentation
          * Accessor: getter and setter for title
          * */
         std::string evaluationTitle(void) const;
         void setEvaluationTitle(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for title container
          * */
         std::string evaluationTitleContainer(int) const;
         void setEvaluationTitleContainer(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for category
          * */
         std::string evaluationCategory(void) const;
         void setEvaluationCategory(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for category container
          * */
         std::string evaluationCategoryContainer(int);
         void setEvaluationCategoryContainer(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for maxmark 
          * */
         std::string evaluationMaxMark(void) const;
         void setEvaluationMaxMark(const std::string &);


         /* NOTE: Documentation
          * Accessor:  getter and setter for maxmark container
          * */
         float evaluationMaxMarkContainer(int);
         void setEvaluationMaxMarkContainer(std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for weight
          * */
         std::string evaluationWeight(void) const;
         void setEvaluationWeight(const std::string &);


         /* NOTE: Documentation
          * Accessor: getter and setter for weight container
          * */
         float evaluationWeightContainer(int);
         void setEvaluationWeightContainer(std::string &);


         /* NOTE: Documentation
          * Load only preliminary data from file:
          * reads data based on first character matches
          * from a predefined enumerator in settings.h
          * */
         void loadEvaluationData(void);


         /* NOTE: Documentation
          * error print will in all output from
          * exceptions for BaseData class only
          * */
         void errorPrint(const char *);
   };
};

#endif
