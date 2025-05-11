#ifndef DERIVEDCLASSES_H
#define DERIVEDCLASSES_H

#include "baseclasses.h"

// Human Units
class Rifleman : public Unit {
public:
    Rifleman();
};

class Tank : public Unit {
public: 
    Tank();
};

// Alien Units
class Zorg : public Unit {
public:
    Zorg();
};

class Clanker : public Unit {
public:
    Clanker();
};

#endif