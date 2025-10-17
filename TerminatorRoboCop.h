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

#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include <iostream>
#include <string>
#include "Battlefield.h"
#include "Robot.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "SteppingRobot.h"

class UltimateRobot;

class TerminatorRoboCop : public RoboCop, public Terminator {
private:

public:
    TerminatorRoboCop(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          RoboCop(initX, initY, name, battlefield),
          Terminator(initX, initY, name, battlefield),
          MovingRobot(initX, initY, name, name[0], battlefield),
          ShootingRobot(initX, initY, name, name[0], battlefield),
          SeeingRobot(initX, initY, name, name[0], battlefield),
          SteppingRobot(initX, initY, name, name[0], battlefield) {}


   void upgradeToUltimateRobot(Robot*& ultimateRobot);

    void look(int x, int y) override {
        Terminator::look(x, y);
    }

    void move() override {
        if (enemyFound) {
            int oldX = getX();
            int oldY = getY();
            if (battlefield->hasRobotAt(enemyX, enemyY)) {
                enemyName = battlefield->getRobotAt(enemyX, enemyY)->getName();
                battlefield->removeRobotAt(enemyX, enemyY);
            }
            cout << name << " moved to (" << enemyX << ", " << enemyY << ")" << endl;
            battlefield->updatePosition(this, oldX, oldY, enemyX, enemyY);
        } else {
            RoboCop::move();
        }
    }

   void fire(int x, int y) override {
    RoboCop::fire(x, y);
}


    void step() override {
        Terminator::step();
        if (kills >= 3){
            resetKills();
            Robot* ultimateRobot = nullptr;
            upgradeToUltimateRobot(ultimateRobot);
        }
    }
};

#endif