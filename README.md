# Genetic-Knapsack-Solver

A C++ implementation of a Genetic Algorithm to solve the 0/1 Knapsack Problem.

## Introduction

The 0/1 Knapsack Problem is a classic optimization problem where the goal is to select a subset of items, each with a weight and a value, to maximize the total value while keeping the total weight within a given limit. This repository contains a C++ implementation of a Genetic Algorithm to solve the 0/1 Knapsack Problem.

## Features

- **Genetic Algorithm**: The solution utilizes a genetic algorithm to evolve a population of candidate solutions over several generations.
- **Elitism**: The algorithm incorporates elitism to retain the best-performing individuals from one generation to the next.
- **Rank Selection**: A rank-based selection mechanism is employed to select parents for crossover based on their fitness.
- **Mutation**: Random mutations are applied to offspring to introduce diversity in the population.
- **Crossover**: Two-point crossover is used to create new individuals by combining genetic material from two parent solutions.

## Getting Started

## Usage

  input file (`input.txt`) containing test cases. Each test case should include the weight limit, the number of items, and the weight and value of each item.

   Example:

   ```plaintext
   1
   10 5
   2 5
   3 8
   4 9
   5 10
   9 7
   ```

   The program reads the input file, performs the genetic algorithm for each test case, and outputs the selected items for each test case along with their total weight and value.

## Algorithm Overview

1. **Initialization**: Randomly generate an initial population of candidate solutions.

2. **Fitness Calculation**: Evaluate the fitness of each solution in the population based on the total value of selected items while considering the weight constraint.

3. **Elitism**: Retain the best-performing solutions from the current population.

4. **Selection**: Use rank-based selection to choose parent solutions for crossover.

5. **Crossover**: Apply two-point crossover to create new offspring.

6. **Mutation**: Introduce random mutations to the offspring to maintain diversity.

7. **Replacement**: Replace the current population with the combined offspring and elite solutions.

8. **Termination**: Repeat steps 2-7 for a fixed number of generations or until convergence.
