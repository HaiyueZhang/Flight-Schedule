#include "Airport.h"
#include "readFile.h"

//avoid multiple definition of `distances' in Airport.o
int distances[AirportNum][AirportNum];

//avoid multiple definition of `airportlist' in Airport.o
Airport airportlist[AirportNum];

//avoid multiple definition of `airportmap' in Airport.o
map<int, Airport> airportmap;

void initializeAirportData() {
    vector<string> airportsData;
    airportsData = file_to_vector("./data/airports.dat");
    for (size_t i = 0; i < airportsData.size(); i++) {
        vector<string> result = splitString(airportsData[i]);
        Airport ap;
        ap.numid = stoi(result[0]);
        ap.name = result[4];
        ap.x = stod(result[6]);
        ap.y = stod(result[7]);
        airportlist[ap.numid - 1] = ap;
        airportmap[ap.numid] = ap;
    }
}

void initializeDistanceData() {
    for (size_t i = 0; i < AirportNum; i++) {
        for (size_t j = 0; j < AirportNum; j++) {
            distances[i][j] = INT32_MAX;
        }
    }
    vector<string> routesData;
    routesData = file_to_vector("./data/input_detail.dat");
    for (size_t i = 0; i < 60000 && i < routesData.size(); i++) {
        vector<string> result = splitString(routesData[i]);
        distances[stoi(result[3]) - 1][stoi(result[5]) - 1] = stod(result[19]);
    }
}

void initializeRestDistanceData() {
    vector<string> routesData;
    routesData = file_to_vector("./data/input_detail.dat");
    for (size_t i = 60000; i < routesData.size(); i++) {
        vector<string> result = splitString(routesData[i]);
        //distances[departure airportID][destination airportID] = distances
        distances[stoi(result[3]) - 1][stoi(result[5]) - 1] = stod(result[19]);
    }
}

void Dijkstra(int airportID, int * dis, int * path, bool * visited) {
    int v0 = airportID;
    //cout << distances[1][2] << "!!!!!!!!" << endl;
    for (int i = 0; i < AirportNum; i++) {
        dis[i] = distances[v0][i];
        visited[i] = 0;
        //shortest path initialization 
        path[i] = -1;
    }
    visited[v0] = true;
    for (int i = 0; i < AirportNum; i++) {
        int p, minn = INT32_MAX;
        for (int j = 0; j < AirportNum; j++) {
            if (!visited[j] && dis[j] != INT32_MAX && dis[j] < minn ) {
                p = j;
                minn = dis[j];
            }
        }
        visited[p] = true;
        for (int j = 0; j < AirportNum; j++) {
            if (!visited[j] && distances[p][j] != INT32_MAX && dis[p] + distances[p][j] < dis[j]) {
                dis[j] = dis[p] + distances[p][j];
                //the node p visited on shortest path between i and j
                path[j] = p;
            }
        }
    }
    return;
}


// DELTA STEPPING ALGORITHM BEGINS

void relax(int w, int x, int delta, int * tent, map<int, unordered_set<int>> &B) {
    if (x < tent[w]) {
        B[tent[w] / delta].erase(w);
        B[x / delta].insert(w);
        tent[w] = x;
    }
}

vector<pair<int, int>> findRequestsLight(unordered_set<int> V, int delta, int * tent) {
    vector<pair<int, int>> ret;
    for (int v : V) {
        for (int w = 0; w < AirportNum; w++) {
            if (distances[v][w] <= delta) {
                ret.push_back({w, tent[v] + distances[v][w]});
            }
        }
    }
    return ret;
}

vector<pair<int, int>> findRequestsHeavy(unordered_set<int> V, int delta, int * tent) {
    vector<pair<int, int>> ret;
    for (int v : V) {
        for (int w = 0; w < AirportNum; w++) {
            if (distances[v][w] < INT32_MAX && distances[v][w] > delta) {
                ret.push_back({w, tent[v] + distances[v][w]});
            }
        }
    }
    return ret;
}

inline void relaxRequests(vector<pair<int, int>> Req, int delta, int * tent, map<int, unordered_set<int>> &B) {
    for (auto r : Req) {
        relax(r.first, r.second, delta, tent, B);
    }
}

int firstNonEmpty(map<int, unordered_set<int>> &B) {
    for (auto b : B) {
        if (!b.second.empty()) {
            return b.first;
        }
    }
    return -1;
}

void DeltaStepping(int airportID, int delta, int * tent, map<int, unordered_set<int>> &B) {  // must be ordered map
    std::fill(tent, tent + AirportNum, INT32_MAX);
    relax(airportID, 0, delta, tent, B);
    int i;
    unordered_set<int> R;
    vector<pair<int, int>> Req;
    while ((i = firstNonEmpty(B)) != -1) {
        R.clear();
        while (!B[i].empty()) {
            Req = findRequestsLight(B[i], delta, tent);
            for (int b : B[i]) {
                R.insert(b);
            }
            B[i].clear();
            relaxRequests(Req, delta, tent, B);
        }
        Req = findRequestsHeavy(R, delta, tent);
        relaxRequests(Req, delta, tent, B);
    }
}
