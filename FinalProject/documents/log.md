# Development Log

## 05/02 - 05/06
### Goals
- [x] 1. Add more test cases for BFS
- [X] 2. Implementation of error handling for invalid input airport ID

### Specific Tasks
- Shitao Shi
    - [x] Add more test cases for BFS
    - [x] Implementation of error handling for invalid input airport ID

- Haiyue Zhang
    - [x] Implementation of getting most important Airport
    - [x] Create a test case for Dijkstra

- Raymond Wu
    - [x] Add test case for Delta stepping algorithm

### Encountered Problems


## 04/25 - 05/01
### Goals
- [x] 1. Implementation of Delta stepping algorithm
- [X] 2. Solve bugs on Dijkstra algorithm

### Specific Tasks
- Haiyue Zhang
    - [x] Solve bugs on Dijkstra algorithm

- Raymond Wu
    - [x] Implementation of Delta stepping algorithm

### Encountered Problems
- Haiyue Zhang
    - SearchMinPath function reports non-connected, redundant path, which means there are some bugs on Dijkstra algorithm. 
    Finally, I found mistakes and solved them.

### Plans for next week
- [ ] Add more test cases for BFS
- [ ] Implementation of error handling for invalid input airport ID in BFS
- [ ] Create a test case for Dijkstra
- [ ] Add test case for Delta stepping algorithm
- [ ] Implementation of getting most important Airport

## 04/18 - 04/24
### Goals
- [x] 1. Implementation of BFS algorithm
- [X] 2. Update user interface
- [x] 3. Add test cases
- [x] 4. Complete Mid-Project Checkin

### Specific Tasks
- Shitao Shi
    - [x] Implementation of BFS algorithm
    - [X] Update user interface
    - [x] Add test cases
    - [x] Participate Mid-Project Checkin

- Haiyue Zhang
    - [x] Participate Mid-Project Checkin

### Encountered Problems

### Plans for next week
- [ ] Implementation of Delta stepping algorithm
- [ ] Add more test cases for BFS
- [ ] Implementation of error handling for invalid input airport ID in BFS
- [ ] Create a test case for Dijkstra
- [ ] Achieve error handling for invalid path in Dijkstra's algorithm (SEGFAULTS!!!)


## 04/11 - 04/17
### Goals
- [x] 1. Writing Dijkstra's algorithm
- [X] 2. Initializing airport and distance data
- [x] 3. Making user interface
- [x] 4. Debug for data parsing

### Specific Tasks
- Haiyue Zhang
    - [x] Writing Dijkstra's algorithm
    - [x] Initializing airport and distance data
    - [x] Making user interface

- Shitao Shi
    - [x] Debug for data parsing

### Encountered Problems
- Haiyue Zhang
    - When I tried to make my code, I found my global variables have multiple definition errors. So I use extern to solve this issue
    - I defined a macro definition "AirportNum" in my Airport.h. Because I once found it is hard to change AirportNum in global variables. Macro definition can help me change this variable directly.

### Plans for next week
- [ ] Implementation of BFS algorithm
- [ ] Implementation of Delta stepping algorithm
- [ ] Preparation for mid-project check

## 04/04 - 04/10
### Goals
- [x] 1. Data pre-processing
- [x] 2. Preparation of seting up algorithms


### Specific Tasks

- Shitao Shi
    - [x] Data pre-processing.

- Haiyue Zhang
    - [x] Create Airport.cpp and Airport.cpp
 
### Encountered Problems
- We have different habit on code writing. We choose and follow an uniform style to write in the future.

### Plans for next week
- [ ] Writing algorithms(BFS, Dijkstra's algorithm, Delta stepping algorithm)

## 03/28 - 04/03
### Goals
- [x] 1. Makefile Initialization   
- [x] 2. Catch test environment establishment   
- [x] 3. Resubmit proposal

### Specific Tasks
- Haiyue Zhang
    - [x] I improve and rewrite Dijkstra's Algorithm part in algorithms, including time complexity and specific work we will done by Dijkstra's Algorithm.

- Shitao Shi
    - [x] Initialized test environment.
    - [x] Initialized makefile.
    - [x] Implemented read from file.
    - [x] Implemented display of data.
    - [x] Described Dataset & BFS algorithm in proposal.

- Raymond Wu
    - [x] Delta Stepping Algorithm
    - [x] Rewrite leading question
 
### Encountered Problems
- Haiyue Zhang
    - The complexity described for Dijkstra in our last proposal is achieved by using min-heap and priority queues. I need to find the time complexity of Dijkstra's Algorithm in common case.

### Plans for next week
- [ ] Data pre-processing
- [ ] Preparation of seting up algorithms
