# AI-Puzzle
AI Puzzle Solver 🧩
This project implements an AI-based solution for solving the N-Puzzle Problem using the A (A-Star) search algorithm*. The algorithm combines Dijkstra's shortest path strategy with the Manhattan distance heuristic to efficiently solve the puzzle by finding the optimal sequence of moves.

# Features:
A Search Algorithm*: Combines cost and heuristic functions to explore the puzzle state space.
Manhattan Distance Heuristic: Estimates the number of moves required to reach the goal state.
Handles customizable puzzle sizes (e.g., 8-puzzle, 15-puzzle) and initial/goal states.
Tracks solution paths, number of moves, and time taken to solve.
Includes functionality to read input from files and display the solution visually.
# How It Works:
The puzzle is represented as a 2D grid with numbered tiles and a blank space (0).
The solver starts from an initial state and uses A* to find the shortest path to the goal state.
The path is displayed along with the moves taken (Up, Down, Left, Right) and time to solution.
# Usage:
  Input: Puzzle size, initial state, goal state, and maximum moves.
  Output: Solution path with directions and statistics.
# Technologies Used:
  C++: The entire solver is implemented in C++.
  STL Libraries: Used for data structures like vectors, priority queues, and unordered maps.
  Chrono: Measures time taken to solve the puzzle.
