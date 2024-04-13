# Monty Hall Problem Simulator

The task is to develop a C++ program that simulates the Monty Hall Problem, allowing for the simulation of scenarios with a variable number of doors and different strategies for opening doors by the host.

## Prerequisites
- C++ compiler (supporting C++11 or newer)
- Git (optional, for cloning the repository)

## How to Install and Run

1. Clone the repository:

    ```bash
    git clone https://github.com/faze-geek/Monty-Hall-Simulator.git
    ```

    Alternatively, you can download the source code as a ZIP archive and extract it.

2. Navigate to the repository directory:

    ```bash
    cd Monty-Hall-Simulator
    ```

3. Navigate to the particular folder:

    ```bash
    cd '.\C++ Implementation\'   
    ```

4. Compile the program using a C++ compiler. For example, using g++:

    ```bash
    g++ MontyHall.cpp -o MontyHall -I"C++ Implementation/Include"
    ```
    Kindly keep the same path provided in this command, so that the required header files can be compiled. 
    
5. Run the program with the desired command-line arguments:

    ```bash
    ./MontyHall  --num_doors <num_doors> --num_doors_opened_by_host <num_doors_opened_by_host> --num_simulations <num_simulations>
    ```

    Replace `<num_doors>`, `<num_doors_opened_by_host>`, and `<num_simulations>` with your input values.
6. Example:
   
   ```
   PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall  --num_doors 5 --num_doors_opened_by_host 3 --num_simulations 10000
   Simulation Results
   Scenario 1: 1991/10000 = 19.91% wins if player sticks to the initial choice.
   Scenario 2: 8009/10000 = 80.09% wins if player switches the initial choice.
   ```

## Command-Line Arguments
There are 3 arguments that need to be supported.
- `--num_doors`: Specifies the total number of doors in the simulation.
- `--num_doors_opened_by_host`: Specifies the number of doors opened by the host.
- `--num_simulations`: The number of simulation iterations to aggregate the results over.

I have used the **open source library** [cxxopts](https://github.com/jarro2783/cxxopts) for having an elegant Command-Line interface. 
I preferred this library over conventional command line arguments using **argv** (Argument Vector) because :
1. It supports default values of the original Monty Hall problem (3 Doors, 1 Opened).
   
   ```
   PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall
   Simulation Results
   Scenario 1: 3338/10000 = 33.38% wins if player sticks to the initial choice.
   Scenario 2: 6662/10000 = 66.62% wins if player switches the initial choice.
   ```
2. Arguments are not positional and can be specified in any order.

   ```
   PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall  --num_doors_opened_by_host 3 --num_doors 5
   Simulation Results
   Scenario 1: 1989/10000 = 19.89% wins if player sticks to the initial choice.
   Scenario 2: 8011/10000 = 80.11% wins if player switches the initial choice.
   ```
3. It provides a user friendly help flag to understand how the code is related to the arguments.

    ```
    PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall  --help
    Monty Hall Problem Simulator
    Usage:
      MontyHall [OPTION...]
    
      -n, --num_doors arg           Number of doors (default: 3)
      -k, --num_doors_opened_by_host arg
                                    Number of doors opened by host (default: 1)
      -s, --num_simulations arg     Number of simulations (default: 10000)
    ```

## Implementation

I have implemented 2 algorithms for better visualization by the user. \
The exact logic of each implementation is documented through comments before the function.
They are **scenario_statistics_optimal()** (default) and **scenario_statistics_randomised()** (commented). You may use any of the two, kindly uncomment lines 108-109 accordingly.

- ### scenario_statistics_optimal()
This is the most optimum routine for simulating the Monty Hall problem and can perform each simulation in about constant time **~O(1)**. This algorithm only uses random number generation and does not physically alter any memory space like arrays (no operations like random shuffling, random sampling are performed). Each choice in this algorithm is made randomly. You can read about this approach in more detail through the code comments.\
**The optimization allows us to achieve 1000 million simulations alongside large input values of num_doors and num_doors_opened_by_host simultaneously, which is not possible by a linear algorithm. Use this routine to run large inputs.**
```
PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall  --num_doors 100000 --num_doors_opened_by_host 99990 --num_simulations 100000000
Simulation Results
Scenario 1: 1006/100000000 = 0.001006% wins if player sticks to the initial choice.
Scenario 2: 11112187/100000000 = 11.1122% wins if player switches the initial choice.
```

- ### scenario_statistics_sequential()
This is another routine for simulating the Monty Hall problem. It performs each simulation in **O(N*k)** time. In this routine, we carry out each step of the Monty Hall problem in memory spaces like arrays. Each choice in this algorithm is made randomly as well. But since random shuffling of arrays is performed, this is slower. You can read about this approach in more detail through the code comments.\
**This routine shows how to physically pick and manipulate the doors through arrays. Use this routine for better user visualization.**

## Output

This simulator returns the winning percentages of the following cases -
1. The player stays with his initial pick.
2. The player switches his initial pick to a new pick.

## Explanation (Bonus)

Kindly refer to [Explanation.pdf](https://github.com/faze-geek/Monty-Hall-Simulator/blob/main/Explanation.pdf) to understand the mathematical derivation behind Monty Hall Problem simulator.
