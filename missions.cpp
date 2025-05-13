#include "missions.h"
#include "combat.h"
#include <iostream>

bool MissionSystem::runDefenseMission(Faction& defender, Faction& attacker, int rounds) {
    cout << "\n=== DEFENSE MISSION STARTED ===";
    cout << "\nDefender: " << defender.getName();
    cout << "\nAttacker: " << attacker.getName();
    cout << "\nSurvive for " << rounds << " rounds to win!\n";
    
    for (int round = 1; round <= rounds; round++) {
        cout << "\n\n=== ROUND " << round << " ===";
        
        // Attacker gathers resources and recruits
        cout << "\n\n-- " << attacker.getName() << " Turn --";
        attacker.gatherResources();
        attacker.recruitMenu();
        
        // Defender cannot gather resources 
        cout << "\n\n-- " << defender.getName() << " Turn --";
        defender.recruitMenu();
        
        // Combat phase
        cout << "\n\n-- Combat Phase --";
        CombatSystem::attack(attacker, defender);
        CombatSystem::attack(defender, attacker);
        
        // Check if defender was wiped out
        if (defender.getArmySize() == 0) {
            cout << "\n\nDEFENSE FAILED! " << defender.getName() << " were destroyed!";
            return false;
        }
    }
    
    cout << "\n\nDEFENSE SUCCESSFUL! " << defender.getName() << " survived all rounds!";
    return true;
}

bool MissionSystem::humanDefenseMission() {
    HumanFaction humans(305);   //start off with 250 resources, after the entry 2
    AlienFaction aliens(100);
    
    // Starting armies
    humans.addUnit(new Rifleman());
    humans.addUnit(new Tank());
    aliens.addUnit(new Zorg());
    aliens.addUnit(new Clanker());
    
    return runDefenseMission(humans, aliens, 15);
}

bool MissionSystem::alienDefenseMission() {
    AlienFaction aliens(305);  //start off with 250 resources, after the entry 2
    HumanFaction humans(100);
    
    // Starting armies
    aliens.addUnit(new Zorg());
    aliens.addUnit(new Clanker());
    humans.addUnit(new Rifleman());
    humans.addUnit(new Tank());
    
    return runDefenseMission(aliens, humans, 15);
}
bool MissionSystem::teamDeathmatch() {

    HumanFaction humans(200);
    AlienFaction aliens(200);
    humans.addUnit(new Rifleman());
    humans.addUnit(new Tank());
    aliens.addUnit(new Zorg());
    aliens.addUnit(new Clanker());

    int round = 1;
    const int maxrounds = 20; 

    while (round <= maxrounds) {
        cout << "\n\n=== ROUND " << round << " ===";
        cout << "\n\n-- HUMAN TURN --";
        humans.gatherResources();
        humans.recruitMenu();

        
        cout << "\n\n-- ALIEN TURN --";
        aliens.gatherResources();
        aliens.recruitMenu();

        cout << "\n\n-- COMBAT PHASE --";
        CombatSystem::attack(humans, aliens);
        CombatSystem::attack(aliens, humans);

        if (aliens.getArmySize() == 0) {
            cout << "\n\nVICTORY! Humans have wiped out the aliens!";
            return true;
        }
        if (humans.getArmySize() == 0) {
            cout << "\n\nDEFEAT! Aliens have wiped out the humans!";
            return false;
        }

        round++;
    }

    cout << "\n\nSTALEMATE! Maximum rounds reached with both sides surviving!";
    return false;
}