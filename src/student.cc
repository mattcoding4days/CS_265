/* All  main documentaion is in header files
 * for corresponding cpp files.
 * */
#include <iostream>
#include <fstream>
#include <sstream>
#include "../hdr/student.hpp"


namespace GraderApplication
{
  StudentData::StudentData(void)
    : name ("")
      , studentDataLen(0)
      , labScore (0.0)
      , assignScore (0.0)
      , midtermScore (0.0)
      , finalScore (0.0)
      , totalGrade (0.0)
      , letterGrade ("")
      , isWDR (false)
      , isError (false)
      , errorDef ("")
      , mlineCount(0)

  {
    /* Initialize the vectors */
    gradesContainer.reserve(1);
    calculatedGradesContainer.reserve(1);
  }


  StudentData::~StudentData(void)
  {
    gradesContainer.clear();
    calculatedGradesContainer.clear();
  }


  StudentData::StudentData(StudentData &&src) noexcept : Utillity(src)
    , name(src.name)
    , gradesContainer(std::move(src).gradesContainer)
    , calculatedGradesContainer(std::move(src).calculatedGradesContainer)
    , studentDataLen(src.studentDataLen)
    , labScore(src.labScore)
    , assignScore(src.assignScore)
    , midtermScore(src.midtermScore)
    , finalScore(src.finalScore)
    , totalGrade(src.totalGrade)
    , letterGrade(src.letterGrade)
    , isWDR(src.isWDR)
    , isError(src.isError)
    , errorDef(src.errorDef)
    , mlineCount(src.mlineCount)

    {
      /* Curent line is from derived class*/
      currentLine = src.currentLine;
      /* Reset the original object b
       * ecause ownership has moved */
      src.currentLine = "";
      src.name = "";
      src.gradesContainer.clear();
      src.calculatedGradesContainer.clear();
      src.studentDataLen = 0;
      src.labScore = 0.0;
      src.assignScore = 0.0;
      src.midtermScore = 0.0;
      src.finalScore = 0.0;
      src.totalGrade = 0.0;
      src.letterGrade = 0.0;
      src.isWDR = false;
      src.isError = false;
      src.errorDef = "";
      src.mlineCount = 0;
    }


  StudentData::StudentData(const StudentData &src) 
    : Utillity(src)
      , name(src.name)
      , gradesContainer(src.gradesContainer)
      , calculatedGradesContainer(src.calculatedGradesContainer)
      , studentDataLen(src.studentDataLen)
      , labScore(src.labScore)
      , assignScore(src.assignScore)
      , midtermScore(src.midtermScore)
      , finalScore(src.finalScore)
      , totalGrade(src.totalGrade)
      , letterGrade(src.letterGrade)
      , isWDR(src.isWDR)
      , isError(src.isError)
      , errorDef(src.errorDef)
      , mlineCount(src.mlineCount)

  {
    currentLine = src.currentLine;
  }


  StudentData& StudentData::operator=(const StudentData &src)
  {
    /* pessimistic check for self assignment */
    if (this == &src)
    {
      return *this;
    }

    currentLine = src.currentLine;
    name = src.name;
    gradesContainer = src.gradesContainer;
    calculatedGradesContainer = src.calculatedGradesContainer;
    studentDataLen = src.studentDataLen;
    labScore = src.labScore;
    assignScore = src.labScore;
    midtermScore = src.midtermScore;
    finalScore = src.finalScore;
    totalGrade = src.totalGrade;
    letterGrade = src.letterGrade;
    isWDR = src.isWDR;
    isError = src.isWDR;
    errorDef = src.errorDef;
    mlineCount = src.mlineCount;

    return *this;
  }


  StudentData& StudentData::operator=(StudentData&& src) noexcept
  {
    /* pessimistic check for self assignment */
    if (this == &src)
    {
      return *this;
    }
    /* Init move */
    currentLine = src.currentLine;
    name = src.name;
    gradesContainer = std::move(src).gradesContainer;
    calculatedGradesContainer = std::move(src).calculatedGradesContainer;
    studentDataLen = src.studentDataLen;
    labScore = src.labScore;
    assignScore = src.labScore;
    midtermScore = src.midtermScore;
    finalScore = src.finalScore;
    totalGrade = src.totalGrade;
    letterGrade = src.letterGrade;
    isWDR = src.isWDR;
    isError = src.isWDR;
    errorDef = src.errorDef;
    mlineCount = src.mlineCount;

    /* Reset the original object because ownership has moved */
    src.name = "";
    src.gradesContainer.clear();
    src.calculatedGradesContainer.clear();
    src.studentDataLen = 0;
    src.labScore = 0.0;
    src.assignScore = 0.0;
    src.midtermScore = 0.0;
    src.finalScore = 0.0;
    src.totalGrade = 0.0;
    src.letterGrade = 0.0;
    src.isWDR = false;
    src.isError = false;
    src.errorDef = "";
    src.mlineCount = 0;

    return *this;
  }


