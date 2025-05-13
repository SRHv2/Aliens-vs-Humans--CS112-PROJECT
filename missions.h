#ifndef MISSIONS_H
#define MISSIONS_H
using namespace std;
#include "factions.h"

class MissionSystem {
public:
    static bool humanDefenseMission();
    static bool alienDefenseMission();
    static bool teamDeathmatch();
private:
    static bool runDefenseMission(Faction& defender, Faction& attacker, int rounds);
};

#endif