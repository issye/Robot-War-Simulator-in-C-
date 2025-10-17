/**********|**********|**********|
Program: main.cpp
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Battlefield.h"
#include "Robot.h"
#include "TerminatorRoboCop.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "BlueThunder.h"
#include "MadBot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"

using namespace std;

int main() {
    ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        cerr << "Error opening config.txt" << endl;
        return 1;
    }

    int m, n, steps, numRobots;
    string line;

    getline(configFile, line);
    if (sscanf(line.c_str(), "M by N : %d %d", &m, &n) != 2) {
        cerr << "Error reading battlefield dimensions" << endl;
        return 1;
    }

    getline(configFile, line);
    if (sscanf(line.c_str(), "steps: %d", &steps) != 1) {
        cerr << "Error reading number of steps" << endl;
        return 1;
    }

    getline(configFile, line);
    if (sscanf(line.c_str(), "robots: %d", &numRobots) != 1) {
        cerr << "Error reading number of robots" << endl;
        return 1;
    }

    Battlefield battlefield(m, n, steps);

    for (int i = 0; i < numRobots; ++i) {
        getline(configFile, line);
        istringstream iss(line);
        string robotType, name;
        string xStr, yStr;
        int x, y;

        if (!(iss >> robotType >> name >> xStr >> yStr)) {
            cerr << "Error reading robot information: " << line << endl;
            return 1;
        }

        if (xStr == "random") {
            x = rand() % m;
        } else {
            x = stoi(xStr);
        }

        if (yStr == "random") {
            y = rand() % n;
        } else {
            y = stoi(yStr);
        }

        if (robotType == "TerminatorRoboCop") {
            battlefield.addRobot(new TerminatorRoboCop(x, y, name, &battlefield));
        } else if (robotType == "RoboCop") {
            battlefield.addRobot(new RoboCop(x, y, name, &battlefield));
        } else if (robotType == "Terminator") {
            battlefield.addRobot(new Terminator(x, y, name, &battlefield));
        } else if (robotType == "BlueThunder") {
            battlefield.addRobot(new BlueThunder(x, y, name, &battlefield));
        } else if (robotType == "MadBot") {
            battlefield.addRobot(new MadBot(x, y, name, &battlefield));
        } else if (robotType == "RoboTank") {
            battlefield.addRobot(new RoboTank(x, y, name, &battlefield));
        } else if (robotType == "UltimateRobot") {
            battlefield.addRobot(new UltimateRobot(x, y, name, &battlefield));
        } else {
            cerr << "Invalid robot type: " << robotType << endl;
            return 1;
        }
    }

    configFile.close();

    srand(time(0));
    battlefield.simulate();

    return 0;
}