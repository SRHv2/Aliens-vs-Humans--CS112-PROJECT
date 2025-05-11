#include "baseclasses.h"

Unit::Unit(string n, float h, int ap, int c, bool heavy) : 
    name(n), health(h), attackPower(ap), cost(c), isHeavy(heavy) {}

Unit::~Unit() {}

string Unit::getName() const { return name; }
float Unit::getHealth() const { return health; }
int Unit::getAttackPower() const { return attackPower; }
int Unit::getCost() const { return cost; }
bool Unit::getIsHeavy() const { return isHeavy; }

void Unit::takeDamage(float damage) { health -= damage; }

ostream& operator<<(ostream& os, const Unit& unit) {
    os << unit.name << " [HP: " << unit.health << " ATK: " << unit.attackPower << "]";
    return os;
}

Faction::Faction(string n, int r) : name(n), resources(r), armySize(0), armyCapacity(5) {
    army = new Unit*[armyCapacity];
}

Faction::~Faction() {
    for (int i = 0; i < armySize; i++) {
        delete army[i];
    }
    delete[] army;
}

void Faction::expandArmy() {
    armyCapacity = (armyCapacity<<1); //Expan by 2 times
    Unit** newArmy = new Unit*[armyCapacity];
    for (int i = 0; i < armySize; i++) {
        newArmy[i] = army[i];
    }
    delete[] army;
    army = newArmy;
}

string Faction::getName() const { return name; }
int Faction::getResources() const { return resources; }
int Faction::getArmySize() const { return armySize; }

Unit* Faction::getUnit(int index) const { 
    if (index >= 0 && index < armySize) return army[index];
    return nullptr;
} //explain

void Faction::addResources(int amount) { resources += amount; }

bool Faction::spendResources(int amount) {
    if (resources >= amount) {
        resources -= amount;
        return true;
    }
    return false;
}

void Faction::addUnit(Unit* unit) {
    if (spendResources(unit->getCost())) {
        if (armySize == armyCapacity) {
            expandArmy();
        }
        army[armySize++] = unit;
    } else {
        cout << "Not enough resources!";
        delete unit;
    }
}

void Faction::removeUnit(int index) {
    if (index < 0 || index >= armySize) return;
    delete army[index];
    for (int i = index; i < armySize-1; i++) {
        army[i] = army[i+1];
    }
    armySize--;
}

void Faction::displayArmy() const {
    cout << "\n" << name << " Army:";
    for (int i = 0; i < armySize; i++) {
        cout << "\n" << i << ": " << *army[i];
    }
}

int Faction::calculateTotalAttackPower() const {
    int total = 0;
    for (int i = 0; i < armySize; i++) {
        total += army[i]->getAttackPower();
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
    if (heavyCount!=0){
     heavyDamage = totalDamage * 0.7f;
     normalDamage = totalDamage * 0.3f;
    }
    else normalDamage=totalDamage;
    for (int i = 0; i < armySize; i++) {
        if (army[i]->getIsHeavy()) {
            float damage = heavyDamage / max(1, heavyCount);
            army[i]->takeDamage(damage);
            cout << "\n" << army[i]->getName() << " takes " << damage << " damage (heavy unit)";
        } else {
            float damage = normalDamage / max(1, normalCount);
            army[i]->takeDamage(damage);
            cout << "\n" << army[i]->getName() << " takes " << damage << " damage (normal unit)";
        }
    }
    
    for (int i = armySize-1; i >= 0; i--) {
        if (army[i]->getHealth() <= 0) {
            cout << "\n" << army[i]->getName() << " has been destroyed!";
            removeUnit(i);
        }
    }
}