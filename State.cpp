#include "State.h"

// Default constructor
State::State(){
    srand();

    reward = 0;
    value  = double( rand() / RAND_MAX ) + 1;
}

// Initializing constructor
State::State(double r, double v) {
    reward = r;
    value  = v;
}


// Mutator Methods

// Get reward
double State::getReward() { return reward; }

// Get value
double State::getValue() { return value; }


// Accessor Methods

// Set reward
void State::setReward(double r) { reward = r; }

// Set reward
void State::setValue(double v) { value = v; }
