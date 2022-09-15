#pragma once
#include <string>
#include <vector>

// file to string
std::string file_to_string(const std::string & filename);

// file to vector
std::vector<std::string> file_to_vector(const std::string& filename);

// display data
void display_data (const std::string& filename);

// split string in dataset
std::vector<std::string> splitString(std::string str);
