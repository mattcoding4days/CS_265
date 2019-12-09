#include "../hdr/base.h"
#include "../hdr/grader.h"
#include "../hdr/student.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <cstring>

using namespace GraderApplication;

/* sub routine prototypes */
int countStudentLines(const std::string &);
void manualFileInput(std::string &);
void printUsage();
int parseArguments(int argc, char **argv, std::string &inputFile, std::string &name);


/* XXX: Documentation
 * */
int main(int argc, char **argv)
{
   auto start = std::chrono::system_clock::now();
   std::string inputFile("");
   std::string name("");

   int numargsfilled = parseArguments(argc, argv, inputFile, name); 

   if (numargsfilled == 1) {
      int numStudents = countStudentLines(inputFile);
      Grader grader(numStudents, inputFile);
      grader.loadBaseData(inputFile);
      grader.loadVector();
      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = end-start;
      std::time_t end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << std::ctime(&end_time) << std::endl;
      grader.makeGrades();
      grader.outputFinal();
      grader.outputError();
      grader.sanitize();
   }

   else if (numargsfilled == 2) {
      std::cout << "Name: " << name << std::endl;
      std::cout << "File: " << inputFile << std::endl;
   } else {
      std::cout << "numargsfilled: " << numargsfilled << std::endl;
      std::cerr << "Something happened" << std::endl;
   }

   exit(EXIT_SUCCESS);
}


/* XXX: Documentation
 *  Argument parser
 *  return range [1, 2]
 *  return 1 = only file was passed
 *  return 2 = file and name arguemnts fillfilled
 *  other exceptions are failures, in which 
 *  printUsage is called, which calls exit
 *  with EXIT_FAILURE.
 *
 *  Domain for parseArguments [1, 3] anything > 3 will be ignored 
 * */
int parseArguments(int argc, char **argv,
      std::string &inputFile, std::string &name)
{
   int retVal = 0; // will never return 0
   if (argc < 2) {
      manualFileInput(inputFile);
      retVal = 1;
   }
   else {
      int nFlag = 0;
      const char *nameFlag = "-s";
      for (int i = 1; i < argc; i++) {
         if (strncmp(nameFlag, argv[i], 2) == 0) {
            /* get the position of the -s flag */
            nFlag = i;
            break;
         }
      }
      if (nFlag == 0) { 
         /* No -s flag was given, the argument must be a filename */
         inputFile = argv[nFlag+1];
         return retVal = 1;
      }
      if (argv[nFlag+1] == NULL) {
         /* Check to see if -s has corresponding name arg,
          * if not show proper error msg, print usage and exit
          * */
         fprintf(stderr, "\n\t\tStudent name not supplied\n\n");
         printUsage();
      } else if ((strncmp(nameFlag, argv[nFlag+1], 2) == 0)) {
         /* Check to see if -s has been passed twice "-s -s",
          * if so, show proper error msg, print usage and exit
          * */
         fprintf(stderr, "\n\t\tName flag found multiple times\n");
         printUsage();
      } else {
         /* If we make it to here we have a valid -s flag and a corresponding arg 
          * Now we must figure out if we have a file name before -s or after,
          * or not at all and handle appropriately
          * */
         if (nFlag == 1) {
            if (argv[nFlag+2] != NULL) {
               /* Check for 3rd arg which will be treated as filename*/
               name = argv[nFlag+1];
               inputFile = argv[nFlag+2];
               return retVal = 2;
            }
            else {
               /* name properly passed, but file arg is lacking */
               name = argv[nFlag+1];
               manualFileInput(inputFile);
               retVal = 2;
            }
         }
         else if (nFlag == 2) {
            inputFile = argv[nFlag-1];
            name = argv[nFlag+1];
            return retVal = 2;
         }
      }
   }
   return retVal;
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
   fprintf(stderr, "grader: Usage\n");
   fprintf(stderr, "./grader                    [Prompted for filename]\n");
   fprintf(stderr, "./grader -s name            [Prompted for filename, will return grade for the name passed]\n");
   fprintf(stderr, "./grader filename           [Run with specified file]\n");
   fprintf(stderr, "./grader filename -s sname  [Run specified file on just the specified student]\n");
   fprintf(stderr, "./grader -s name1 name2     [Run with name2 as filename and name1 as student name]\n");

   exit(EXIT_FAILURE);
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
      exit(EXIT_FAILURE);
   }
   inFile.close();
   return numberOfLines;
}
