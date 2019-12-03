#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>

/* From the British Columbia grade scale via wikipedia */
// A+ 90%–100%
// A  85%–89%
// A- 80%–84%
// B+ 75%–79%
// B  70%–74%
// B- 65%–69%
// C+ 60%–64%
// C  56%–59%
// C- 50%–55%
// F  0%–49%

namespace GraderApplication
{
   /* Check what range the final grade matches */
   #define IS_A_PLUS(x) ((x) >= 90)
   #define IS_A(x) ((x) >= 85 && (x) <= 89)
   #define IS_A_MINUS(x) ((x) >= 80 && (x) < 85)
   #define IS_B_PLUS(x) ((x) >= 75 && (x) < 80)
   #define IS_B(x) ((x) >= 70 && (x) < 75)
   #define IS_B_MINUS(x) ((x) >= 65 && (x) < 70)
   #define IS_C_PLUS(x) ((x) >= 60 && (x) < 65)
   #define IS_C(x) ((x) >= 56 && (x) < 60)
   #define IS_C_MINUS(x) ((x) >= 50 && (x) < 56)
   #define IS_F(x) ((x) < 50)


   /* XXX: Documentaion
    * Max line length expected after the name postfix is read in. 
    * */
   const int LEN = 8;

   /* XXX: Documentaion
    * File delimiters, or characters we want to ignore, or look for 
    * when parsing the file 
    * */
   enum Delim 
   {
      WS = ' ',
      COMM = '#',
      TAB = '\t'
   };

   /* XXX: Documentaion
    * BaseSchema delimiters, Used to check against
    * when parsing the file for post student grade data
    * */
   enum BaseChecks
   {
      TITLE = 'T',
      CATEGORY = 'C',
      MAXMARK = 'M',
      WEIGHT = 'W'
   };

   /* XXX: Documentaion
    * Colors set by the default constructor, just for better program readabillity 
    * */
   struct Colors
   {
      std::string RED;
      std::string GREEN;
      std::string YELLOW;
      std::string BLUE;
      std::string RESET;
      
      /* Fill in with ANSI color codes later */
      Colors(void)
         : RED("")
         , GREEN("")
         , YELLOW("")
         , BLUE("")
         , RESET("")
      { }
   };

   /* XXX: Documentaion
    * Stuct for letter grade representation the student will recieve 
    * */
   struct Echelon
   {
      std::string high_A;
      std::string mid_A;
      std::string low_A;
      std::string high_B;
      std::string mid_B;
      std::string low_B;
      std::string high_C;
      std::string mid_C;
      std::string low_C;
      std::string F;
      std::string GOR;

      Echelon()
         : high_A("A+") , mid_A("A") , low_A("A-")
         , high_B("B+") , mid_B("B") , low_B("B-")
         , high_C("C+") , mid_C("C") , low_C("C-")
         , F("F"), GOR("Grade out of Range")
      { }
   };
};

#endif
