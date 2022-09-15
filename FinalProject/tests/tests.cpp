#include <string>
#include <vector>
#include <queue>

#include "../catch/catch.hpp"
#include "../src/readFile.h"
#include "../src/BFS.h"
#include "../src/Airport.h"
#include "../src/interaction.h"


TEST_CASE("Check file_to_string works on a small test data") {
	std::string res = file_to_string("tests/testdata1.dat");
	REQUIRE("hello\nhaiyuez2\nshi40\nhaozhen6\n225\n!!!" == res);
}

TEST_CASE("Check file_to_vector works on a small test data") {
	std::vector<std::string> res = file_to_vector("tests/testdata1.dat");
	std::string expected[] = {"hello", "haiyuez2", "shi40", "haozhen6", "225", "!!!"};
	// check elements
	for (int i = 0; i < res.size(); ++i) {
		REQUIRE(expected[i] == res[i]);
	}
	// check size
	REQUIRE(6 == res.size());
}

TEST_CASE("Check BFS works on a small graph part-1") {
	Graph graph(7);
	graph.insert_edge(1, 2);
	graph.insert_edge(1, 3);
	graph.insert_edge(2, 4);
	graph.insert_edge(2, 5);
	graph.insert_edge(3, 5);
	graph.insert_edge(4, 5);
	graph.insert_edge(4, 6);
	graph.insert_edge(5, 6);

	int expected[] = {1, 2, 3, 4, 5, 6};
	// check elements of BFS traversal
	std::queue<int> res = graph.BFS(1, false);
	for (int i = 0; i < res.size(); ++i) {
		REQUIRE(expected[i] == res.front());
		res.pop();
	}
}

TEST_CASE("Check BFS works on a small graph part-2") {
	Graph graph(7);
	graph.insert_edge(1, 2);
	graph.insert_edge(1, 3);
	graph.insert_edge(2, 4);
	graph.insert_edge(2, 5);
	graph.insert_edge(3, 5);
	graph.insert_edge(4, 5);
	graph.insert_edge(4, 6);
	graph.insert_edge(5, 6);

	int expected[] = {5, 6};
	// check elements of BFS traversal
	std::queue<int> res = graph.BFS(5, false);
	for (int i = 0; i < res.size(); ++i) {
		REQUIRE(expected[i] == res.front());
		res.pop();
	}
}

TEST_CASE("Check BFS works on a small graph part-3") {
	Graph graph(4);
    graph.insert_edge(0, 1);
    graph.insert_edge(0, 2);
    graph.insert_edge(1, 2);
    graph.insert_edge(2, 0);
    graph.insert_edge(2, 3);
    graph.insert_edge(3, 3);
	int expected[] = {2, 0, 3, 1};
	// check elements of BFS traversal
	std::queue<int> res = graph.BFS(2, false);
	for (int i = 0; i < res.size(); ++i) {
		REQUIRE(expected[i] == res.front());
		res.pop();
	}
}

TEST_CASE("Check BFS works on a small graph part-4") {
	Graph graph(4);
    graph.insert_edge(0, 1);
    graph.insert_edge(0, 2);
    graph.insert_edge(1, 2);
    graph.insert_edge(2, 0);
    graph.insert_edge(2, 3);
    graph.insert_edge(3, 3);
	int expected[] = {3};
	// check elements of BFS traversal
	std::queue<int> res = graph.BFS(3, false);
	for (int i = 0; i < res.size(); ++i) {
		REQUIRE(expected[i] == res.front());
		res.pop();
	}
}

TEST_CASE("Check Dijkstra algorithm") {
	initializeAirportData();
	initializeDistanceData();
	initializeRestDistanceData();
	int dis[AirportNum];
    int path[AirportNum]; 
    bool visited[AirportNum];
	Dijkstra(1, dis, path, visited);
	vector<int> vec;
	int p = 2;
    vec.push_back(p);
    while (path[p] != -1) {
        p = path[p];
        vec.push_back(p);
    }
    vec.push_back(1);
	REQUIRE(vec.size() == 2);
	REQUIRE(airportlist[vec[0]].name == "\"HGU\"");
}

