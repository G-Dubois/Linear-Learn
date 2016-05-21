#ifndef STATE
#define STATE

#include <iostream>
#include <random>

using namespace std;

class State {
private:

    // Data members
    double reward;
    double value;

public:

    // Constructors
    State();
    State(double r, double v);

    // Accessor Methods
    double getReward();
    double getValue();

    // Mutator Methods
    void setReward(double r);
    void setValue(double v);
};

#endif
