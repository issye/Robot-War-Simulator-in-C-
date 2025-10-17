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

#ifndef ROBOT_H
#define ROBOT_H
using namespace std;

class Battlefield;

class Robot {
private:
    int x, y;

protected:
    string name;
    char symbol;
    int lives;
    int kills;
    Battlefield *battlefield;

public:
    Robot(int x, int y, string name, char symbol, Battlefield *battlefield)
        : x(x), y(y), name(name), symbol(symbol), lives(3), kills(0), battlefield(battlefield) {}

    virtual void look(int x, int y) = 0;
    virtual void move() = 0;
    virtual void fire(int x, int y) = 0;
    virtual void step() = 0;
    
    
    void resetLives() { lives = 3; }
    void resetKills() { kills = 0; }

    void setSymbol(char s) { symbol = s; }
    void setLives(int l) { lives = l; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    void setKills(int k) { kills = k; }

    int getLives() const { return lives; }
    int getX() const { return x; }
    int getY() const { return y; }
    string getName() const { return name; }
    int getKills() const { return kills; }
    char getSymbol() const { return symbol; }

    virtual ~Robot() {}
};

#endif