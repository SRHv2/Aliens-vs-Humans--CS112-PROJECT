#include "derivedclasses.h"

// Human Units
Rifleman::Rifleman() : Unit("Rifleman", 10, 7, 20, false) {}

Tank::Tank() : Unit("Tank", 24, 4, 35, true) {}

// Alien Units  
Zorg::Zorg() : Unit("Zorg", 8, 8, 20, false) {}

Clanker::Clanker() : Unit("Clanker", 22, 5, 35, true) {}