# AI Puzzle Solver (N-Puzzle, A* Search)

A C++ program that solves the N-Puzzle (for example the 8-puzzle or 15-puzzle) by finding the shortest sequence of moves with the **A\* search algorithm** and the **Manhattan distance** heuristic.

## How it works
1. Reads the start board from `input.txt`
2. Expands board states in order of `f(n) = g(n) + h(n)`: moves so far plus the summed Manhattan distance of every tile from its goal square
3. Skips states it has already visited
4. Prints the optimal move sequence and the number of moves

## Build and run
```bash
g++ -O2 -std=c++17 Puzzle.cpp -o puzzle
./puzzle
```
Edit `input.txt` to try another starting board. `Report.docx` explains the approach and results.

## Tech
C++ · A* search · heuristic search · priority queue

---

**Built by [Abdullah Ahmad](https://abdullah-ahmad-portfolio.vercel.app)**, Full Stack Software Engineer in Lahore, Pakistan · [GitHub](https://github.com/Abdullahahmad666) · [LinkedIn](https://www.linkedin.com/in/abdullah-ahmad-a00913259/)
