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
#include <fstream>    // For file operations
#include <sstream>    // For string stream operations
#include <string>
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time() to seed the random number generator
#include <vector>
#include <limits>     // ** NEW INCLUDE FOR THE FIX **

// === NEW INCLUDES FOR LOGGING ===
#include <streambuf> // For implementing the tee buffer
#include <chrono>    // For getting a timestamp
#include <iomanip>   // For formatting the timestamp
// ================================
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

// === NEW CODE FOR LOGGING ===

// A custom stream buffer that duplicates output to two other stream buffers.
class TeeBuffer : public std::streambuf {
private:
    std::streambuf* sb1;
    std::streambuf* sb2;

public:
    TeeBuffer(std::streambuf* streambuf1, std::streambuf* streambuf2)
        : sb1(streambuf1), sb2(streambuf2) {}

protected:
    // This function is called when the buffer is full and needs to write a character.
    virtual int overflow(int c) {
        if (c == EOF) {
            return !EOF;
        }

        // Write the character to both underlying buffers
        int const r1 = sb1->sputc(c);
        int const r2 = sb2->sputc(c);

        // If either write failed, signal an error by returning EOF
        if (r1 == EOF || r2 == EOF) {
            return EOF;
        }

        return c;
    }

    // This function is called to flush the buffer's contents.
    virtual int sync() {
        // Sync both underlying buffers
        int const r1 = sb1->pubsync();
        int const r2 = sb2->pubsync();
        // Return 0 on success, -1 on failure
        return (r1 == 0 && r2 == 0) ? 0 : -1;
    }
};

// An RAII (Resource Acquisition Is Initialization) class to manage stream redirection.
// It redirects streams in its constructor and restores them in its destructor,
// ensuring cleanup happens automatically when the object goes out of scope.
struct StreamRedirector {
    std::ofstream& log_file_stream;
    TeeBuffer cout_tee;
    TeeBuffer cerr_tee;
    std::streambuf* original_cout_buf;
    std::streambuf* original_cerr_buf;

    StreamRedirector(std::ofstream& log_file) :
        log_file_stream(log_file),
        cout_tee(std::cout.rdbuf(), log_file.rdbuf()),
        cerr_tee(std::cerr.rdbuf(), log_file.rdbuf()),
        original_cout_buf(std::cout.rdbuf(&cout_tee)), // Redirect cout and save original
        original_cerr_buf(std::cerr.rdbuf(&cerr_tee))  // Redirect cerr and save original
    {}

    ~StreamRedirector() {
        // Restore original stream buffers
        std::cout.rdbuf(original_cout_buf);
        std::cerr.rdbuf(original_cerr_buf);
    }
};
// ============================

using namespace std;

int main() {
    // === LOGGING SETUP ===
    // Generate a timestamp for the log file name
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    // Note: std::localtime is not thread-safe, but is sufficient for this single-threaded application.
    ss << "battle_log_" << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << ".txt";
    std::string log_filename = ss.str();

    // Open the log file for writing
    std::ofstream log_file(log_filename);
    if (!log_file.is_open()) {
        // If we can't open the log, write to the original cerr and exit.
        std::cerr << "FATAL ERROR: Could not open log file: " << log_filename << std::endl;
        return 1;
    }

    // Create the RAII object to handle redirection.
    // Redirection starts here and will be automatically cleaned up when main exits.
    StreamRedirector redirector(log_file);
    // ======================

    // Open the configuration file "config.txt"
    ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        cerr << "Error opening config.txt" << endl;
        return 1; // Exit if the file cannot be opened
    }

    int m, n, steps, numRobots;
    string line;

    // Read battlefield dimensions
    getline(configFile, line);
    if (sscanf(line.c_str(), "M by N : %d %d", &m, &n) != 2) {
        cerr << "Error reading battlefield dimensions" << endl;
        return 1; // Exit if the dimensions cannot be read
    }

    // Read number of steps for the simulation
    getline(configFile, line);
    if (sscanf(line.c_str(), "steps: %d", &steps) != 1) {
        cerr << "Error reading number of steps" << endl;
        return 1; // Exit if the number of steps cannot be read
    }

    // Read number of robots
    getline(configFile, line);
    if (sscanf(line.c_str(), "robots: %d", &numRobots) != 1) {
        cerr << "Error reading number of robots" << endl;
        return 1; // Exit if the number of robots cannot be read
    }

    // Create the battlefield with the given dimensions and steps
    Battlefield battlefield(m, n, steps);

    // Read robot information from the configuration file and create robot objects
    for (int i = 0; i < numRobots; ++i) {
        getline(configFile, line);
        istringstream iss(line);
        string robotType, name;
        string xStr, yStr;
        int x, y;

        // Parse robot type, name, and coordinates
        if (!(iss >> robotType >> name >> xStr >> yStr)) {
            cerr << "Error reading robot information: " << line << endl;
            return 1; // Exit if robot information cannot be read
        }

        // Determine x-coordinate
        if (xStr == "random") {
            x = rand() % m; // Generate random x-coordinate within battlefield width
        } else {
            x = stoi(xStr); // Convert string to integer
        }

        // Determine y-coordinate
        if (yStr == "random") {
            y = rand() % n; // Generate random y-coordinate within battlefield height
        } else {
            y = stoi(yStr); // Convert string to integer
        }

        // Create robot based on the type and add to the battlefield
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
            return 1; // Exit if an invalid robot type is encountered
        }
    }

    configFile.close(); // Close the configuration file

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    
    cout << "Starting simulation. Log will be saved to " << log_filename << endl;
    battlefield.simulate(); // Start the battlefield simulation

    // Add these lines to pause the console before exiting
    cout << "\n\nPress Enter to exit the simulation...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
    cin.get(); // Wait for the user to press Enter
    
    return 0;
}
