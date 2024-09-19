#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;

// Puzzle State
class Puzzle 
{
public:
    int size;
    vector<int> starting_state;
    vector<int> goal_state;
    unordered_map<int, int> goal_index;

    Puzzle(int size, vector<int> start_state, vector<int> goal_state) : size(size), starting_state(start_state), goal_state(goal_state)
    {
        
        for (int i = 0; i < goal_state.size(); i++)
        {
            goal_index[goal_state[i]] = i;
        }
    }

     // Bool to Check Goal State
    bool is_goal(const vector<int>& state) 
    {
        return state == goal_state;
    }

    // Explore Neighbours
    vector<pair<vector<int>, pair<int, int>>> neighbours(const vector<int>& state) 
    {
        vector<pair<vector<int>, pair<int, int>>> neighbours;
        vector<int> copy = state;
        int zero_index = find(state.begin(), state.end(), 0) - state.begin();
        int zero_row = zero_index / size;
        int zero_col = zero_index % size;

        // Moves of Space
        vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (auto dir : directions) 
        {
            int updated_row = zero_row + dir.first;
            int updated_column = zero_col + dir.second;
            if (updated_row >= 0 && updated_row < size && updated_column >= 0 && updated_column < size) 
            {
                int new_zero = updated_row * size + updated_column;
                swap(copy[zero_index], copy[new_zero]);
                neighbours.push_back({ copy, dir });
                swap(copy[new_zero], copy[zero_index]); 
            }
        }
        return neighbours;
    }

    // Heuristic
    int manhattan(const vector<int>& state) 
    {
        int distance = 0;
        for (int i = 0; i < state.size(); i++)
        {
            if (state[i] == 0) continue;  // Ignore the empty tile
            int goal = goal_index[state[i]];
            int current_row = i / size;
            int current_col = i % size;
            int goal_row = goal / size;
            int goal_col = goal % size;
            distance += abs(current_row - goal_row) + abs(current_col - goal_col);
        }
        return distance;
    }

   

    
};

// A* Node structure for storing state, nodecost-value, finalcost-value, parent, and direction
struct AStarNode 
{
    vector<int> state;
    int node_cost;  // Cost of node
    int final_cost;  // Estimated (node_cost + heuristic)
    AStarNode* parent;
    pair<int, int> direction;

    AStarNode(vector<int> state, int nodecost, int finalcost, AStarNode* parent = nullptr, pair<int, int> direction = { 0, 0 })
        : state(state), node_cost(nodecost), final_cost(finalcost), parent(parent), direction(direction) {}
};

// Priority queue (min-heap)
struct PriorityQueue 
{
    bool operator()(AStarNode* a, AStarNode* b) 
    {
        return a->final_cost > b->final_cost; // Min-heap based on finalcost-value
    }
};

// (Dijkstra + Manhattan Heuristics)
class AStar 
{
public:
    Puzzle puzzle;

    AStar(Puzzle puzzle) : puzzle(puzzle) {}

    pair<vector<vector<int>>, vector<string>> solve(int max_moves) 
    {
        priority_queue<AStarNode*, vector<AStarNode*>, PriorityQueue> queue_set;
        unordered_map<string, int> goal_score;

        vector<int> start_state = puzzle.starting_state;
        vector<int> goal_state = puzzle.goal_state;

        // Push the starting_state into the priority queue
        queue_set.push(new AStarNode(start_state, 0, puzzle.manhattan(start_state)));

        goal_score[helper(start_state)] = 0;

        while (!queue_set.empty()) 
        {
            AStarNode* current_node = queue_set.top();
            queue_set.pop();

            // Check the goal
            if (puzzle.is_goal(current_node->state)) 
            {
                return reconstruct_path_directions(current_node);
            }

            // Explore neighbors
            for (auto neighbour_pair : puzzle.neighbours(current_node->state)) 
            {
                vector<int> neighbouring_state = neighbour_pair.first;
                pair<int, int> move_direction = neighbour_pair.second;

                int goal_moves = current_node->node_cost + 1;
                if (goal_moves <= max_moves) 
                {
                    string neighbor_key = helper(neighbouring_state);
                    if (goal_score.find(neighbor_key) == goal_score.end() || goal_moves < goal_score[neighbor_key]) 
                    {
                        goal_score[neighbor_key] = goal_moves;
                        int final_moves = goal_moves + puzzle.manhattan(neighbouring_state);
                        queue_set.push(new AStarNode(neighbouring_state, goal_moves, final_moves, current_node, move_direction));
                    }
                }
            }
        }
        return { {}, {} }; // Empty state is no Solution found
    }

private:
    // Helper function 
    string helper(const vector<int>& state) 
    {
        string s;
        for (int num : state) 
        {
            s += to_string(num) + ",";
        }
        return s;
    }

    // Reconstruct the path and directions
    pair<vector<vector<int>>, vector<string>> reconstruct_path_directions(AStarNode* node) 
    {
        vector<vector<int>> goal_path;
        vector<string> directions;
        AStarNode* current = node;

        while (current != nullptr) 
        {
            goal_path.push_back(current->state);
            if (current->parent != nullptr) 
            {
                directions.push_back(get_move_direction(current->direction));
            }
            current = current->parent;
        }

        reverse(goal_path.begin(), goal_path.end());
        reverse(directions.begin(), directions.end());

        return { goal_path, directions };
    }

    // Pair to String to show the Moves
    string get_move_direction(pair<int, int> direction) 
    {
        if (direction == make_pair(-1, 0)) return "Up";
        if (direction == make_pair(1, 0)) return "Down";
        if (direction == make_pair(0, -1)) return "Left";
        if (direction == make_pair(0, 1)) return "Right";
        return "";
    }
};

// Read the input
void read(const string& inputfilename, int& size_of_array, int& max_moves, vector<int>& start_state, vector<int>& goal_state) 
{
    freopen(inputfilename.c_str(), "r", stdin); // Open file 
    cin >> size_of_array >> max_moves;
    start_state.resize(size_of_array * size_of_array);
    goal_state.resize(size_of_array * size_of_array);
    for (int i = 0; i < size_of_array * size_of_array; i++)
    {
        cin >> start_state[i];
    } 
    for (int i = 0; i < size_of_array * size_of_array; i++)
    {
        cin >> goal_state[i];
    } 
}

// Main
int main() 
{
    string filename = "input.txt"; 
    int sizeofarray, max_moves;
    vector<int> starting_state;
    vector<int> goal_state;

    read(filename, sizeofarray, max_moves, starting_state, goal_state);
    Puzzle puzzle(sizeofarray, starting_state, goal_state);
    AStar solver(puzzle);

    auto starting_time = chrono::high_resolution_clock::now();
    auto [solution, moves] = solver.solve(max_moves);
    auto ending_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time = ending_time - starting_time;

    if (!solution.empty()) 
    {
        cout << "Solved in " << moves.size() << " moves:\n";
        for (int i = 0; i < solution.size(); i++) {
            if (i > 0) 
            {
                cout << "Move " << i << ": " << moves[i - 1] << "\n";
            }
            for (int j = 0; j < sizeofarray * sizeofarray; j++) 
            {
                if (j % sizeofarray == 0 && j != 0) cout << "\n";
                cout << solution[i][j] << " ";
            }
            cout << "\n\n";
        }
        cout << "Time taken to rech Goal State: " << time.count() << " seconds\n";
    } else {
        cout << "No solution found within " << max_moves << " moves.\n";
        cout << "Time taken to Fail: " << time.count() << " seconds\n";
    }

    return 0;
}