  void StudentData::errorPreserve(std::string &e)
  {
    /* The offending line data will have already been set
     * in the loadStudent method with currentLine
     * */
    this->setStudentError(true);
    this->setErrorDefinition(e);
  }


  std::string StudentData::studentName(void) const { return this->name; }


  void StudentData::setStudentName(std::string &_name)
  {
    try
    {
      if (this->isAlphaNumeric(_name))
      {
        this->name = _name;
      }
      else
      {
        throw StudentIDNonAlphaNumeric();
      }
    }
    catch (StudentIDNonAlphaNumeric &e)
    {
      std::string onError(e.what());
      this->errorPreserve(onError);
    }
  }


  float StudentData::studentGradesContainer(int &itr) { return this->gradesContainer[itr]; }


  void StudentData::setStudentGradesContainer(std::string &_grade, EvaluationData &eval)
  {
    try
    {
      /* Check if string is infact a digit */
      if (this->isDigits(_grade))
      {
        float temp = stringTofloat(_grade);
        this->gradesContainer.emplace_back(temp);
        /* Check if a mark is larger than max mark */
        int size = this->gradesContainer.size();
        for (int i = 0; i < size; i++ )
        {
          if (this->gradesContainer[i] > eval.evaluationMaxMarkContainer(i)
              && !(this->studentWDR()))
          {
            throw StudentMarkExceedsMaxMark();
          }
        }
      }

      else {
        /* if it is not a digit, convert to uppercase and
         * and check if it is WDR, if not throw error
         * */
        std::string n_grade = convert_toupper(_grade);
        if (n_grade == WDRN)
        {
          this->setStudentWDR(true);
        }
        else
        {
          throw FailStringFloatConversion();
        }
      }
    }
    catch (FailStringFloatConversion &e)
    {
      std::string onError(e.what());
      this->errorPreserve(onError);
    }
    catch (StudentMarkExceedsMaxMark &e)
    {
      std::string onError(e.what());
      this->errorPreserve(onError);
    }
  }


  float StudentData::calculatedGrades(int itr) { return this->calculatedGradesContainer[itr]; }


  void StudentData::setCalculatedGrades(std::vector<float> &calcMarks)
  {
    for (std::size_t i = 0; i < calcMarks.size(); ++i)
    {
      this->calculatedGradesContainer.emplace_back(calcMarks[i]);
    }
  }


  int StudentData::studentDataLength(void) const { return this->studentDataLen; }


  void StudentData::setStudentDataLength(int _length, int eval)
  {
    try
    {
      if (_length == eval)
      {
        this->studentDataLen = _length;
      }
      else
      {
        /* Our lengths do not match, cannot compute data correctly
         * throw and end program
         * */
        throw StudentDataLengthError();
      }

    }
    catch (StudentDataLengthError &e)
    {
      std::string onError(e.what());
      this->errorPreserve(onError);
    }
  }


  float StudentData::studentLabScore(void) const { return this->labScore; }

  void StudentData::setStudentLabScore(float score)
  {
    /* bound check */
    if (score < 0)
    {
      std::cerr << "Score: " << score << " is out of bounds" << std::endl;
    }
    else
    {
      this->labScore += score;
    }
  }


  float StudentData::studentAssignScore(void) const { return this->assignScore; }


  void StudentData::setStudentAssignScore(float score)
  {
    /* bound check */
    if (score < 0)
    {
      std::cerr << "Score: " << score << " is out of bounds" << std::endl;
    }
    else
    {
      this->assignScore += score;
    }
  }


  float StudentData::studentMidtermScore(void) const { return this->midtermScore; }


  void StudentData::setStudentMidtermScore(float score)
  {
    /* bound check */
    if (score < 0)
    {
      std::cerr << "Score: " << score << " is out of bounds" << std::endl;
    }
    else
    {
      this->midtermScore += score;
    }
  }


  float StudentData::studentFinalScore(void) const { return this->finalScore; }


  void StudentData::setStudentFinalScore(float score)
  {
    /* bound check */
    if (score < 0)
    {
      std::cerr << "Score: " << score << " is out of bounds" << std::endl;
    }
    else
    {
      this->finalScore += score;
    }
  }


  float StudentData::studentTotalGrade(void) const { return this->totalGrade; }


  void StudentData::setStudentTotalGrade(const float _totalGrade) { this->totalGrade += _totalGrade; }


  std::string StudentData::studentLetterGrade(void) const { return this->letterGrade; }


