#include "State.h"

// Default constructor
State::State(){
    reward = 0;
    value  = 0;
    eligibility = 0;
    index = 0;
}

// Initializing constructor
State::State(double r, double v, int i) {
    reward = r;
    value  = v;
    eligibility = 0;
    index = i;
}


// Mutator Methods

// Get reward
double State::getReward() { return reward; }

// Get value
double State::getValue() { return value; }

// Get the eligibility
double State::getEligibility() { return eligibility; }

// Get index location
int State::isAt() { return index; }


// Accessor Methods

// Set reward
void State::setReward(double r) { reward = r; }

// Set reward
void State::setValue(double v) { value = v; }

// Set eligibility to 1
void State::setEligibility() { eligibility = 1; }

// Set index location
void State::isAt(int i) { index = i; }


// Eligibility Trace Methods

// Reset the eligibility to 0
void State::resetEligibility() { eligibility = 0; }

// Reduce the eligibility based on lambda
void State::updateEligibility(double lambda) { eligibility *= lambda; }
