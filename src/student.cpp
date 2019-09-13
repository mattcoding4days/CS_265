#include <iostream>
#include <string>
#include "student.hpp"

namespace Grades
{
   /* Defualt Constructor */
   Student::Student()
      : category("")
      , title("")
      , maxMark("")
      , mark("")
   { }

   /* Getters and Setters */
   const std::string& Student::getCategory() const { return category; }

   void Student::setCategory(const std::string& mCategory)
   {
      category = mCategory;
   }

   const std::string& Student::getTitle() const { return title; }

   void Student::setTitle(const std::string& mTitle)
   {
      title = mTitle;
   }

   const std::string& Student::getMaxMark() const { return maxMark; }

   void Student::setMaxMark(const std::string& mMaxMark)
   {
      maxMark = mMaxMark;
   }

   const std::string& Student::getMark() const { return mark; }

   void Student::setMark(const std::string& mMark)
   {
      mark = mMark;
   }
   
   void Student::printInformation() const
   {
      std::cout << "\n Information" << std::endl;
      std::cout << "+============+" << std::endl;
      std::cout << "Category: " << this->getCategory() << std::endl;
      std::cout << "Title: " << this->getTitle() << std::endl;
      std::cout << "Max Mark: " << this->getMaxMark() << std::endl;
      std::cout << "Student Marks: : " << this->getMark() << std::endl;
   }
};

using namespace Grades;

/* Prototypes */
int getGenericIntegerInput(const std::string&);
std::string getGenericStringInput(const std::string);
Student& getInformation(Student& stu);


/* init main routine */
int main()
{
   Student student;
   
   getInformation(student);
   student.printInformation();
   return 0;
}

/* Definitions
 * */
int getGenericSize(const std::string& prompt)
{
   BUFFER input;
   std::cout << prompt;
   std::getline(std::cin, input);
   int size = std::stoi(input);
   return size;
}

std::string getGenericStringInput(const std::string prompt)
{
   BUFFER input;
   std::cout << prompt;
   std::getline(std::cin, input);
   return input;
}

Student& getInformation(Student& stu)
{
   std::string category = getGenericStringInput("Enter Category: ");
   stu.setCategory(category);

   std::string title = getGenericStringInput("Enter Title: ");
   stu.setTitle(title);

   std::string maxMark = getGenericStringInput("Enter max possible mark: ");
   stu.setMaxMark(maxMark);

   std::string mark = getGenericStringInput("Enter Student Marks: ");
   stu.setMark(mark);
   return stu;
}
