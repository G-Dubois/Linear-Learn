/**
 *  Author:         Grayson M. Dubois
 *  Project:        Linear Learn
 *  Description:    Agent uses TD-learning algorithm to learn the values of
 *                      states in a single array to find the goal
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "State.h"

using namespace std;

// World variables
vector<State> world;
int worldSize;
double alpha;
double discount;

int main (int argc, char** argv) {

    // Get the world settings
    if ( argc > 1 ) {
        getSettingsFromFile(argv[1]);
    } else {
        worldSize = 64;
        alpha = 0.5;
        discount = 0.9;
    }

    for (int i = 0; i < worldSize; i++) {
        world.push_back(new State());
        cout << "State: " << i << "\n\tValue: " << world[i].getValue() << "\n\tReward: " << world[i].getReward() << "\n";
    }

    for (int i = 0; i < worldSize; i++) {
        delete world[i];
    }

    return 0;
}

// Get settings from config file
void getSettingsFromFile(string filename) {
    worldSize = 64;
    alpha = 0.5;
    discount = 0.5;
}
