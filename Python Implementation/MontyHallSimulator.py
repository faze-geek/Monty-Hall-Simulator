import argparse
import random

# Set up the argument parser.
parser = argparse.ArgumentParser(description='Monty Hall Problem Simulator')
parser.add_argument('--num_doors', type=int, default=3, help='Specifies the total number of doors.')
parser.add_argument('--num_doors_opened_by_host', type=int, default=1, help='Specifies the number of doors opened by the host.')
parser.add_argument('--num_simulations', type=int, default=10000, help='Specifies the number of times the program is simulated.')

# Parse the command-line arguments if provided, else initialize with default values of Monty Hall Problem.
args = parser.parse_args()

# Assign the values to variables.
n = args.num_doors
k = args.num_doors_opened_by_host
simulations = args.num_simulations

# Error handling.
assert 3 <= n, "There must be a minimum of 3 doors to play the Monty Hall Simulator."
assert 0 <= k <= (n-2), "Invalid number of doors given to open. Must be between 0 and (num_doors - 2)."
assert 0 < simulations , "The number of simulations must always be positive."

# Function to run a single simulation of the Monty Hall Problem
def scenario_statistics_randomised(n, k):
    # Logic and Assumptions :
    # Placement of car is randomised. 
    # Choice of player is randomised.
    
    # Now there are 2 scenarios for success - 
    # 1. If the player's initial choice was the car, then he will win if he does not swtich.
    # 2. If the player's initial choice was not the car, then he will win if randomly chooses the index of (n-k-2).

    # To visualize the condition for 2nd scenario's success, go through these steps.
    # Step 1: 2 indices for car and player's choice get randomly selected.
    # Step 2: Host opens k wrong doors other than player's choice.
    # Let us remove the car, the player's choice and other k wrong doors from the original array. This leaves n-k-2 choices.
    # Now virtually assign indices from 0 to (n-k-3) as goats, and (n-k-2)th index as car.
    # Then P(of getting a car from the remaining doors) = P(of getting index n-k-2 when randomly chosen from [0,n-k-2]) where P() is probability. 

    # Time Complexity per simulation:
    # O(3*k), where k is a constant. We are generating 3 random numbers.
    # O(k) could be 32 roughly. As 32 bits are getting generated for integers.

    car_idx = random.randint(0, n-1)                     # The car index.  
    player_idx = random.randint(0, n-1)                  # The player choice.
    
    random_choice = random.randint(0, n-k-2)             # The new choice, in case he decides to switch to any remaining door.
    
    # Case 1. He wins if he stays.
    stay_success = car_idx == player_idx
    # Case 2. He wins if he switches.
    switch_success =  car_idx != player_idx and random_choice == n-k-2

    return (stay_success, switch_success)

def scenario_statistics_sequential(n, k):
    # Logic and Assumptions :
    # Placement of car is randomised. 
    # The player always chooses door 1.
    
    # Then after removal of k wrong doors there are 2 scenarios - 
    # 1. If the car is actually behind door1 (index 0), the he will win if he does not switch.
    # 2. The car is present somewhere ahead of door1 (index 1 to size-1 of the new array, where new array is original array - k wrong doors).
    # Then he will win if the randomly chosen door in that range has a car.
 
    # Time Complexity per simulation: O(N)    

    doors = [0] * n                 # Initializing doors array with all wrong doors (goats).                                    
    r = random.randint(0, n-1)      # Randomly placing car at any index of the array.
    doors[r] = 1

    # Now remove k wrong doors.
    i = 0 
    idx = 1
    while i < k :
        if(idx != r and doors[idx] == 0):  # Host never checks index r (the correct door).
            doors[idx] = -1                # The removed door is given a value of -1 and later discarded.
            i += 1
        idx += 1

    # Make a new array with n-k doors.
    rem_doors = []
    for val in doors: 
        if (val != -1) : rem_doors.append(val)

    stay_success = 0
    switch_success = 0

    # Case 1. He wins if he stays.
    if(rem_doors[0] == 1) : stay_success = 1
    # Case 2. He wins if he switches. 
    else: switch_success = rem_doors[random.randint(1, len(rem_doors) - 1)]

    return (stay_success, switch_success)

def simulate(n, k, simulations):
    switch_cnt = 0
    stay_cnt = 0
    for _ in range(simulations):
        # The below 2 lines provide two visualizations. Choose from the randomised (default) or sequential simulation. 
        # Uncomment accordingly.
        # res_1, res_2 = scenario_statistics_sequential(n, k) 
        res_1, res_2 = scenario_statistics_randomised(n, k)

        # Counting scenario 1 cases.
        stay_cnt +=  res_1
        # Counting scenario 2 cases.        
        switch_cnt += res_2

    print(f"Scenario 1: {stay_cnt}/{simulations} = {round(stay_cnt/simulations*100, 3)}% wins if player sticks to the intial choice.")        # Successful cases without switch.
    print(f"Scenario 2: {switch_cnt}/{simulations} = {round(switch_cnt/simulations*100, 3)}% wins if player switches the initial choice.")    # Successful cases with switch.  
 
if __name__ == "__main__":
    print("Simulation Results")
    simulate(n, k, simulations)