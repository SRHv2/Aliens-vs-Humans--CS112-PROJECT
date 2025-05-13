#ifndef BASECLASSES_H
#define BASECLASSES_H
using namespace std;
#include <iostream>
#include <algorithm>
#include <string>
class Unit {
protected:
    string name;
    float health;
    int attackPower;
    int cost;
    bool isHeavy;
public:
    Unit(string n, float h, int ap, int c, bool heavy);
    virtual ~Unit();
    
    string getName() const;
    float getHealth() const;
    int getAttackPower() const;
    int getCost() const;
    bool getIsHeavy() const;
    
    void takeDamage(float damage);
    
    friend ostream& operator<<(ostream& os, const Unit& unit);
};

class Faction {
protected:
    string name;
    int resources;
    Unit** army;
    int armySize;
    int armyCapacity;
    
    void expandArmy();
public:
    Faction(string n, int r);
    virtual ~Faction();
    
    string getName() const;
    int getResources() const;
    int getArmySize() const;
    Unit* getUnit(int index) const;
    
    void addResources(int amount);
    bool spendResources(int amount);
    void addUnit(Unit* unit);
    void removeUnit(int index);
    void displayArmy() const;
    
    int calculateTotalAttackPower() const;
    void distributeDamage(float totalDamage);
    
    virtual void recruitMenu() = 0;
    virtual void gatherResources() = 0;
};

#endif  