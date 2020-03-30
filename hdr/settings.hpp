#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace GraderApplication
{
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

  /* Define a Debug flag here, Debug enabled print statements
   * at important bottle neck points in the software still need
   * to be implemented
   *
   * To turn Debug logging off change macro to 1
   * To turn on change to 0
   * */
#define DEBUG 0

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

  /* NOTE: Documentaion
   * File delimiters, or characters we want to ignore, or look for 
   * when parsing the file 
   * */
  enum Delim 
  {
    WS = ' ',
    COMM = '#',
    TAB = '\t'
  };

  struct Colors
  {
    const char *Black;
    const char *Red;
    const char *Green;
    const char *Yellow;
    const char *Blue;
    const char *Purple;
    const char *Cyan;
    const char *White;   
    const char *BBlack;
    const char *BRed;
    const char *BGreen;
    const char *BYellow;
    const char *BBlue;
    const char *BPurple;
    const char *BCyan;
    const char *BWhite;
    const char *Reset;

    /* Default constructor for Ansi escape color codes */
    Colors(void)
      : Black("\033[0;30m")  
        ,Red("\033[0;31m")
        ,Green("\033[0;32m")  
        ,Yellow("\033[0;33m")
        ,Blue("\033[0;34m")
        ,Purple("\033[0;35m") 
        ,Cyan("\033[0;36m")
        ,White("\033[0;37m") 
        ,BBlack("\033[1;30m") 
        ,BRed("\033[1;31m")
        ,BGreen("\033[1;32m") 
        ,BYellow("\033[1;33m")
        ,BBlue("\033[1;34m")
        ,BPurple("\033[1;35m")
        ,BCyan("\033[1;36m")
        ,BWhite("\033[1;37m") 
        ,Reset("\033[0m")

    { /* not needed */  }
  };


  /* NOTE: Documentaion
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
