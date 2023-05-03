#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector;

//User interface
void userOption();

//Find the shortest path between two airports
//src: departure airportID
//dest: destination airportID
void searchMinPath(int src, int dest);
void searchMinDistance(int src, int dest);

//Find the most important airports
vector<int> getMostimportantAirport(int src, int times);

// Error handling for inputting invalid airport ID
int checkValid(int airportID);
