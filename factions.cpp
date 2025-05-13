#include "derivedclasses.h"
#include "combat.h"
#include "baseclasses.h"
#include <iostream>
#include <cstdlib>
#include "factions.h"
#include "missions.h"

HumanFaction::HumanFaction(int startResources) : Faction("Humans", startResources) {}

void HumanFaction::gatherResources() {
     int gatheredresource= rand()%60+1;
    addResources(gatheredresource); 
}


AlienFaction::AlienFaction(int startResources) : Faction("Aliens", startResources) {}

void AlienFaction::gatherResources() {
    int gatheredresource= rand()%60+1;
    addResources(gatheredresource); 
}
void HumanFaction::recruitMenu() {
    bool recruiting = true;
    
    while (recruiting && resources > 0) {
        cout << "\n\nHuman Recruitment (Resources: " << resources << ")";
        cout << "\n1. Rifleman (20 resources)";
        cout << "\n2. Tank (35 resources)";
        cout << "\n3. Finish recruiting";
        cout << "\nEnter choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                const int unitCost = 20;
                cout << "How many Riflemen? (Each costs " << unitCost << "): ";
                int quantity;
                cin >> quantity;
                
                // Validate quantity
                if (quantity <= 0) {
                    cout << "Invalid quantity!";
                    break;
                }
                
                 int totalCost = unitCost * quantity;
                
                
                if (totalCost > resources) {
                    cout << "Cannot afford " << quantity << " Riflemen! (Need: " << totalCost << ", Have: " << resources << ")";
                    break;
                }
                
                // Ensure army capacity
                while (armySize + quantity > armyCapacity) {
                    expandArmy();
                }
                
                // Deduct resources
                resources -= totalCost;
                
                // Add units without spending
                for (int i = 0; i < quantity; i++) {
                    army[armySize++] = new Rifleman();
                }
                cout << "Successfully recruited " << quantity << " Riflemen";
                break;
            }
            case 2: {
                const int unitCost = 35;
                cout << "How many Tanks? (Each costs " << unitCost << "): ";
                int quantity;
                cin >> quantity;
                
                if (quantity <= 0) {
                    cout << "Invalid quantity!";
                    break;
                }
                
                 int totalCost = unitCost * quantity;
                
                if (totalCost > resources) {
                    cout << "Cannot afford " << quantity << " Tanks! (Need: " << totalCost << ", Have: " << resources << ")";
                    break;
                }
                
                while (armySize + quantity > armyCapacity) {
                    expandArmy();
                }
                
                resources -= totalCost;
                for (int i = 0; i < quantity; i++) {
                    army[armySize++] = new Tank();
                }
                cout << "Successfully recruited " << quantity << " Tanks";
                break;
            }
            case 3:
                recruiting = false;
                break;
            default:
                cout << "Invalid choice!";
        }
    }
}

void AlienFaction::recruitMenu() {
    bool recruiting = true;
    
    while (recruiting && resources > 0) {
        cout << "\n\nAlien Recruitment (Resources: " << resources << ")";
        cout << "\n1. Zorg (20 resources)";
        cout << "\n2. Clanker (35 resources)";
        cout << "\n3. Finish recruiting";
        cout << "\nEnter choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                const int unitCost = 20;
                cout << "How many Zorgs? (Each costs " << unitCost << "): ";
                int quantity;
                cin >> quantity;
               
                if (quantity <= 0) {
                    cout << "Invalid quantity!";
                    break;
                }
                
                 int totalCost = unitCost * quantity;
                
                if (totalCost > resources) {
                    cout << "Cannot afford " << quantity << " Zorgs! (Need: "<< totalCost << ", Have: " << resources << ")";
                    break;
                }
                
                while (armySize + quantity > armyCapacity) {
                    expandArmy();
                }
                
                resources -= totalCost;
                for (int i = 0; i < quantity; i++) {
                    army[armySize++] = new Zorg();
                }
                cout << "Successfully recruited " << quantity << " Zorgs";
                break;
            }
            case 2: {
                const int unitCost = 35;
                cout << "How many Clankers? (Each costs " << unitCost << "): ";
                int quantity;
                std::cin >> quantity;
                
                if (quantity <= 0) {
                    std::cout << "Invalid quantity!";
                    break;
                }
                
                const int totalCost = unitCost * quantity;
                
                if (totalCost > resources) {
                    std::cout << "Cannot afford " << quantity << " Clankers! (Need: " 
                              << totalCost << ", Have: " << resources << ")";
                    break;
                }
                
                while (armySize + quantity > armyCapacity) {
                    expandArmy();
                }
                
                resources -= totalCost;
                for (int i = 0; i < quantity; i++) {
                    army[armySize++] = new Clanker();
                }
                std::cout << "Successfully recruited " << quantity << " Clankers";
                break;
            }
            case 3:
                recruiting = false;
                break;
            default:
                std::cout << "Invalid choice!";
        }
    }
}
