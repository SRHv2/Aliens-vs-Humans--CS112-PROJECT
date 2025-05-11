#ifndef COMBAT_H
#define COMBAT_H

#include "factions.h"

class CombatSystem {
public:
    static void attack(Faction& attacker, Faction& defender);
    static void processRound(Faction& f1, Faction& f2, int roundNumber);
};

#endif