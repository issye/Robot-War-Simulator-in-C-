/***|***|****|
Program: Battlefield.h
Course: Object Oriented Programming and Data Structures
Trimester: 2410
Name: Adriana binti Meor Azman
ID: 1211111079
Email: 1211111079@student.mmu.edu.my
Phone: 016-7199579
Name: Issye Lailiyah Binti Sopingi  
ID: 1231303279  
Email: 1231303279@student.mmu.edu.my
Phone: 014-3277626
Name: Zulaikha Afzan Binti Bee Wan  
ID: 1221102418  
Email: 1221102418@student.mmu.edu.my
Phone: 014-9738597
Name: Rahaf Khalid Hamed Mohamed Khier  
ID: 1221303108  
Email: 1221303108@student.mmu.edu.my
Phone: 011-62164425
Lecture Section: TC1L
Tutorial Section: TT4L
***|***|****/

#ifndef STEPPINGROBOT_H
#define STEPPINGROBOT_H
#include "Robot.h"
using namespace std;

// Declares that steppingRobot inherits from robot
class SteppingRobot : virtual public Robot 
{
public:
    // Constructor
    SteppingRobot(int x, int y, string name, char symbol, Battlefield* battlefield)
        : Robot(x, y, name, symbol, battlefield) {}

    // Pure virtual function
    virtual void step() = 0; 
};
#endif