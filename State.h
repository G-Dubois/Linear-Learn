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
    double eligibility;
    int index;

public:

    // Constructors
    State();                                // Creates a generic state
    State(double r, double v, int i);       // Initializes a state with given values

    // Accessor Methods
    double getReward();
    double getValue();
    double getEligibility();
    int isAt();

    // Mutator Methods
    void setReward(double r);
    void setValue(double v);
    void setEligibility();
    void isAt(int i);

    // Eligibility Trace Methods
    void resetEligibility();
    void updateEligibility(double lambda);
};

#endif
