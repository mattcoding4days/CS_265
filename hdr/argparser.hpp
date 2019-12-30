#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <iostream>
#include <cstring>
#include <string>

namespace GraderApplication
{
    /* NOTE: Documentation
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
    class ArgParse
    {
        private:
            const char *nameFlag;

        public:
            int argc;
            char **argv;
            std::string inputFile;
            std::string id;


            /* NOTE: Documentation
             * Explicit constructor
             * takes only one argument which
             * should be -s for the flag that
             * will represent
             * */
            ArgParse(const char *flag);


            /* NOTE: Documentation
             * return range [1, 2]
             * return 1 = only file was passed
             * return 2 = file and name arguemnts fillfilled
             * other exceptions are failures, in which
             * printUsage is called, which calls exit
             * with EXIT_FAILURE.
             *
             * Domain for parseArguments [1, 3] anything > 3 will be ignored
             * */
            int parseArguments(int argc, char **argv,
                               std::string &inputFile, std::string &name);


            /* NOTE: Documentation
            * Get userinput for file
            * */
            void manualFileInput(std::string &input);


            /* NOTE: Documentation
            * printUsage()
            * Explain proper usage to the user
            * */
            void printUsage(void);
    };
};


#endif
