/**
 *  Author:         Grayson M. Dubois
 *  Project:        Linear Learn
 *  Description:    Agent uses TD-learning algorithm to learn the values of
 *                      states in a single array to find the goal
 */

// Dependencies

// IO Dependencies
#include <iostream>
#include <iomanip>
#include <fstream>

// Container Dependencies
#include <vector>

// Utilities
#include <random>     // For random nuber generation
#include <time.h>     // For initializing random seed

// Custom Class Dependencies
#include "State.h"

// Namespace Declarations
using namespace std;

// Enum Move indicates a movement left or right
enum Move {
    Left,
    Right
};

// World variables
vector<State> world;
int worldSize;
double alpha;
double discount;
int numberOfRuns;

int goalLocation;
int agentLocation;

// Statistical variables
int averageNumberOfSteps;
int maxNumberOfSteps;
int minNumberOfSteps;

// Random number generator
default_random_engine randomNumberGenerator;
uniform_real_distribution<double> valueDistribution(0.0, 0.001);
uniform_real_distribution<double> epsilonSoftDistribution(0.0, 1.0);

// Function Declarations
void getSettingsFromFile(string);
Move chooseMovement(State, State, State);
Move randomMovement();
unsigned int getLeftLocation(int);
unsigned int getRightLocation(int);

// TD-learning Functions
double V(int);
double r(int);

int main (int argc, char** argv) {

    // Set up random number generation
    randomNumberGenerator.seed( time(0) );

    // Get the world settings
    if ( argc > 1 ) {
        getSettingsFromFile(argv[1]);
    } else {
        worldSize = 64;
        alpha = 0.5;
        discount = 0.9;
    }

    // Set up a log file
    ofstream Log;
    Log.open("results.log");

    // Set up a final report file
    ofstream FinalReport;
    FinalReport.open("final.log");

    // Initialize the world array with states
    for (int i = 0; i < worldSize; i++) {

        // Generate a random value between 0 and 0.0001
        double randomValue = valueDistribution(randomNumberGenerator);

        // Create a new state with random values and rewards, and add it to the world array
        State newState(0, randomValue, i);
        world.push_back(newState);

        // Print state stats
        //cout << "Location: " << world[i].isAt() << "\n\tValue: " << world[i].getValue() << "\n\tReward: " << world[i].getReward() << "\n";
    }

    // Set up statistical variables
    averageNumberOfSteps = 0;
    maxNumberOfSteps = 0;
    minNumberOfSteps = INT_MAX;

    // Set up a location for the goal
    goalLocation = randomNumberGenerator() % worldSize;
    world[goalLocation].setReward(1.0);

    // Initial info
    for (int index = 0; index < worldSize; index++) {
        Log << "\tState " << index << "\n\t\tValue: " << world[index].getValue() << "\n\t\tReward: " << world[index].getReward() << "\n";
    }

    // Main loop of program. Run episodes until task is learned
    for (int i = 0; i < numberOfRuns; i++) {

        // Set up a location for the agent
        agentLocation = randomNumberGenerator() % worldSize;

        // Initialize Episode statistical variables
        int numberOfSteps = 0;

        // Set up a variable for the previous state
        State* previousState;

        // Loop to control the movements until agent has reached the goal
        do {

            //cout << "Agent Location: " << agentLocation << "\nGoal Location: " << goalLocation << "\n";

            // Set the previous state to the current state
            previousState = &world[agentLocation];

            // Choose a movement for the agent
            Move movement = chooseMovement( world[getLeftLocation( agentLocation )],
                                            world[agentLocation],
                                            world[getRightLocation( agentLocation )] );

            // Perform the movement
            switch (movement) {
                case Left:
                    agentLocation = getLeftLocation(agentLocation);
                    break;
                case Right:
                    agentLocation = getRightLocation(agentLocation);
                    break;
                default:
                    agentLocation = getLeftLocation(agentLocation);
                    break;
            }

            //*************TD-Learning Starts Here***************

            // Update previous state
            int s = previousState->isAt();
            int sPlus1 = agentLocation;

            double TDError = ( r(s) + discount * V(sPlus1) ) - V(s);
            //cout << "delta = ( r(" << s << ") + discount * V(" << sPlus1 <<  ") ) - V(" << s << ")\n";
            //cout << "delta = ( " << r(s) << " + " << discount << " * " << V(sPlus1) <<  " ) - " << V(s) << "\n";
            //cout << "delta = " << TDError <<"\n";

            previousState->setValue( previousState->getValue() + alpha * TDError );

            // If we have reached the goal, update the goal state
            if (agentLocation == goalLocation) {
                int G = goalLocation;

                double TDError = r(G) - V(G);
                //cout << "Gdelta = r(" << G << ") - V(" << G << ")\n";
                //cout << "Gdelta = " << r(G) << " - " << V(G) << "\n";
                //cout << "Gdelta = " << TDError << "\n";

                world[agentLocation].setValue( world[agentLocation].getValue() + alpha * TDError );

                break;
            }

            //*************TD-Learning Finished Here***********

            // Increment the number of steps taken so far
            numberOfSteps++;

            // Break out of loop if number of steps exceeds 100
            if (numberOfSteps >= 100){
                Log << "Steps exceeded 100. Terminating episode.\n";
                //cout << "Steps exceeded 100. Terminating episode.\n";
                break;
            }
        } while ( agentLocation != goalLocation );

        // Logging results

        //cout << "Episode " << i << "\nNumber of steps: " << numberOfSteps << "\n";
        Log << "Episode " << i << "\nNumber of steps: " << numberOfSteps << "\n";

        for (int index = 0; index < worldSize; index++) {
            Log << "\tState " << index << "\n\t\tValue: " << world[index].getValue() << "\n\t\tReward: " << world[index].getReward() << "\n";
        }

        // Calculate statistics
        if (numberOfSteps != 100 && numberOfSteps > maxNumberOfSteps) {
            maxNumberOfSteps = numberOfSteps;
        }

        if (numberOfSteps != 0 && numberOfSteps < minNumberOfSteps) {
            minNumberOfSteps = numberOfSteps;
        }

        averageNumberOfSteps += numberOfSteps;
    }

    //*****Logging and data reporting********
    
    averageNumberOfSteps /= numberOfRuns;
    cout << "Complete!\n"
        << "Number of Runs:\t\t\t" << numberOfRuns << "\n"
        << "Max Number of Steps:\t\t" << maxNumberOfSteps << "\n"
        << "Min Number of Steps:\t\t" << minNumberOfSteps << "\n"
        << "Average Number of Steps:\t" << averageNumberOfSteps << "\n";

    // Final report

    FinalReport << "Complete!\n"
        << "Number of Runs:\t\t\t" << numberOfRuns << "\n"
        << "Max Number of Steps:\t\t" << maxNumberOfSteps << "\n"
        << "Min Number of Steps:\t\t" << minNumberOfSteps << "\n"
        << "Average Number of Steps:\t" << averageNumberOfSteps << "\n";

    for (int index = 0; index < worldSize; index++) {
        FinalReport << "\tState " << index << "\n\t\tValue: " << world[index].getValue() << "\n\t\tReward: " << world[index].getReward() << "\n";
    }

    // Set up a .csv file to record the final values
    ofstream csv;
    csv.open("linear-learn.csv");

    csv << "State, Value, Reward\n";

    // Write csv file for final data
    for (int i = 0; i < worldSize; i++) {
        csv << i << ", " << world[i].getValue() << ", " << world[i].getReward() << "\n";
    }

    return 0;
}

