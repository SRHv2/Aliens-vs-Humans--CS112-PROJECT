#include "combat.h"
#include <iostream>

void CombatSystem::attack(Faction& attacker, Faction& defender) {
    int totalAttack = attacker.calculateTotalAttackPower();
    int defenderCount = defender.getArmySize();
    
    if (defenderCount == 0) return;
    
    float totalDamage = float(totalAttack) / defenderCount;
    
    cout << "\n\n" << attacker.getName() << " forces attack with total power: " << totalAttack;
    cout << "\nTotal damage to distribute: " << totalDamage << " per defender unit";
    cout << "\nDamage distribution: 70% to heavy units, 30% to normal units";
    
    defender.distributeDamage(totalDamage);
    
    cout << "\n\nRemaining " << defender.getName() << " forces:";
    defender.displayArmy();
}

void CombatSystem::processRound(Faction& f1, Faction& f2, int roundNumber) {
    cout << "\n\n=== ROUND " << roundNumber << " ===";
    
    cout << "\n\n-- Resource Phase --";
    f1.gatherResources();
    f2.gatherResources();
    cout << "\n" << f1.getName() << " resources: " << f1.getResources();
    cout << "\n" << f2.getName() << " resources: " << f2.getResources();
    
    if (roundNumber % 4 == 0) {
        cout << "\n\n-- Recruitment Phase --";
        cout << "\n" << f1.getName() << " recruitment:";
        f1.recruitMenu();
        
        cout << "\n" << f2.getName() << " recruitment:"; 
        f2.recruitMenu();
    }
    
    cout << "\n\n-- Combat Phase --";
    attack(f1, f2);
    attack(f2, f1);
}