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

#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include <iostream>
#include <string>
#include "Robot.h"
#include "Battlefield.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"

using namespace std;

class UltimateRobot : public virtual MovingRobot, public virtual SteppingRobot, public virtual SeeingRobot, public virtual ShootingRobot {
private:
    string enemyName;
    bool enemyFound;
    int enemyX, enemyY;

public:
    UltimateRobot(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          MovingRobot(initX, initY, name, name[0], battlefield),
          SteppingRobot(initX, initY, name, name[0], battlefield),
          SeeingRobot(initX, initY, name, name[0], battlefield),
          ShootingRobot(initX, initY, name, name[0], battlefield),
          enemyFound(false), enemyX(0), enemyY(0) {}

    void look(int x, int y) override {
        int startX = getX() - 1;
        int startY = getY() - 1;
        int endX = getX() + 1;
        int endY = getY() + 1;

        // Check if the 3x3 grid is within the battlefield boundaries
        if (startX < 0) startX = 0;
        if (startY < 0) startY = 0;
        if (endX >= battlefield->getWidth()) endX = battlefield->getWidth() - 1;
        if (endY >= battlefield->getHeight()) endY = battlefield->getHeight() - 1;

        // Check if the 3x3 grid has an enemy robot
        enemyFound = false;
        for (int i = startX; i <= endX; i++) {
            for (int j = startY; j <= endY; j++) {
                if (battlefield->hasRobotAt(i, j) && battlefield->getRobotAt(i, j)->getName() != getName()) {
                    cout << name << " is looking around and found enemy robot " << battlefield->getRobotAt(i, j)->getName() << endl;
                    enemyFound = true;
                    enemyY = j;
                    break; // Exit the inner loop if an enemy is found
                }
            }
            if (enemyFound) {
                enemyX = i;
                break; // Exit the outer loop if an enemy is found
            }
        }

        if (!enemyFound) {
            cout << name << " is looking around its immediate neighborhood." << endl;
        }
    }

    void move() override {
       int newX = getX();
        int newY = getY();
        int direction;

        if (enemyFound) { // If an enemy was found during look()
            newX = enemyX;
            newY = enemyY;
            enemyName = battlefield->getRobotAt(enemyX,enemyY)->getName();
            battlefield->removeRobotAt(enemyX, enemyY);
        } else { // If no enemy was found, move randomly
            do {
                direction = rand() % 8; // Generate a random number between 0 and 7

                switch (direction) {
                    case 0:
                        newY--; // Up
                        break;
                    case 1:
                        newY++; // Down
                        break;
                    case 2:
                        newX--; // Left
                        break;
                    case 3:
                        newX++; // Right
                        break;
                    case 4:
                        newX--; // Up Left
                        newY--;
                        break;
                    case 5:
                        newX++; // Up Right
                        newY--;
                        break;
                    case 6:
                        newX--; // Down Left
                        newY++;
                        break;
                    case 7:
                        newX++; // Down Right
                        newY++;
                        break;
                }
                // Check if the new position is within the battlefield boundaries
            } while (newX < 0 || newX >= battlefield->getWidth() || newY < 0 || newY >= battlefield->getHeight());
        }
        // If a valid move is found, update the robot's position
        cout << name << " moved to (" << newX << ", " << newY << ")" << endl;
        
        battlefield->updatePosition(getX(), getY(), newX, newY);
    }

    void step() override {
 if (enemyFound) {
        cout << name << " is stepping over enemy robot " << enemyName << endl;
        kills++;
 }
            }

    void fire(int x, int y) override {
        int shotsFired = 0; // Keep track of shots fired

        while (shotsFired < 3) {
            if (x >= 0 && x < battlefield->getWidth() && y >= 0 && y < battlefield->getHeight()) {
                if (battlefield->hasRobotAt(x, y) && battlefield->getRobotAt(x, y)->getName() != getName()) {
                    cout << name << " killed " << battlefield->getRobotAt(x, y)->getName() << "!" << endl;
                    kills++;
                    battlefield->removeRobotAt(x, y); // Remove the enemy robot
                    shotsFired++; // Increment shotsFired if a valid shot is taken
                } else if (battlefield->hasRobotAt(x, y) && battlefield->getRobotAt(x, y)->getName() == getName()) {
                    cout << name << " cannot fire at itself!" << endl;
                } else {
                    cout << name << " fired at an empty location." << endl;
                    shotsFired++; // Increment shotsFired even if it's an empty location
                }
            } else {
                cout << name << " cannot fire outside the battlefield boundaries." << endl;
            }

            // Generate new x and y for the next shot
            x = rand() % battlefield->getWidth();
            y = rand() % battlefield->getHeight();
        }
    }
};

#endif