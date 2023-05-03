#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "interaction.h"
#include "readFile.h"
#include "Airport.h"
#include "BFS.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::map;

void userOption() {
    cout << "---------------------------------------------------" << endl;
    cout << "|       CS225 Final Project OpenFlights           |" << endl;
    cout << "|                                                 |" << endl;
    cout << "| 0 - Traversal the airline routes (BFS).         |" << endl;
    cout << "| 1 - Find the min path between two airports.     |" << endl;
    cout << "| 2 - Find the min distance between two airports. |" << endl;
    cout << "| 3 - Find the most important airports from your  |" << endl;
    cout << "|     airport.                                    |" << endl;
    cout << "| 4 - Exit.                                       |" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Please select an option from above lists: " << endl;
    int option;
    cin >> option;
    if (option == 0) {
        int airportID, visualize;
        cout << "Please input your Starting Airport ID: " << endl;
        cin >> airportID;
        airportID = checkValid(airportID);
        cout << "Visualize your result? 1=true, 0=false" << endl;
        cin >> visualize;
        routes_traversal(airportID, visualize);
    } else if (option == 1) {
        cout << "Input your Source Airport ID: " << endl;
        int airportID;
        cin >> airportID;
        airportID = checkValid(airportID);
        int destAirportID;
        cout << "Input your Destination Airport ID: " << endl;
        cin >> destAirportID;
        destAirportID = checkValid(destAirportID);
        searchMinPath(airportID, destAirportID);
    } else if (option == 2) {
        cout << "Input your Source Airport ID: " << endl;
        int airportID;
        cin >> airportID;
        airportID = checkValid(airportID);
        int destAirportID;
        cout << "Input your Destination Airport ID: " << endl;
        cin >> destAirportID;
        destAirportID = checkValid(destAirportID);
        searchMinDistance(airportID, destAirportID);
    } else if (option == 3) {
        cout << "Input your Source Airport ID: " << endl;
        int airportID;
        vector<int> vec;
        cin >> airportID;
        airportID = checkValid(airportID);
        cout << "Input the minimum times airports are passed by from your Source Airport: " << endl;
        int times;
        cin >> times;
        vec = getMostimportantAirport(airportID, times);
        for (size_t i = 0; i < vec.size(); i++) {
            if (airportlist[vec[i]].name != "\\N") {
                cout << airportlist[vec[i]].name << " ";
            }        
        }
        cout << endl;
    } else {
        cout << "Bye!" << endl;
    }
}

void searchMinPath(int src, int dest) { 
    src--;
    dest--;
    if (airportlist[src].numid == -1 || airportlist[dest].numid == -1) {
        cout << "Invalid airport ID" << endl;
        return;
    }
    int dis[AirportNum];
    int path[AirportNum]; 
    bool visited[AirportNum];
    Dijkstra(src, dis, path, visited);
    cout << "The minimum path is displayed below" << endl;
    vector<int> vec;
    // cout << path[2] << "!!!" << endl;
    int p = dest;
    vec.push_back(p);
    while (path[p] != -1) {
        p = path[p];
        vec.push_back(p);
    }
    vec.push_back(src);
    // for (size_t i = 0; i < vec.size(); i++) {
    //     cout << vec[i] << endl;
    // }
    while (!vec.empty()) {
        cout << airportlist[vec.back()].name;
        if (vec.size() > 1) {
            cout << "--";
        }
        vec.pop_back();
    }
    cout << endl;
}

void searchMinDistance(int src, int dest) {
    src--;
    dest--;
    if (airportlist[src].numid == -1 || airportlist[dest].numid == -1) {
        cout << "Invalid airport ID" << endl;
        return;
    }
    int tent[AirportNum];
    map<int, unordered_set<int>> B;
    DeltaStepping(src, 3000, tent, B);
    cout << "Distance: " << tent[dest] << endl;
}

vector<int> getMostimportantAirport(int src, int times) {
    src--;
    vector<int> result;
    if (airportlist[src].numid == -1) {
        cout << "Invalid airport ID" << endl;
        return result;
    }
    map<int, int> frequency;
    int dis[AirportNum];
    int path[AirportNum]; 
    bool visited[AirportNum];
    Dijkstra(src, dis, path, visited);
    for(int i = 0; i < AirportNum; i++) {
        if (i == src) {
            continue;
        }
        int p = i;
        if (frequency.find(p) == frequency.end()) {
            frequency[p] = 0;
        }
        frequency[p] = frequency[p] + 1;
        while (path[p] != -1) {
            p = path[p];
            if (frequency.find(p) == frequency.end()) {
                frequency[p] = 0;
            }
            frequency[p] = frequency[p] + 1;
        } 
    }
    map<int, int>::iterator it;
    for (it = frequency.begin(); it != frequency.end(); it++) {
        if (it -> second >= times) {
            if (airportlist[it -> first].name != "\\N") {
                result.push_back(it -> first);
            }           
        }
    }
    return result;
}

int checkValid(int airportID) {
    bool invalid = true;
    std::vector<int> v;
    std::vector<std::string> input = file_to_vector("./data/input.dat");
    
    for (size_t i = 0; i < input.size()-1; ++i) {
        v.push_back(std::stoi(splitString(input[i])[1]));
        v.push_back(std::stoi(splitString(input[i])[2]));
    }

    while (invalid) {
        if (std::find(v.begin(), v.end(), airportID) != v.end()) {
            invalid = false;
        } else {
            std::cout << "Invalid Airport ID!" << '\n';
            std::cout << "Please input a valid Airport ID: " << '\n';
            std::cin >> airportID;
        }
    }

    return airportID;
}