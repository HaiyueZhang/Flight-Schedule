#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "readFile.h"

std::string file_to_string(const std::string& filename) {
    std::ifstream text(filename);
    
    std::stringstream strStream;
    if (text.is_open()) {
        strStream << text.rdbuf();
    }

    return strStream.str();
}

std::vector<std::string> file_to_vector(const std::string& filename) {
    std::ifstream text(filename);
    std::vector<std::string> out;

    if (text.is_open()) {
		std::string temp;
        while (!text.eof()) {
			getline(text, temp);
			out.push_back(temp);
        }
		text.close();
    }

    return out;
} 

void display_data (const std::string& filename) {
    unsigned int maxRow {10};
    std::vector<std::string> fileVector = file_to_vector(filename);
    if (maxRow > fileVector.size()) {
        for (auto row : fileVector) {
            std::cout << row << '\n';
        }
    } else {
        for (unsigned int i = 0; i < maxRow; ++i) {
            std::cout << fileVector[i] << '\n';
        }
    }
}

std::vector<std::string> splitString(std::string str) {
    std::vector<std::string> result;
    std::string temp;
    size_t start = 0;
    size_t end = 0;
    bool isValid = true;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '\"') {
            isValid = !isValid;
        }
        if (str[i] == ',' && isValid) {
            end = i;
            temp = str.substr(start, end - start);
            result.push_back(temp);
            start = end + 1;
            end = start;
        }
    }
    temp = str.substr(start, str.length() - start);
    result.push_back(temp);
    return result;
}