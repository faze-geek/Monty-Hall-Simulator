
# Python Implementation
## Prerequisites
- Python (version 3.2 or newer)
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
    cd '.\Python Implementation\'
    ```
4. Run the program with the desired command-line arguments:

    ```bash
    python MontyHallSimulator.py  --num_doors <num_doors> --num_doors_opened_by_host <num_doors_opened_by_host> --num_simulations <num_simulations>
    ```
    Replace `<num_doors>`, `<num_doors_opened_by_host>`, and `<num_simulations>` with your input values.
   
5. Example
   
   ```
    PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\Python Implementation> python MontyHallSimulator.py --num_doors 5 --num_doors_opened_by_host 3
     --num_simulations 10000
    Simulation Results
    Scenario 1: 1986/10000 = 19.86% wins if player sticks to the intial choice.
    Scenario 2: 8014/10000 = 80.14% wins if player switches the initial choice.
   ```

## Command-Line Arguments
There are 3 arguments that need to be supported.
- `--num_doors`: Specifies the total number of doors in the simulation.
- `--num_doors_opened_by_host`: Specifies the number of doors opened by the host.
- `--num_simulations`: The number of simulation iterations to aggregate the results over.

I have used the **open source module** [argparse](https://github.com/python/cpython/blob/main/Lib/argparse.py) to achieve this.

## Implementation

I have implemented 2 algorithms for better visualization by the user. \
The exact logic of each implementation is documented through comments before the function.
They are **scenario_statistics_randomised()** (default) and **scenario_statistics_sequential()** (commented). You may use any of the two, kindly uncomment lines 101-102 accordingly.

- ### scenario_statistics_randomised()
This is the most optimum routine for simulating the Monty Hall problem and can perform each simulation in about constant time **~O(1)**. This algorithm only uses random number generation and does not physically alter any memory like arrays (no operations like random shuffling / random sampling are performed). Each choice in this algorithm is made randomly. You can read about this approach in more detail in the comments.\
**The optimization allows us to achieve 1000 million simulations, which is not possible by a linear algorithm. Use this routine to run large inputs.**
```
PS C:\Users\kunni\OneDrive\Desktop\Anurag_Bhat_Task\Python Implementation> python MontyHallSimulator.py --num_doors 5 --num_doors_opened_by_host 3 --num_simulations 100000000
Simulation Results
Scenario 1: 19997625/100000000 = 19.998% wins if player sticks to the intial choice.
Scenario 2: 80002375/100000000 = 80.002% wins if player switches the initial choice.
```

- ### scenario_statistics_sequential()
This is another routine for simulating the Monty Hall problem. It performs each simulation in **O(N)** time. In this routine we carry out the Monty Hall problem steps in memory spaces. We use the assumptions that the player always picks door 1 and the opening of doors by the host happens in a sequential manner.\
**This routine shows how to physically manipulate the arrays as set of doors. Use this routine for better user visualization.**  

### Comparision with C++ Implementation
Overall the Python implementation provides better readability, the elegant syntax makes the code simpler to understand. On the other hand the same algorithm runs comparatively faster for larger inputs in C++.
