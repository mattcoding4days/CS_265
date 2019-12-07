#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>


namespace GraderApplication {
   /* Check what range the final grade matches */
#define IS_A_PLUS(x) ((x) >= 89.5 && (x) <= 100 )
#define IS_A(x) ((x) >= 84.5 && (x) < 89.5)
#define IS_A_MINUS(x) ((x) >= 79.5 && (x) < 84.5)
#define IS_B_PLUS(x) ((x) >= 75.5 && (x) < 79.5)
#define IS_B(x) ((x) >= 71.5 && (x) < 75.5)
#define IS_B_MINUS(x) ((x) >= 67.5 && (x) < 71.5)
#define IS_C_PLUS(x) ((x) >= 63.5 && (x) < 67.5)
#define IS_C(x) ((x) >= 59.5 && (x) < 63.5)
#define IS_C_MINUS(x) ((x) >= 54.5 && (x) < 59.5)
#define IS_D(x) ((x) >= 49.5 && (x) < 54.5)
#define IS_F(x) ((x) >= 0 && (x) < 49.5)

/* Max amount of evaluation lines we can have */
#define HEADER_MAX 4

/* Define Header Keywords here. The text file surely should have
 * some standardization
 * */
#define TITLE "TITLE" 
#define CATEGORY "CATEGORY"
#define MAXMARK "MAXMARK"
#define WEIGHT "WEIGHT"
#define WDRN "WDR"

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
      std::string D;
      std::string F;
      std::string INC;
      std::string WDR;

      Echelon()
         : high_A("A+") , mid_A("A") , low_A("A-")
           , high_B("B+") , mid_B("B") , low_B("B-")
           , high_C("C+") , mid_C("C") , low_C("C-")
           , D("D")
           , F("F")
           , WDR("WDR")

      { /* Not needed */ }
   };
};

#endif