// Get settings from config file
void getSettingsFromFile(string filename) {

    // Set up input file stream
    ifstream fin;
    fin.open(filename);

    // Do a priming read to ignore config file header
    string _;
    getline(fin, _);

    // Get the data from the input file
    fin >> worldSize >> alpha >> discount >> numberOfRuns;
}

// Decide what movement to make
// MOVEMENT POLICY:
//      If the values of two states are equal, choose left
//      %10 of the time, choose randomly (epsilon soft policy)
//      Agent MUST move
Move chooseMovement(State leftState, State currentState, State rightState) {

    // Initialize the movement to left
    Move movement = Left;

    // If the right value is greater than or equal to
    if (leftState.getValue() < rightState.getValue() ) {
        movement = Right;
    }

    // Set up epsilon soft policy
    double epsilon = epsilonSoftDistribution(randomNumberGenerator);

    if (epsilon < 0.1) {
        //cout << "RANDOM MOVEMENT!\n";
        movement = randomMovement();
    }

    return movement;
}

// Choose a random movement for the agent
Move randomMovement(){
    int random = randomNumberGenerator() % 2;
    switch (random){
        case 0:
            return Left;
        case 1:
            return Right;
        default:
            return Left;
    }
}

// Functions to get the left and right locations of a state

// Get left location
unsigned int getLeftLocation(int currentLocation) {
    unsigned int left;

    // If at the left bound, set left to the rightmost index
    if ( currentLocation == 0 ) {
        left = worldSize - 1;
    } else {
        left = currentLocation - 1;
    }

    return left;
}

// Get right location
unsigned int getRightLocation(int currentLocation) {
    unsigned int right;

    // If at the right bound, set right to the leftmost index
    if ( currentLocation == worldSize - 1 ) {
        right = 0;
    } else {
        right = currentLocation + 1;
    }

    return right;
}

//****** TD-Learning Functions

// Get the value of a state
double V(int state) {
    return world[state].getValue();
}

// Get the reward of a state
double r(int state) {
    return world[state].getReward();
}
