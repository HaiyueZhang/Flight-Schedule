#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
//Macro definition
#define AirportNum 14110

using std::map;
using std::string;
using std::vector;
using std::unordered_set;
using std::pair;
using std::cout;
using std::endl;
struct Airport {
    // Airport ID
    int numid = -1;
    // Airport code name
    string name;
    // Airport Latitude
    double x;
    // Airport Longitude
    double y;
};

//Global variable initialization
//Adjacency Matrix, departure airport, destination airport
extern int distances[AirportNum][AirportNum];

//Global variable initialization
extern Airport airportlist[AirportNum];

//Global variable initialization
extern map<int, Airport> airportmap;

//Initialize each source in AirportData
void initializeAirportData();

//Initialize distances between two airports in each routes
void initializeDistanceData();

//The dataset is too huge, so we process them in two batches
void initializeRestDistanceData();

//Dijkstra algorithm process
void Dijkstra(int airportID, int * dis, int * path, bool * visited);

void relax(int w, int x, int delta, int * tent, map<int, unordered_set<int>> &B);

vector<pair<int, int>> findRequestsLight(unordered_set<int> V, int delta, int * tent);

vector<pair<int, int>> findRequestsHeavy(unordered_set<int> V, int delta, int * tent);

inline void relaxRequests(vector<pair<int, int>> Req, int delta, int * tent, map<int, unordered_set<int>> &B);

int firstNonEmpty(map<int, unordered_set<int>> &B);

void DeltaStepping(int airportID, int delta, int * tent, map<int, unordered_set<int>> &B);