  void StudentData::setStudentLetterGrade(const std::string &_letterGrade) { this->letterGrade = _letterGrade; }


  bool StudentData::studentWDR(void) const { return this->isWDR; }


  void StudentData::setStudentWDR(bool _isWDR) { this->isWDR = _isWDR; }


  bool StudentData::studentError(void) const { return this->isError; }


  void StudentData::setStudentError(bool _isError) { this->isError = _isError; }


  std::string StudentData::errorDefinition(void) const { return this->errorDef; }


  void StudentData::setErrorDefinition(const std::string &e)
  {
    if (! (e.empty()) )
    {
      this->errorDef = e;
    }
    else
    {
      std::cerr << "\nError Definition is empty!\n" << std::endl;
    }
  }


  int StudentData::lineCount(void) const { return this->mlineCount; }


  void StudentData::setLineCount(int _count)
  {
    if (_count > 0)
    {
      this->mlineCount = _count;
    }
    else
    {
      std::cerr << "\nLine count is less than 1" << std::endl;
    }
  }


  bool StudentData::loadStudents(EvaluationData &eval)
  {
    try
    {
      std::ifstream datafile(eval.evaluationFile());
      if ( datafile.is_open() )
      {
        datafile.seekg(eval.currentFilePosition());
        std::string line("");
        while ( std::getline(datafile, line))
        {
          // increment line count
          eval.setFileLineCount(1);
          this->setLineCount(eval.fileLineCount());

          /* if the line is empty skip it,
           * by immediatley restarting the
           * control loop with the continue keyword
           * */
          if (line.empty())
          {
            continue;
          }

          this->setCurrentLineContent(line);
          this->stripComments(line);

          if (! (this->isStudentProcessed(line)) )
          {
            this->processStudent(line);

            std::string sId("");
            std::string sMarks("");

            std::stringstream ss(line);
            ss >> sId;
            this->setStudentName(sId);
            /* After trying to set the name, if it fails
             * due to nonNumeric, we need to test that here
             * so we can end this function and not read in the
             * grades for the failed id.
             * If the name setter failed it would have reported
             * to errorPreserve which would have switched
             * the isError variable to true, check for that here
             * */

            if (this->studentError())
            {
              eval.setCurrentFilePosition(datafile);
              datafile.close();
              return true;
            }
            else
            {
              int i = 0;
              while (ss >> sMarks)
              {
                this->setStudentGradesContainer(sMarks, eval);
                if (! (this->studentError()) )
                {
                  i++;
                }
                else
                {
                  /* Setting the grades failed */
                  eval.setCurrentFilePosition(datafile);
                  datafile.close();
                  return true;
                }
              }

              /* Set datalength checks if the length is the
               * same as the evaluation data length */
              this->setStudentDataLength(i, eval.evaluationDataLength());
              // only process one line at a time, update file position
              eval.setCurrentFilePosition(datafile);
              datafile.close();
              return true;
            }
          }
          /* A duplicate student was found,
           * throw for error preserving purposes
           * */
          eval.setCurrentFilePosition(datafile);
          throw DuplicateFound();

        }
      }
      else
      {
        throw std::logic_error("*** File Not Found: ");
      }
    }
    catch (std::logic_error &e)
    {
      std::cerr << e.what() << eval.evaluationFile() << std::endl;
      exit(EXIT_FAILURE);
    }
    catch (DuplicateFound &e)
    {
      std::string onError(e.what());
      this->errorPreserve(onError);
    }
    return false;
  }


  bool StudentData::isStudentProcessed(const std::string &lineToCompare)
  {
    bool isProcessed = false;
    std::string tempLine("");
    // test if the file exists
    if ( this->testForFileExistence(TEMPFILE) )
    {
      std::ifstream tempFile(TEMPFILE);
      while ( std::getline(tempFile, tempLine) )
      {
        if ( lineToCompare == tempLine )
        {
          tempFile.close();
          isProcessed = true;
          return isProcessed;
        }
      }
    }
    // the file did not exist, which means
    // this is the first student we are reading infile
    return isProcessed;
  }


  bool StudentData::testForFileExistence(const std::string &file)
  {
    /* Test if grader has already created or temp file */
    std::ifstream infile(file);
    if ( infile.good() )
    {
      infile.close();
      return true;
    }
    return false;
  }


  void StudentData::processStudent(const std::string &process)
  {
    /* only append to the file, dont trample over old data */
    std::ofstream outFile(TEMPFILE, std::fstream::app);
    if ( outFile.good() )
    {
      // write only the student id, which should be the first
      // index of the line
      outFile << process << std::endl;
      outFile.close();
    }
    else
    {
      std::cerr << "Debug MSG: Could not open file to process student" << std::endl;
    }
  }
};
