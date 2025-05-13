#include "combat.h"
#include <iostream>

void CombatSystem::attack(Faction& attacker, Faction& defender) { 
    int totalAttack = attacker.calculateTotalAttackPower(); // Calculate total attack power of the attacker
    int defenderCount = defender.getArmySize(); // Get the number of defenders
    
    if (defenderCount == 0) 
    return;
    
    float totalDamage = float(totalAttack) / defenderCount; // Calculate damage per defender unit
    
    cout << "\n\n" << attacker.getName() << " forces attack with total power: " << totalAttack;
    cout << "\nTotal damage to distribute: " << totalDamage << " per defender unit";
    cout << "\nDamage distribution: 70% to heavy units, 30% to normal units";
    
    defender.distributeDamage(totalDamage); // Distribute damage to defender units
    
    cout << "\n\nRemaining " << defender.getName() << " forces:";
    defender.displayArmy();
}

void CombatSystem::processRound(Faction& f1, Faction& f2, int roundNumber) { // Process a round of combat between two factions
    cout << "\n\n=== ROUND " << roundNumber << " ===";
    
    cout << "\n\n-- Resource Phase --";
    f1.gatherResources();
    f2.gatherResources();
    cout << "\n" << f1.getName() << " resources: " << f1.getResources();
    cout << "\n" << f2.getName() << " resources: " << f2.getResources();
    cout << "\n\n-- Combat Phase --";
    attack(f1, f2); // Attack from factipn1 to faction2
    attack(f2, f1); // Attack from faction2 to faction1
}