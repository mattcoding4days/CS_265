/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include <iostream>
#include <iterator>
#include <sstream>
#include "../hdr/evaluation.hpp"


namespace GraderApplication
{
   EvaluationData::EvaluationData(const std::string &file)
      : dataFile(file)
      , totalHeaderCount(0)
      , dataLineLength(0)
      , totalLineCount(0)
      , currentLine("")
      , currentFilePos(0)
      , title("")
      , category("")
      , maxMark("")
      , weight("")
   {
      /* Init vectors */
      titleContainer.reserve(1);
      categoryContainer.reserve(1);
      maxMarkContainer.reserve(1);
      weightContainer.reserve(1);
   }

   std::string EvaluationData::evaluationFile(void) const { return this->dataFile; }


   int EvaluationData::totalEvaluationCount(void) const { return this->totalHeaderCount; }


   void EvaluationData::setTotalEvaluationCount(int _x ) { this->totalHeaderCount += _x; }


   int EvaluationData::evaluationDataLength(void) const { return this->dataLineLength; }


   void EvaluationData::setEvaluationDataLength(int _length)
   {
      try
      {
         if (this->dataLineLength == 0)
         {
            /* This is the first time we are setting the length*/
            this->dataLineLength = _length;
         }
         else if (this->dataLineLength == _length)
         {
            /* Our lengths match, all is well in the galaxy, do nothing */
         }
         else
         {
            /* Our lengths do not match, cannot compute data correctly
             * throw and end program
             * */
            throw DataLength();
         }

      }
      catch (DataLength &e)
      {
         errorPrint(e.what());
      }
   }


   std::string EvaluationData::currentLineContent(void) const { return this->currentLine; }


   void EvaluationData::setCurrentLineContent(const std::string _currentLine)
   {
      if (!(_currentLine.empty()))
      {
         this->currentLine = _currentLine;
      }
   }


   int EvaluationData::fileLineCount(void) const { return this->totalLineCount; }


   void EvaluationData::setFileLineCount(int _x)
   {
      this->totalLineCount += _x;
   }


   std::streampos EvaluationData::currentFilePosition(void) const { return this->currentFilePos; }


   void EvaluationData::setCurrentFilePosition(std::ifstream &f) { this->currentFilePos = f.tellg(); }


   std::string EvaluationData::evaluationTitle(void) const { return this->title; }


   void EvaluationData::setEvaluationTitle(const std::string &_title)
   {
      try
      {
         if ( this->title.empty() )
         {
            this->title = _title; 
         }
         else
         {
            throw DuplicateFound();
         }
      }
      catch (DuplicateFound &e)
      {
         errorPrint(e.what());
      }
   }


   std::string EvaluationData::evaluationTitleContainer(int itr) const
   {
      if (itr < 0 || itr > this->evaluationDataLength())
      {
         std::cerr << "Iterator found out of bounds for eval data length" << std::endl;
         exit(EXIT_FAILURE);
      }
      return this->titleContainer[itr];
   }


   void EvaluationData::setEvaluationTitleContainer(const std::string &_sub)
   {
      try
      {
         for (int i = 0; i < this->evaluationDataLength(); ++i)
         {
            if (this->titleContainer[i] == _sub)
            {
               throw DuplicateFound();
            }
         }
         /* if no exception is thrown insert the value */
         this->titleContainer.emplace_back(_sub);
      }
      catch(DuplicateFound &e)
      {
         errorPrint(e.what());
      }
   } 


   std::string EvaluationData::evaluationCategory(void) const { return this->category; }


   void EvaluationData::setEvaluationCategory(const std::string &_category)
   { 
      try
      {
         if ( this->category.empty() )
         {
            this->category = _category;
         }
         else
         {
            throw DuplicateFound();
         }
      }
      catch (DuplicateFound &e)
      {
         errorPrint(e.what());
      }
   }


   std::string EvaluationData::evaluationCategoryContainer(int itr)
   {
      if (itr < 0 || itr > this->evaluationDataLength())
      {
         std::cerr << "Iterator found out of bounds for eval data length" << std::endl;
         exit(EXIT_FAILURE);
      }
      return this->categoryContainer[itr];
   }


   void EvaluationData::setEvaluationCategoryContainer(const std::string &_sub)
   {
      /* Nothing much to check here */
      this->categoryContainer.emplace_back(_sub);

   }


   std::string EvaluationData::evaluationMaxMark() const { return this->maxMark; }


   void EvaluationData::setEvaluationMaxMark(const std::string &_maxMark)
   {
      try
      {
         if ( this->maxMark.empty() )
         {
            this->maxMark = _maxMark;
         }
         else
         {
            throw DuplicateFound();
         }
      }
      catch (DuplicateFound &e)
      {
         errorPrint(e.what());
      }
   }