TEST_CASE("Check Dijkstra algorithm in longer path") {
	initializeAirportData();
	initializeDistanceData();
	initializeRestDistanceData();
	int dis[AirportNum];
    int path[AirportNum]; 
    bool visited[AirportNum];
	Dijkstra(3367, dis, path, visited);
	vector<int> vec;
	int p = 3575;
    vec.push_back(p);
    while (path[p] != -1) {
        p = path[p];
        vec.push_back(p);
    }
    vec.push_back(3367);
	REQUIRE(vec.size() == 5);
	REQUIRE(airportlist[vec[2]].name == "\"YVR\"");
}

TEST_CASE("Check find most important airport") {
	initializeAirportData();
	initializeDistanceData();
	initializeRestDistanceData();
	int airportID = 2;
	vector<int> vec;
	int times = 60;
	vec = getMostimportantAirport(airportID, times);
	REQUIRE(vec.size() == 36);
}

TEST_CASE("Check relax") {
	int w, x, delta, tent[1];
	map<int, unordered_set<int>> B;

	w = 0;
	x = 20;  // should replace original tent
	delta = 30;
	tent[0] = 40;  // should be in bucket 1
	B[1].insert(0);
	relax(w, x, delta, tent, B);
	REQUIRE(tent[0] == 20);
	REQUIRE(B[1].empty());
	REQUIRE(B[0].count(0) > 0);
	B[0].clear();

	w = 0;
	x = 60;  // should not replace original tent
	delta = 30;
	tent[0] = 40;  // should be in bucket 1
	B[1].insert(0);
	relax(w, x, delta, tent, B);
	REQUIRE(tent[0] == 40);
	REQUIRE(B[1].count(0) > 0);
	REQUIRE(B[0].empty());
}

TEST_CASE("Check firstNonEmpty") {
	map<int, unordered_set<int>> B;
	B[100].insert(100);
	B[5].insert(5);
	B[8].insert(8);
	B[58].insert(58);
	REQUIRE(firstNonEmpty(B) == 5);
	B[5].clear();
	REQUIRE(firstNonEmpty(B) == 8);
}

TEST_CASE("Check findRequestsLight") {
	int delta, tent[1];
	unordered_set<int> V;

	for (size_t i = 0; i < AirportNum; i++) {
        for (size_t j = 0; j < AirportNum; j++) {
            distances[i][j] = INT32_MAX;
        }
    }
	distances[0][4] = 30;
	distances[0][10] = 40;
	distances[0][30] = 50;
	tent[0] = 40;
	delta = 40;
	V.insert(0);
	vector<pair<int, int>> result = findRequestsLight(V, delta, tent);
	vector<pair<int, int>> ans = {{4, 70}, {10, 80}};
	REQUIRE(result == ans);
}

TEST_CASE("Check findRequestsHeavy") {
	int delta, tent[1];
	unordered_set<int> V;

	for (size_t i = 0; i < AirportNum; i++) {
        for (size_t j = 0; j < AirportNum; j++) {
            distances[i][j] = INT32_MAX;
        }
    }
	distances[0][4] = 30;
	distances[0][10] = 40;
	distances[0][30] = 50;
	tent[0] = 40;
	delta = 40;
	V.insert(0);
	vector<pair<int, int>> result = findRequestsHeavy(V, delta, tent);
	vector<pair<int, int>> ans = {{30, 90}};
	REQUIRE(result == ans);
}

TEST_CASE("Check DeltaStepping") {
	for (size_t i = 0; i < AirportNum; i++) {
        for (size_t j = 0; j < AirportNum; j++) {
            distances[i][j] = INT32_MAX;
        }
    }
	auto set_distance = [&](int i, int j, int d) {
		distances[i][j] = distances[j][i] = d;
	};
	set_distance(0, 4, 30);
	set_distance(0, 10, 40);
	set_distance(0, 30, 50);
	set_distance(40, 30, 50);
	
	int tent[AirportNum];
    map<int, unordered_set<int>> B;
	DeltaStepping(30, 3000, tent, B);
	REQUIRE(tent[0] == 50);
	REQUIRE(tent[10] == 90);
	REQUIRE(tent[40] == 50);
}