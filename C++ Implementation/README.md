# C++ Implementation
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
6. Example
   
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
1. It supports default values (3 Door 1 Opened) of the original Monty Hall problem.
   
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
They are **scenario_statistics_randomised()** (default) and **scenario_statistics_sequential()** (commented). You may use any of the two, kindly uncomment lines 101-102 accordingly.

- ### scenario_statistics_randomised()
This is the most optimum routine for simulating the Monty Hall problem and can perform each simulation in about constant time **~O(1)**. This algorithm only uses random number generation and does not physically alter any memory like arrays (no operations like random shuffling / random sampling are performed). Each choice in this algorithm is made randomly. You can read about this approach in more detail in the comments.\
**The optimization allows us to achieve 1000 million simulations, which is not possible by a linear algorithm. Use this routine to run large inputs.**
```
PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\C++ Implementation> ./MontyHall  --num_doors 5 --num_doors_opened_by_host 3 --num_simulations 100000000
Simulation Results
Scenario 1: 19998401/100000000 = 19.9984% wins if player sticks to the initial choice.
Scenario 2: 80001599/100000000 = 80.0016% wins if player switches the initial choice.
```

- ### scenario_statistics_sequential()
This is another routine for simulating the Monty Hall problem. It performs each simulation in **O(N)** time. In this routine we carry out the Monty Hall problem steps in memory spaces. We use the assumptions that the player always picks door 1 and the opening of doors by the host happens in a sequential manner.\
**This routine shows how to physically manipulate the arrays as set of doors. Use this routine for better user visualization.** 
