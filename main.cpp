#include <iostream>
#include <vector>
#include "src/readFile.h"
#include "src/interaction.h"
#include "src/Airport.h"

int main() {
	std::cout << "CS225 Final Project OpenFlights is starting... \n";
	initializeAirportData();
	std::cout << "Airport Data is loading... \n";
	initializeDistanceData();
	std::cout << "Distance Data is loading... \n";
	initializeRestDistanceData();
	std::cout << "Almost done... \n";
	userOption();
	return 0;
}
