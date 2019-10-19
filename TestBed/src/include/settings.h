#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

/* XXX: Documentaion
 * Max line length expected after the name postfix is read in. 
 * */
const int LEN = 8;

/* XXX: Documentaion
 * An assumption of the number of students the file will contain,
 * this is so we can reserve space in the vector that will hold
 * all student objects, so the code is much faster than the vector
 * having to constantly resize its self when it adds a student.
 *
 * vector will also use emplace_back instead of push_back, to mitigate 
 * costly copy constructor calls
 * */
const int NUM_STUDENT_ASSUMPTION = 30;

/* XXX: Documentaion
 * File delimiters, or characters we want to ignore, or look for 
 * when parsing the file 
 * */
enum Delim 
{
   WS = ' ',
   COMM = '#'
};

/* XXX: Documentaion
 * Enum for letter grade representation the student will recieve 
 * */
enum LetterGrade
{
   A = 'A',
   B = 'B',
   C = 'C',
   D = 'D',
   F = 'F'
};

/* XXX: Documentaion
 * Colors set by the default constructor, just for better program readabillity 
 * */
struct Colors
{
   const std::string RED;
   const std::string GREEN;
   const std::string YELLOW;
   const std::string BLUE;
   const std::string RESET;
   
   /* Fill in with ANSI color escape codes later */
   Colors()
      : RED("")
      , GREEN("")
      , YELLOW("")
      , BLUE("")
      , RESET("")
   { }
};

#endif
