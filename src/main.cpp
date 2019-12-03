#include "../hdr/base.h"
#include "../hdr/grader.h"
#include "../hdr/student.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace GraderApplication;

/* sub routine prototypes */
int countStudentLines( const std::string & );
void manualFileInput(std::string &);
void printUsage();


/* XXX: Documentation
 * */
int main(int argc, char **argv)
{
   std::string inputFile("");
   std::string name("");
   if (argc < 2) {
      manualFileInput(inputFile);
   } else {
      int nFlag = 0;
      const char *nameFlag = "-s";
      for (int i = 1; i < argc; i++) {
         const char *temp = argv[i];
         if (strcmp(nameFlag, temp) == 0 && (!nFlag)) {
            nFlag = i;
            if (argv[i+1] != NULL) {
               /* Evaluate seperately to give more accurate error msg */
               temp = argv[i+1];
               if (strcmp(nameFlag, temp) != 0) {
                  name = argv[i+1];
               } else {
                  std::cerr << "\n\t\t-s flag used twice\n";
                  printUsage();
               }
            } else {
               std::cerr << "\n\t\tNo student name given\n";
               printUsage();
            }
         }
      }
      /* -s was not passed */
      if (!nFlag) { inputFile = argv[1]; }
      /* -s was the first argument passed and there are enough arguments to assume a file*/
      else if (nFlag && argc > 3) { inputFile = argv[nFlag + 2]; }
      /*  */
      else if (nFlag && argc == 3) { manualFileInput(inputFile); }
      /* -s was the second argument, which means the first arg is filename */
      else if (nFlag == 2) { inputFile = argv[nFlag - 1]; }
   }
   if (name.empty()) {
      std::cout << "File: " << inputFile << std::endl;

   } else {
      std::cout << "Name: " << name << std::endl;
      std::cout << "File: " << inputFile << std::endl;
   }


   ///* Do a quick count of students in the file
   // * */
   //int numberOfStudentsToBeLoaded = countStudentLines(inputFile);
   //if ( numberOfStudentsToBeLoaded == -1 ) {
   //   /* an error has occured, likely from trying to open a corrupted file path, 
   //    * the count students routine will print out an appropriate error msg in this 
   //    * event, return 1 and exit the program.
   //    * */
   //   exit(1);
   //}

   ///* init timer, for time and date stamp */
   //auto start = std::chrono::system_clock::now();

   ///* Instantiate main object, which derives from Base and StudentData
   // * */
   //Grader graderProgram(numberOfStudentsToBeLoaded, inputFile);
   ///* load all base data (Base is referring to the prelim data 
   // * before students are encountered)*/
   //graderProgram.loadBaseData(inputFile);

   ///* load the student vector defined in grader class
   // * */
   //graderProgram.loadVector();
   //auto end = std::chrono::system_clock::now();
   //std::chrono::duration<double> elapsed_seconds = end-start;
   //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   //std::cout << std::ctime(&end_time) << std::endl;

   ///* Finalize and clean up  */
   //graderProgram.makeGrades();
   //graderProgram.outputFinal();
   //graderProgram.sanitize();
   //return 0;
}

/* XXX: Documentation
 * Get userinput for file 
 * */
void manualFileInput(std::string &input)
{
   std::cout << "Enter file path: ";
   std::getline(std::cin, input);
}

/* XXX: Documentation
 * printUsage()
 * Explain proper usage to the user 
 * */
void printUsage()
{
   std::cout << "grader: Usage\n";
   std::cout << "./grader                       [Prompted for filename]\n";
   std::cout << "./grader -s name               [Prompted for filename, will return grade for the name passed]\n";
   std::cout << "./grader filename              [Run with specified file]\n";
   std::cout << "./grader filename -s sname     [Run specified file on just the specified student]\n";
   std::cout << "./grader -s name1 name2        [Run with name2 as filename and name1 as student name]\n";

   exit(2);
}

/* XXX: Documentation
 * countStudentLines: Is meant to only count lines
 * that include student names
 * it must skip, empty lines, and comments #
 *
 * The returned value will be used to accurately
 * reserve space in the student vector, which will hold
 * all objects, as well as to be used as an accurate reference
 * for size for internal localized temp arrays or vectors that
 * may be used.
 * */
int countStudentLines( const std::string &fileDat )
{
   int numberOfLines = 0;
   std::string dummyLine; 
   std::ifstream inFile( fileDat );

   if ( inFile.good() ) {
      while ( std::getline( inFile, dummyLine )) {
         if (! ( dummyLine.empty()) ) {
            char c = '\0';
            c = dummyLine[0];
            if ( ! (std::isupper( c )) && c != WS && c != COMM ) {
               ++numberOfLines;
            }
         }
      }
   } else {
      std::cerr << "Error opening " << fileDat 
                << " to count number of students to be loaded into the program" << std::endl;
      return -1;
   }
   inFile.close();
   return numberOfLines;
}
