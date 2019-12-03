#include <iostream>
#include <string.h>


struct CliOptions {

};

void printUsage();
int getOption(int count, char **argv, const char *accepted);


/* Init main routine */
int main(int argc, char *argv[])
{
   if (argc < 2) {
      printUsage();
   }
   const char *sname = "-s";
   int status;
   status = getOption(argc, argv, sname);

   if (status) {
      
   }

   return 0;
}

void printUsage()
{
   std::cout << "Usage: grader -s <path/to/file>" << std::endl;
   exit(2);
}

/* get user option, :*/
int getOption(int count, char **argv, const char *sname)
{
   for (int i = 1; i < count; ++i) {
      const char *temp = argv[i];
      if (strcmp(sname, temp) == 0) {
         fprintf(stdout, "Found s flag: %s\n", temp);
         return 0;
      } else {
         
      }
   }
   return -1;
}
