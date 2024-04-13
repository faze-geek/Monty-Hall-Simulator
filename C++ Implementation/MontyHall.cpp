#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

// Set up the argument parser.
#include "Include/cxxopts.hpp"

using namespace std;
#define mtrand(a,b)             uniform_int_distribution<int>(a, b)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Function to run a single simulation of the Monty Hall Problem
pair<int, int> scenario_statistics_randomised(int n,int k){
    // Logic and Assumptions :
    // Placement of car is randomised. 
    // Choice of player is randomised.
    
    // Now there are 2 scenarios for success - 
    // 1. If the player's initial choice was the car, then he will win if he does not swtich.
    // 2. If the player's initial choice was not the car, then he will win if randomly chooses the index of (n-k-2).

    // To visualize the condition for 2nd scenario's success, go through these steps.
    // Step 1: 2 indices for car and player's choice get randomly selected.
    // Step 2: Host opens k wrong doors other than player's choice.
    // Let us remove the car, the player's choice and other k wrong doors from the original array. This leaves n-k-2 choices.
    // Now virtually assign indices from 0 to (n-k-3) as goats, and (n-k-2)th index as car.
    // Then P(of getting a car from the remaining doors) = P(of getting index n-k-2 when randomly chosen from [0,n-k-2]) where P() is probability. 

    // Time Complexity per simulation:
    // O(3*k), where k is a constant. We are generating 3 random numbers.
    // O(k) could be 32 roughly. As 32 bits are getting generated for integers.

    int car_idx = mtrand(0, n-1);                     // The car index.
    int player_idx = mtrand(0, n-1);                  // The player choice.

    int random_choice = mtrand(0, n-k-2);             // The new choice, in case he decides to switch to any remaining door.
    
    // Case 1. He wins if he stays.
    bool stay_success = car_idx == player_idx;
    // Case 2. He wins if he switches.       
    bool switch_success = car_idx != player_idx && random_choice == (n-k-2);

    return pair<bool, bool>{ stay_success, switch_success};
}

pair<int, int> scenario_statistics_sequential(int n, int k) {
    // Logic and Assumptions :
    // Placement of car is randomised. 
    // The player always chooses door 1.
    
    // Then after removal of k wrong doors there are 2 scenarios - 
    // 1. If the car is actually behind door1 (index 0), the he will win if he does not switch.
    // 2. The car is present somewhere ahead of door1 (index 1 to size-1 of the new array, where new array is original array - k wrong doors).
    // Then he will win if the randomly chosen door in that range has a car.
 
    // Time Complexity per simulation: O(N)

    vector<int> doors(n, 0);                 // Initializing doors array with all wrong doors (goats). 
    int r = mtrand(0, n-1);                  // Randomly placing car at any index of the array.
    doors[r] = 1;
    
    // Now remove k wrong doors.
    int i = 0;
    int idx = 1;
    while (i < k) {
        if (idx != r && doors[idx] == 0) {   // Host never checks index r (the correct door).
            doors[idx] = -1;                 // The removed door is given a value of -1 and later discarded.
            i++;
        }
        idx++;
    }

    // Make a new array with n-k doors.
    vector<int> rem_doors;
    for (int val : doors) {
        if (val != -1) rem_doors.push_back(val);
    }

    bool stay_success = 0;
    bool switch_success = 0;
    // Case 1. He wins if he stays.
    if (rem_doors[0] == 1) stay_success = 1;
    // Case 2. He wins if he switches.
    else switch_success = rem_doors[mtrand(1, rem_doors.size() - 1)];

    return make_pair(stay_success, switch_success);
}

void simulate(int n, int k, int simulations) {
    int switch_cnt = 0;
    int stay_cnt = 0;
    for (int i = 0; i < simulations; i++) {
        // The below 2 lines provide two visualizations. Choose from the randomised (default) or sequential simulation. 
        // Uncomment accordingly.
        // pair<int, int> results = scenario_statistics_sequential(n, k);            
        pair<int, int> results = scenario_statistics_randomised(n, k);
        
        // Counting scenario 1 cases.
        stay_cnt += results.first;
        // Counting scenario 2 cases.
        switch_cnt += results.second;
    }
    double res1 = static_cast<double>(stay_cnt) / static_cast<double>(simulations);
    double res2 = static_cast<double>(switch_cnt) / static_cast<double>(simulations);
    
    cout << "Scenario 1: " << stay_cnt << "/" << simulations<< " = " <<  res1 * 100 << "% wins if player sticks to the initial choice." << endl;
    cout << "Scenario 2: " << switch_cnt << "/" << simulations<< " = " << res2 * 100 << "% wins if player switches the initial choice." << endl;
}

int main(int argc, char* argv[]) {
    // Seed the random number generator.
    srand(time(0));  
    
    // Invoking an instance of the cxxopts library.
    cxxopts::Options options("MontyHall", "Monty Hall Problem Simulator");

    // Parse the command-line arguments if provided, else initialize with default values of Monty Hall Problem.
    options.add_options()
            ("n, num_doors", "Number of doors", cxxopts::value<int>()->default_value("3"))
            ("k, num_doors_opened_by_host", "Number of doors opened by host", cxxopts::value<int>()->default_value("1"))
            ("s, num_simulations", "Number of simulations", cxxopts::value<int>()->default_value("10000"))
            ("h, help", "Print usage");
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        cout << options.help() << endl;
        exit(0);
    }
    // Assign the values to variables.
    int n = result["num_doors"].as<int>();
    int k = result["num_doors_opened_by_host"].as<int>();
    int s = result["num_simulations"].as<int>();
    
    // Error Handling.
    if(!(3 <= n)){
        cerr << "There must be a minimum of 3 doors to play the Monty Hall Simulator."<<endl;
        abort();
    }
    if (!(0 <= k && k <= n - 2)) {
        cerr << "Invalid number of doors given to open. Must be between 0 and (num_doors - 2)."<< endl;
        abort(); 
    }
    if (s <=0) {
        cerr << "Number of simulations must be positive."<< endl;
        abort();
    }
    cout << "Simulation Results" << endl;
    simulate(n, k, s);
    
    return 0;
}