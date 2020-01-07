#include "../hdr/argparser.hpp"


namespace GraderApplication
{
   ArgParse::ArgParse(const char *flag)
      : nameFlag(flag)
   { }


   int ArgParse::parseArguments(int argc, char **argv,
         std::string &inputFile,
         std::string &name)
   {
      int retVal = 0; // will never return 0
      if (argc < 2)
      {
         manualFileInput(inputFile);
         retVal = 1;
      }
      else
      {
         int nFlag = 0;
         for (int i = 1; i < argc; i++)
         {
            if (strncmp(nameFlag, argv[i], 2) == 0)
            {
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

         if (argv[nFlag+1] == NULL)
         {
            /* Check to see if -s has corresponding name arg,
             * if not show proper error msg, print usage and exit
             * */
            fprintf(stderr, "\n\t\tStudent name not supplied\n\n");
            printUsage();
         }

         else if ((strncmp(nameFlag, argv[nFlag+1], 2) == 0))
         {
            /* Check to see if -s has been passed twice "-s -s",
             * if so, show proper error msg, print usage and exit
             * */
            fprintf(stderr, "\n\t\tName flag found multiple times\n");
            printUsage();
         }

         else
         {
            /* If we make it to here we have a valid -s flag and a corresponding arg 
             * Now we must figure out if we have a file name before -s or after,
             * or not at all and handle appropriately
             * */
            if (nFlag == 1)
            {
               if (argv[nFlag+2] != NULL)
               {
                  /* Check for 3rd arg which will be treated as filename*/
                  name = argv[nFlag+1];
                  inputFile = argv[nFlag+2];
                  return retVal = 2;
               }
               else
               {
                  /* name properly passed, but file arg is lacking */
                  name = argv[nFlag+1];
                  manualFileInput(inputFile);
                  retVal = 2;
               }
            }

            else if (nFlag == 2)
            {
               inputFile = argv[nFlag-1];
               name = argv[nFlag+1];
               return retVal = 2;
            }
         }
      }
      return retVal;
   }


   void ArgParse::manualFileInput(std::string &input)
   {
      std::cout << "Enter file path: ";
      std::getline(std::cin, input);
   }


   void ArgParse::printUsage(void)
   {
      fprintf(stderr, "grader: Usage\n");
      fprintf(stderr, "./grader                    [Prompted for filename]\n");
      fprintf(stderr, "./grader -s name            [Prompted for filename, will return grade for the name passed]\n");
      fprintf(stderr, "./grader filename           [Run with specified file]\n");
      fprintf(stderr, "./grader filename -s sname  [Run specified file on just the specified student]\n");
      fprintf(stderr, "./grader -s name1 name2     [Run with name2 as filename and name1 as student name]\n");

      exit(EXIT_FAILURE);
   }
};
