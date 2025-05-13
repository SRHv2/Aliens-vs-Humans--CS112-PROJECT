#include <iostream>
#include <cstdlib>
#include <ctime>
#include "missions.h"

int main() {
    srand(time(0));
    
    cout << "ALIENS VS HUMANS STRATEGY GAME\n";
    cout << "Select Mission:\n";
    cout << "1. Human Defense (Survive 20 rounds)\n";
    cout << "2. Alien Defense (Survive 20 rounds)\n";
    cout << "Enter choice: ";
    
    int choice;
    cin >> choice;
    
    bool missionSuccess = false;
    
    switch(choice) {
        case 1:
            missionSuccess = MissionSystem::humanDefenseMission();
            break;
        case 2:
            missionSuccess = MissionSystem::alienDefenseMission();
            break;
        default:
            cout << "Invalid choice!";
            return 1;
    }
    
    if (missionSuccess) {
        cout << "\n\nMISSION ACCOMPLISHED!";
    } else {
        cout << "\n\nMISSION FAILED!";
    }
    
    return 0;
}