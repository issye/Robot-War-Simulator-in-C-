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

#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
#include <iostream>
using namespace std;

void Terminator::upgradeToTerminatorRoboCop(Robot*& terminatorRoboCop) 
{
    Robot* oldRobot = this;

    terminatorRoboCop = new TerminatorRoboCop(getX(), getY(), getName(), battlefield);

    terminatorRoboCop->setLives(getLives());

    cout << getName() << " has upgraded to TerminatorRoboCop!" << endl;

    battlefield->addRobot(terminatorRoboCop);   
    battlefield->markRobotForRemoval(oldRobot); 
}