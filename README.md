# DFA Minimization

## Description

This project implements a **Deterministic Finite Automaton (DFA) Minimization** algorithm in C++. The goal of DFA minimization is to reduce the number of states in a DFA while preserving its behavior. The implementation uses partition refinement to identify and merge equivalent states.

### Key Features:
- Supports DFA representation with user-defined states, alphabet, transitions, and final states.
- Implements partition refinement to minimize DFA states.
- Input is provided through standard input in a specific format (explained below).

## Algorithm Overview

The minimization algorithm uses **equivalence class refinement**:
1. **Initial Partitioning**: States are split into two sets—final states and non-final states.
2. **Refinement**: The algorithm iteratively splits the states into smaller partitions based on the behavior of the DFA transitions for each input symbol.
3. **Minimized DFA**: States that behave identically are merged, resulting in a minimized DFA.

## File Structure
.
├── main.cpp        # Main implementation of the DFA minimization algorithm
└── README.md       # This README file

## Getting Started

### Prerequisites

- **C++11 or later**: The code is written in modern C++ and requires a C++11 compliant compiler.

### Compilation

To compile the program, you can use any standard C++ compiler such as `g++`.

```bash
g++ -std=c++11 main.cpp -o minimize_dfa
```
### Running the Program
Once compiled, you can run the executable. The program takes input in a specific format via stdin. Here's the required input format:

1. Number of states: N states, followed by their names.
2. Number of symbols in the alphabet: M symbols, followed by the symbols.
3. Number of final states: F, followed by the final states.
4. Number of transitions: T, followed by transitions in the format: from_state,input_symbol,to_state.


### Example Input:

```bash
5
q0 q1 q2 q3 q4
2
a b
1
q3
7
q0,a,q1
q0,b,q2
q1,a,q3
q1,b,q4
q2,a,q4
q2,b,q3
q3,a,q3
```

### Output
The program will output the number of states in the minimized DFA.Output
The program will output the number of states in the minimized DFA.

### Example Output:
```bash
3
```
### Input Format Explanation

- **States**: List of states, e.g., q0, q1, q2, etc.
- **Alphabet**: List of alphabet symbols, e.g., a, b.
- **Final States**: List of accepting states.
- **Transitions**: Describes the DFA transitions. Each transition is in the format from_state, input_symbol, to_state.

### Example
Given the DFA in the input section above, the minimized DFA has 3 states. The output reflects the number of states after minimization.

### How It Works
- **DFS for Reachable States**: The algorithm first performs a Depth First Search (DFS) to identify all reachable states from the start state and marks unreachable states for removal.
- **Partition Refinement**: It then applies partition refinement based on the behavior of the DFA transitions.
- **State Merging**: Equivalent states are merged to minimize the DFA.

## Contributing
Contributions are welcome! If you'd like to contribute:

- Fork the repository.
- Create a feature branch (git checkout -b feature-branch).
- Commit your changes (git commit -m "Add new feature").
- Push to the branch (git push origin feature-branch).
- Open a pull request.
