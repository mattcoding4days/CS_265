#ifndef SETTINGS_H
#define SETTINGS_H


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
#define TEMPFILE ".temp"
#define SANITIZE "rm .temp"
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
      const char *RED;
      const char *GREEN;
      const char *YELLOW;
      const char *BLUE;
      const char *RESET;

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
      const char *high_A;
      const char *mid_A;
      const char *low_A;
      const char *high_B;
      const char *mid_B;
      const char *low_B;
      const char *high_C;
      const char *mid_C;
      const char *low_C;
      const char *D;
      const char *F;
      const char *INC;
      const char *WDR;

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
