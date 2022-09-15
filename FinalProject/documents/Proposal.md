# Final Project Proposal

## Leading Question
[OpenFlights](https://openflights.org/data.html) has been selected to be the dataset of our final project. We plan to build a program based on graph algorithms that can find the shortest route between any two cities **with airports**.

The dataset contains longitude and latitude data of each airport. With [haversine formula](https://en.wikipedia.org/wiki/Haversine_formula), we can compute [great-circle distance](https://en.wikipedia.org/wiki/Great-circle_distance) (the distance between points on the surface of the earth) between each airport. Mapping each airport to a vertex and the great-circle distance between them to the weight of edge, we can convert airport and distance information into a graph-like structure. Thus, we can utilize graph algorithms including Dijkstra's Algorithm and Delta Step Algorithm to find shortest **flight** path between two arbitrary airports in the map efficiently.

We will also build a visualization method to display this route on a world map if time allows.

## Dataset Acquisition and Processing 
The publicly accessible dataset we have chosen to use is [OpenFlights](https://openflights.org/data.html). Due to necessity of reformatting and existence of dirty data, we will implement data cleaning for pre-processing.

### Data Format
We plan to use airports data and routes data provided by OpenFlights. After pre-processing, only subsets will be considered for selected data and their information are shown in below two tables.
- airports data

| Key | Description |
|---|---|
| Airport ID | Unique OpenFlights identifier for this airport. |
| Name | Name of airport. May or may not contain the City name. |
| City | Main city served by airport. May be spelled differently from Name. |
| Country | Country or territory where airport is located. See Countries to cross-reference to ISO 3166-1 codes. |
| Latitude | Decimal degrees, usually to six significant digits. Negative is South, positive is North. |
| Longitude | Decimal degrees, usually to six significant digits. Negative is West, positive is East. |

- routes data

| Key | Description |
|---|---|
| Airline | 2-letter (IATA) or 3-letter (ICAO) code of the airline. |
| Airline ID | Unique OpenFlights identifier for airline (see Airline). |
| Source airport | 3-letter (IATA) or 4-letter (ICAO) code of the source airport. |
| Source airport ID | Unique OpenFlights identifier for source airport (see Airport) |
| Destination airport | 3-letter (IATA) or 4-letter (ICAO) code of the destination airport. |
| Destination airport ID | Unique OpenFlights identifier for destination airport (see Airport) |
| Stops | Number of stops on this flight ("0" for direct) |

### Data Correction
1. Transfer the raw data into dataframe and use [Pandas](https://pandas.pydata.org/) package to implement the data wrangling. In Pandas missing data is represented by NaN. Drop entries contaning NaN.
2. From the primary key, airport ID, join two data tables by using [MySQL](https://www.mysql.com/). After natural join of two tables, there will not be any missing data.
3. Finally, export the corrected data into a new file.

### Data Storage
The data structure that we are going to use for storing data is 2D array. Every entry (row) will be stored in a 1D array. Below table shows an estimate of the total storage costs for the dataset in Big O notation.

| ARRAY OPERATION | TIME COMPLEXITY |
|---|---|
| Access i-th routes | O(1) |
| Traverse all routes | O(V) |
| Insert element E | O(V) |
| Delete element E | O(V) |

Also, we can use vector to store data of departure airport ID, destination airport ID and distance. And use map to store the frequency of every airport passes by each shortest paths.

## Algorithms
- Graph Traversal Algorithm
    - We plan to use Breadth-First-Search (BFS) for the traversal of our graph. 
    - Time Complexity: O(V+E) 
        - V is a number of vertices in the graph
        - E is a number of edges in the graph
    - The implementation of BFS is shown as following steps,
        1. List container (STL) will be used to store adjacency of each vertex, i.e. adjacent nodes.
        2. The std::queue will be applied for BFS traversal, the same idea as BFS of tree.
        3. Boolean visited vector will be used for avoiding read a node more than once.

- Dijkstra's Algorithm
    - This algorithm can solve issue: Any Shortest Path algorithm to find preferred routes.
    - Our function inputs include departure airport ID, destination airport ID and distance, which will traverse all the possible  paths(direct or stops) between two airports. Our function output will show the shortest path's explicit details(airline, plane type, departure, destination, direct/stop) in command line.
    - We use map store frequency and utilize Dijkstra's algorithm to count up the frequency of each airport’s appearance by traversing all paths in the graph. The most important airports have highest frequency.
    - We rank the most important cities by data of frequency.
    - The time complexity is O((V^2), and space complexity is O(V). V represents the  number of vertices, and E represents the number of edges.
- Delta Stepping Algorithm
    - This algorithm is an improved SSSP algorithm that classifies vertics into buckets to support parallel calculation, thus having a smaller time complexity relative to Dijkstra's Algorithm.
    - The input and output of this algorithm will be the same as Dijkstra's algorithm: input airport and paths information as well as two airports of interests; output the detail of the shortest path between the two airports.
    - For the algorithm to work correctly, we need to also choose a reasonable $\Delta$ value that represents the size of each bucket to classify vertices. Choosing $\Delta =\Theta(1/d)$ (where $d$ is the maximum degree of the graph) will work for most cases according to original paper.
    - The sequential version of the algorithm is expected to have the time complexity of $O(V+E+dL)$; the parallel version of the algorithm has the time complexity of $O(d^2L\log^2V)$. $V$ represents the  number of vertices, $E$ represents the number of edges, $d$ represents the maximum degree of the graph, and $L$ represents maximum shortest path weight.
- Data Visualization(optional)
    - We can use [Force-directed Algorithm](https://en.wikipedia.org/wiki/Force-directed_graph_drawing) to project shortest path on world map graphically, and utilize world map and some other graph sources from [OpenFlights data](https://github.com/jpatokal/openflights/tree/master/data), which can help us establish visualization.
    
## Timeline
| Time | Task |
|---|---|
| 04/01 | 1. Makefile Initialization   2. Catch test environment establishment  |
| 04/08 | 1. Data pre-processing   |
| 04/15 | 1. BFS    2. Dijkstra's algorithm |
| 05/01 | 1. Delta stepping algorithm    2. Data visualization on world map (hard task optional) |
| 05/06 | 1. Final report 2. Final presentation |
