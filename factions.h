#ifndef FACTIONS_H  
#define FACTIONS_H

#include "baseclasses.h"
#include "derivedclasses.h"

class HumanFaction : public Faction {
public:
    HumanFaction(int startResources);
    void recruitMenu() override;
    void gatherResources() override;
};

class AlienFaction : public Faction {
public:
    AlienFaction(int startResources);
    void recruitMenu() override; 
    void gatherResources() override;
};

#endif