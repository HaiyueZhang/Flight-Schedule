# Results
## BFS
### The output and correctness of each algorithm
- The Breadth-First-Search (BFS) algorithm is implemented by adjacency list of graphs. The adjacent nodes are used for storing airport ID and the adjacent edges are applied by saving the route ID. Users can input any source airport ID as a starting vertex for traversal. The output of BFS is visualized by a series of sequential airport ID.
- The correctness of the BFS algorithm is validated by four test cases. The test database comprises a couple of small synthetic datasets. In a nutshell, the outputs of the BFS test match the expected results.

### The answer to your leading question
- BFS algorithm is successfully completing the implementation of airport ID traversal functionality.


## Dijkstra algorithm
### The output and correctness of each algorithm
- Dijkstra algorithm can find the shortest path between two airports, which records each node along shortest path between two arbitrary airports. Also, it can find the most important airport from one airport. The output is displayed on user interface, finding the shortest path is Option 1, finding the most important airport is Option 3.
- In average, both finding the shortest path between two airports and finding the most important airport takes 1.7 seconds to execute.
- There are two test cases focused on dijkstra algorithm, which are "Check Dijkstra algorithm", "Check Dijkstra algorithm in longer path" in tests.cpp. The first test case is based on a short path between airportID 2 to  airportID 3，which tests number of airports and name of destination in the path. The second test case is based on a longer and complex path, which tests number of airports and name of one transfer airport in the path.
- Test case "Check find most important airport" is focused on finding most important airport, which tests number of airports which are passed by over 60 times from source airport.
### The answer to your leading question
- Dijkstra algorithm answers the leading question "finding the shortest route between any two cities". We find that most airports do not have direct routes with each other, which means there are at least one transfer.
- Dijkstra algorithm also solves the question "finding most important airport from one airport".

## Delta stepping algorithm
### The output and correctness of each algorithm
- Delta stepping algorithm we implemented is capable of finding the minimum travel distance between two arbitrary airports using less time (in average 0.8 seconds to compute min travel distance between any two airports) than Dijkstra algorithm, though currently it is not capable of recording the actual path.
- The algorithm is divided into several functions according to original paper, including relax, relaxRequests, findRequestsLight, findRequestsHeavy, and DeltaStepping itself. All functions are individually tested and yielded correct results.
- We only implemented the sequential version of the algorithm instead of the parallel one, but the execution time is already desirable enough.

### The answer to your leading question
- Delta stepping algorithm provides a faster way to determine minimum distance between to airports in cases where actual path is not needed.

## Conclusion
In conclusion, all our algorithms (BFS, Dijkstra, and Delta Stepping) sucessfully achieved our project goals. Also, with a user friendly command line interface, users can easily request desired computation of flight paths, travel distances, or most important airports. Therefore, the project yields overall satisfactory results.