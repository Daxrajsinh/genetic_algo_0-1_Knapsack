# Genetic Algorithm for 0-1 Knapsack Problem

Implemented a Genetic Algorithm to solve the 0-1 Knapsack Problem in C++.

## Problem Statement

The 0-1 Knapsack Problem involves selecting a subset of items, each with a weight and value, to place into a knapsack with a limited capacity. The objective is to maximize the total value without exceeding the weight capacity.

## Approach

A Genetic Algorithm is used, which follows these steps:

1. **Chromosome Representation**: Each chromosome represents a possible solution, with genes as binary values (0 or 1), indicating whether an item is included in the knapsack.
   
2. **Fitness Function**: The fitness of each chromosome is calculated based on the total value of items in the knapsack. If the total weight exceeds the capacity, the fitness is set to 0.

3. **Selection**: The algorithm selects chromosomes for crossover using **Roulette Wheel Selection**, where chromosomes with higher fitness are more likely to be chosen.

4. **Crossover**: **One-Point Crossover** is used to combine two parent chromosomes and generate offspring. Genes to the left of a randomly chosen crossover point are taken from one parent, and genes to the right from the other.

5. **Mutation**: To avoid getting stuck at local maxima, **mutation** is performed by randomly flipping bits in chromosomes with a small mutation rate (0.1 in this case).

6. **Generations**: The algorithm evolves the population over multiple generations (1000 in this case), with the goal of improving the fitness of the population.

## Program Flow

1. **Input**: The user is prompted to input the number of items, each item's weight and value, and the knapsack's capacity.

2. **Initialization**: A random population of chromosomes is created.

3. **Evaluation and Selection**: The fitness of each chromosome is evaluated, and the top chromosomes are selected using roulette wheel selection.

4. **Crossover and Mutation**: Crossover is performed on selected chromosomes to generate offspring. Mutation is applied to prevent premature convergence.

5. **Stopping Condition**: The algorithm runs for a fixed number of generations (1000) or until the best fitness value stabilizes.

6. **Output**: The best solution found by the algorithm is displayed, including the total value of the selected items and which items are included.

## Example

Here’s an example of what the input format look like:

```bash
Enter a number of items:
5
Enter a weight and value of Item 1:
2 10
Enter a weight and value of Item 2:
5 50
Enter a weight and value of Item 3:
10 60
Enter a weight and value of Item 4:
5 30
Enter a weight and value of Item 5:
3 20
Enter the capacity of a knapsack:
10
