/**********|**********|**********|
Program: RoboCop.h
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
**********|**********|**********/

#ifndef ROBOCOP_H
#define ROBOCOP_H

#include <iostream>
#include <string>
#include "Robot.h"
#include "Battlefield.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"

class TerminatorRoboCop; // Forward declaration of TerminatorRoboCop class

using namespace std;

// RoboCop class inherits from MovingRobot, ShootingRobot, and SeeingRobot classes
class RoboCop : public virtual MovingRobot, public virtual ShootingRobot, public virtual SeeingRobot {
public:
    // Constructor initializes the RoboCop with given position, name, and battlefield reference
    RoboCop(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          MovingRobot(initX, initY, name, name[0], battlefield),
          ShootingRobot(initX, initY, name, name[0], battlefield),
          SeeingRobot(initX, initY, name, name[0], battlefield) {}

    // Method to upgrade RoboCop to TerminatorRoboCop
    void upgradeToTerminatorRoboCop(Robot*& terminatorRoboCop);

    // Override the look method from SeeingRobot class
    void look(int x, int y) override {
        cout << name << " is looking around from its current position.\n";
    }

    // Override the move method from MovingRobot class
    void move() override {
        int oldX, oldY, newX, newY;
        oldX = newX = getX();
        oldY = newY = getY();
        int direction;

        do {
            direction = rand() % 8; // Generate a random number between 0 and 7 for direction

            switch (direction) {
                case 0: newY--; break; // Move up
                case 1: newY++; break; // Move down
                case 2: newX--; break; // Move left
                case 3: newX++; break; // Move right
                case 4: newX--; newY--; break; // Move up-left
                case 5: newX++; newY--; break; // Move up-right
                case 6: newX--; newY++; break; // Move down-left
                case 7: newX++; newY++; break; // Move down-right
            }
            // Ensure the new position is within battlefield boundaries and doesn't contain an enemy robot
        } while (newX < 0 || newX >= battlefield->getWidth() || newY < 0 || newY >= battlefield->getHeight() ||
                (battlefield->hasRobotAt(newX, newY) && battlefield->getRobotAt(newX, newY)->getName() != getName()));

        // Update the robot's position if a valid move is found
        battlefield->updatePosition(this, oldX, oldY, newX, newY);
        cout << name << " moved to (" << newX << ", " << newY << ")" << endl;
    }

    // Override the step method from MovingRobot class
    void step() override {}

    // Override the fire method from ShootingRobot class
    void fire(int x, int y) override {
        int shotsFired = 0; // Keep track of the number of shots fired

        while (shotsFired < 3) { // Allow up to 3 shots
            if (x >= 0 && x < battlefield->getWidth() && y >= 0 && y < battlefield->getHeight()) {
                if (battlefield->hasRobotAt(x, y) && battlefield->getRobotAt(x, y)->getName() != getName()) {
                    cout << name << " killed " << battlefield->getRobotAt(x, y)->getName() << "!" << endl;
                    kills++;
                    battlefield->removeRobotAt(x, y); // Remove the enemy robot

                    if (kills >= 3) {
                        resetKills(); // Reset kills
                        Robot* terminatorRoboCop = nullptr;
                        upgradeToTerminatorRoboCop(terminatorRoboCop); // Upgrade to TerminatorRoboCop
                        return;
                    }
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