   float EvaluationData::evaluationMaxMarkContainer(int itr)
   {
      if (itr < 0 || itr > this->evaluationDataLength())
      {
         std::cerr << "Iterator found out of bounds for eval data length" << std::endl;
         exit(EXIT_FAILURE);
      }
      return this->maxMarkContainer[itr];
   }


   void EvaluationData::setEvaluationMaxMarkContainer(std::string &_sub)
   {
      try
      {
         if (isDigits(_sub))
         {
            float temp = stringTofloat(_sub);
            this->maxMarkContainer.emplace_back(temp);
         }
         else
         {
            throw FailStringFloatConversion();
         }

      }
      catch (FailStringFloatConversion &e)
      {
         errorPrint(e.what());
      }
   }


   std::string EvaluationData::evaluationWeight(void) const { return this->weight; }


   void EvaluationData::setEvaluationWeight(const std::string &_weight)
   {
      try
      {
         if ( this->weight.empty() )
         {
            this->weight = _weight;
         }
         else
         {
            throw DuplicateFound();
         }
      }
      catch (DuplicateFound &e)
      {
         errorPrint(e.what());
      }
   }


   float EvaluationData::evaluationWeightContainer(int itr) { return this->weightContainer[itr]; }


   void EvaluationData::setEvaluationWeightContainer(std::string &_sub)
   {
      float total;
      try
      {
         if (isDigits(_sub))
         {
            float temp = stringTofloat(_sub);
            this->weightContainer.emplace_back(temp);
         }
         else
         {
            throw FailStringFloatConversion();
         }

         std::size_t tempCompare = this->evaluationDataLength();
         if (this->weightContainer.size() == tempCompare)
         {
            /* if the container size is equal to the line length
             * we know all grades have been read in, which means
             * it is safe to sum them all up and test the total
             * */
            std::vector<float> Fvec = this->weightContainer;
            total = vecSummation(Fvec);
            if (total != 100)
            {
               throw WeightSummation();
            }
         }
      }
      catch (FailStringFloatConversion &e)
      {
         errorPrint(e.what());
      }
      catch (WeightSummation &e)
      {
         errorPrint(e.what());
      }
   }


   void EvaluationData::loadEvaluationData(void)
   {
      try
      {
         std::ifstream inFile(this->evaluationFile());
         std::string line("");
         if (inFile.good())
         {
            while (std::getline(inFile, line))
            {
               /* record the current line for error purposes */
               this->setCurrentLineContent(line);
               this->stripComments(line);

               std::string keyword("");
               std::string sTemp("");
               std::stringstream ss(line);

               ss >> keyword;
               if (keyword == TITLE)
               {
                  this->setEvaluationTitle(keyword);
                  this->setTotalEvaluationCount(1);
                  int i = 0;
                  while(ss >> sTemp)
                  {
                     this->setEvaluationTitleContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setEvaluationDataLength(i);
               }

               else if (keyword == CATEGORY)
               {
                  this->setEvaluationCategory(keyword);
                  this->setTotalEvaluationCount(1);
                  int i = 0;
                  while(ss >> sTemp)
                  {
                     this->setEvaluationCategoryContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setEvaluationDataLength(i);
               }

               else if (keyword == MAXMARK)
               {
                  this->setEvaluationMaxMark(keyword);
                  this->setTotalEvaluationCount(1);
                  int i = 0;
                  while(ss >> sTemp)
                  {
                     this->setEvaluationMaxMarkContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setEvaluationDataLength(i);
               }

               else if (keyword == WEIGHT)
               {
                  this->setEvaluationWeight(keyword);
                  this->setTotalEvaluationCount(1);
                  int i = 0;
                  while(ss >> sTemp)
                  {
                     this->setEvaluationWeightContainer(sTemp);
                     i++;
                  }
                  /* set our evaluation data length */
                  this->setEvaluationDataLength(i);
               }

               /* we read a line so increment the count */
               this->setFileLineCount(1);

               if (this->totalEvaluationCount() == HEADER_MAX)
               {
                  this->setCurrentFilePosition(inFile);
                  inFile.close();
               }
            }
         }
         else
         {
            throw std::logic_error("*** File Not Found: ");
         }
      }
      catch (std::logic_error &e)
      {
         std::cerr << e.what() << this->evaluationFile() << std::endl;
      }
   }


   void EvaluationData::errorPrint(const char *a)
   {
      std::cerr << "\nERROR: " << a << std::endl;
      std::cerr << "\nOffending line number: "
                << this->fileLineCount() << std::endl;
      std::cerr << "Offending content: "
                << this->currentLineContent() << std::endl;

      exit (EXIT_FAILURE);
   }
};
