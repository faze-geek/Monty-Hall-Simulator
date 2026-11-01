#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

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
    - Firstly, we generate two uniformly random indices `car_idx` and `player_idx` denoting the car door and player's initial choice.
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

int main() {
    // Seed the random number generator.
    srand(time(0));  
    
    // Declare the variables and take input from the user.
    int n;      // Number of doors (original Monty Hall Problem: 3)
    int k;      // Number of doors opened by host (original Monty Hall Problem: 1)
    int s;      // Number of simulations (e.g. 10000)

    cout << "Enter number of doors (n): ";
    cin >> n;
    cout << "Enter number of doors opened by host (k): ";
    cin >> k;
    cout << "Enter number of simulations (s): ";
    cin >> s;
    
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
