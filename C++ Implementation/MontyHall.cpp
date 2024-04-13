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

/* Function to run a single simulation of the Monty Hall Problem.
    Return Type:
    - It returns a pair of boolean value: `<stay_success, switch_success>`
    - `stay_success` = 1, if the player won the car by staying on its initial choice, 0 otherwise.
    - `switch_sucess` = 1, if the player won the car by swithing its initial choice after k goat-doors were revealed, 0 otherwise.
    
    Assumptions:
    - The doors are indexed from 1 to n.
    - Placement of car is randomised. 
    - Choice of player is randomised.

    Methodology:
    - Firstly, we generate two uniformly at random indices `car_idx` and `player_idx` denoting the car door and player's initial choice.
    - `stay_success` = 1 if and only if `car_idx == player_idx`.
    - After `k` doors are revealed, there are exactly `R = n-k-1` doors left that the player can switch to (excluding `k` revealed doors and player's current choice door).
    - By symmetry, the probability of car being in any of these `R` doors is equal.
    - Thus, probability of landing on the car door after switching =  probability of getting `1` when a fair `R`-sided dice is rolled = 1/R.

    Time Complexity per simulation:
    - O(3*K), where K is a constant. We are generating 3 random numbers.
    - O(K) could be 32 roughly. As 32 bits are getting generated for integers.
*/
pair<bool, bool> scenario_statistics_optimal(int n,int k){
    int car_idx = mtrand(1, n);                     // The car index.
    int player_idx = mtrand(1, n);                  // The player's choice.
    int remaining = n - k - 1;                      
    int dice_roll = mtrand(1, remaining);           // The new random choice, in case he decides to switch to any remaining door.
    
    // Case 1. He wins if he stays.
    bool stay_success = car_idx == player_idx;
    // Case 2. He wins if he switches.       
    bool switch_success = car_idx != player_idx && dice_roll == 1;

    return pair<bool, bool>{stay_success, switch_success};
}

/*  Function to run a single simulation of the Monty Hall Problem.
    Return Type:
    - It returns a pair of boolean value: `<stay_success, switch_success>`
    - `stay_success` = 1, if the player won the car by staying on its initial choice, 0 otherwise.
    - `switch_sucess` = 1, if the player won the car by swithing its initial choice after k goat-doors were revealed, 0 otherwise.

    Assumptions:
    - Placement of car is randomised. 
    - Choice of Player is randomised.
    
    Methodology:
    - Firstly, we generate two uniformly at random indices `car_idx` and `player_idx` denoting the car door and player's initial choice.
    - `stay_success` = 1 if and only if `car_idx == player_idx`.
    - To reveal `k` doors, all wrong doors in the `temp_doors` vector are randomly shuffled. The first `k` values are the indices of the doors opened.
    - If the player wants to switch, he makes a choice from `alive_doors` which consists of `n-k-2` unrevealed doors and the car `car_idx` as well.
    - `switch_success` = 1 if and only if the randomly chosen door in `alive_doors` has a car behind it.
 
    Time Complexity per simulation: 
    - O(N*K) where K is a constant.
*/

pair<bool, bool> scenario_statistics_randomised(int n, int k) {
    vector<int> doors(n, 0);                 // Initializing doors array with all wrong doors (goats). 
    int car_idx = mtrand(0, n-1);            // Randomly placing car at any index of the array.
    doors[car_idx] = 1;
    int player_idx = mtrand(0, n-1);         // Randomly pick choice of the player at any index of the array. 
    
    vector<int> temp_doors;                  // A temporary array, to decide which doors to open. 
    for(int i = 0; i < doors.size(); i++){
        if(i != car_idx && i != player_idx){ // Host has to open k wrong doors other than car and player's choice.
            temp_doors.push_back(i);
        }
    }
    // Shuffle the wrong doors randomly, then the first k doors will be opened.
    shuffle(temp_doors.begin(), temp_doors.end(), rng);
    for(int i = 0; i < k; i++){
        doors[temp_doors[i]] = -1;           // Opened doors are assigned -1 and later discarded. 
    }

    // Make a new array with n-k-1 doors.
    // alive_doors are those doors which can be chosen if the player switches.
    vector<int> alive_doors;
    for (int i = 0; i < doors.size(); i++) {
        if (doors[i] != -1 && i != player_idx) alive_doors.push_back(doors[i]);
    }

    bool stay_success = 0;
    bool switch_success = 0;
    // Case 1. He wins if he stays.
    if (player_idx == car_idx) stay_success = 1;
    // Case 2. He wins if he switches.
    else switch_success = alive_doors[mtrand(0, alive_doors.size() - 1)];

    return pair<bool, bool>{stay_success, switch_success};
}

/*  Function to repeatedly simulate the Monty Hall Problem. */
void simulate(int n, int k, int simulations) {
    int switch_cnt = 0;
    int stay_cnt = 0;
    for (int i = 0; i < simulations; i++) {
        // The below 2 lines provide two different algorithms. Choose from the optimal (default) or randomised simulation. 
        // Uncomment accordingly.
        pair<bool, bool> results = scenario_statistics_optimal(n, k);            
        // pair<bool, bool> results = scenario_statistics_randomised(n, k);
        
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

    // Parse the command-line arguments if provided, else initialize with default values of original Monty Hall Problem.
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
