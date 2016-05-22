#include "State.h"

// Default constructor
State::State(){
    reward = 0;
    value  = 0;
    index = 0;
}

// Initializing constructor
State::State(double r, double v, int i) {
    reward = r;
    value  = v;
    index = i;
}


// Mutator Methods

// Get reward
double State::getReward() { return reward; }

// Get value
double State::getValue() { return value; }

// Get index location
int State::isAt() { return index; }


// Accessor Methods

// Set reward
void State::setReward(double r) { reward = r; }

// Set reward
void State::setValue(double v) { value = v; }

// Set index location
void State::isAt(int i) { index = i; }
