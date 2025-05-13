#include "baseclasses.h"

Unit::Unit(string n, float h, int ap, int c, bool heavy) :  //constructor
    name(n), health(h), attackPower(ap), cost(c), isHeavy(heavy) {}

Unit::~Unit() {}

string Unit::getName() const { return name; } //Getters and setters
float Unit::getHealth() const { return health; }
int Unit::getAttackPower() const { return attackPower; }
int Unit::getCost() const { return cost; }
bool Unit::getIsHeavy() const { return isHeavy; }

void Unit::takeDamage(float damage) { health -= damage; }

ostream& operator<<(ostream& os, const Unit& unit) { // Overloading the << operator to output unit details
    os << unit.name << " [HP: " << unit.health << " ATK: " << unit.attackPower << "]";
    return os;
}

Faction::Faction(string n, int r) : name(n), resources(r), armySize(0), armyCapacity(5) { //constructor
    army = new Unit*[armyCapacity]; //gives an army of size 5
}

Faction::~Faction() { //destructor
    for (int i = 0; i < armySize; i++) {
        delete army[i];
    }
    delete[] army;
}

void Faction::expandArmy() {
    armyCapacity = (armyCapacity<<1); //Expand by 2 times
    Unit** newArmy = new Unit*[armyCapacity];
    for (int i = 0; i < armySize; i++) { //copue old army to new army
        newArmy[i] = army[i];
    }
    delete[] army;
    army = newArmy; // Update the pointer to the new army
}

string Faction::getName() const { return name; } //getters and setters
int Faction::getResources() const { return resources; }
int Faction::getArmySize() const { return armySize; }

Unit* Faction::getUnit(int index) const { //get unit at index
    if (index >= 0 && index < armySize) 
    return army[index];
    else
    return nullptr;
} 

void Faction::addResources(int amount) { resources += amount; } //add resources

bool Faction::spendResources(int amount) { //spend resources
    if (resources >= amount) { //validation for resources
        resources -= amount;
        return true;
    }
    return false;
}

void Faction::addUnit(Unit* unit) { //add unit to army
    if (spendResources(unit->getCost())) { 
        if (armySize == armyCapacity) { //expand army if full
            expandArmy();
        }
        army[armySize++] = unit; // Add unit to army
    } else {
        cout << "Not enough resources!";
        delete unit;
    }
}

void Faction::removeUnit(int index) { //remove unit from army
    if (index < 0 || index >= armySize) return;
    delete army[index];
    for (int i = index; i < armySize-1; i++) { // Shift units left
        army[i] = army[i+1];
    }
    armySize--;
}

void Faction::displayArmy() const {
    cout << "\n" << name << " Army:"; 
    for (int i = 0; i < armySize; i++) {
        cout << "\n" << i << ": " << *army[i]; // Display unit details
    }
}

int Faction::calculateTotalAttackPower() const {
    int total = 0;
    for (int i = 0; i < armySize; i++) {
        total += army[i]->getAttackPower(); // Calculate total attack power, add up all units attack power
    }
    return total;
}

void Faction::distributeDamage(float totalDamage) {
    int heavyCount = 0;
    int normalCount = 0;
    float heavyDamage, normalDamage;
    for (int i = 0; i < armySize; i++) {
        if (army[i]->getIsHeavy()) heavyCount++;
        else normalCount++;
    }
    if (heavyCount!=0 && normalCount!=0){ //checks for both heavy and normal units are present{
     heavyDamage = totalDamage * 0.8f;
     normalDamage = totalDamage * 0.2f;
    }
    else if (heavyCount==0){
        heavyDamage = 0;
        normalDamage = totalDamage;
    }
    else if (normalCount==0){
        heavyDamage = totalDamage;
        normalDamage = 0;
    } //                }
    for (int i = 0; i < armySize; i++) {
        if (army[i]->getIsHeavy()) {
            float damage = heavyDamage / max(1, heavyCount); // Calculate damage per heavy unit. Max function is from library algorithm, divides by the left parameter instead of the righ parameter if the left parameter is smaller
            // to avoid division by zero
            army[i]->takeDamage(damage); 
            cout << "\n" << army[i]->getName() << " takes " << damage << " damage (heavy unit)";
        } else {
            float damage = normalDamage / max(1, normalCount); //same thing done for heavy units but for normal ones here
            army[i]->takeDamage(damage);
            cout << "\n" << army[i]->getName() << " takes " << damage << " damage (normal unit)";
        }
    }
    
    for (int i = armySize-1; i >= 0; i--) {
        if (army[i]->getHealth() <= 0) {
            cout << "\n" << army[i]->getName() << " has been destroyed!";
            removeUnit(i); //removes unit at index if health is 0
        }
    }
}