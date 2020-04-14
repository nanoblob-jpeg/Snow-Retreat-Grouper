#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "person.cpp"

#ifndef CONSTANTS
#define CONSTANTS
using plist = std::vector<std::vector<std::string>>;
using p = std::vector<std::string>;
using olist = std::vector<Person*>;

inline std::vector<std::string> cabinNames{"Tanager", "Woodpecker", "Calliope", "Stellar Jay", "Cabin 3", "Cabin 4", "Cabin 5", "Cabin 6", "Cabin 7", "Cabin 8", "Cabin 11", "Cabin 12", "Cabin 13"};
inline std::vector<std::string> girlCabins{"Calliope", "Stellar Jay", "Cabin 8", "Cabin 11", "Cabin 12", "Cabin 13"};
inline std::vector<std::string> boyCabins{"Tanager", "Woodpecker", "Cabin 3", "Cabin 4", "Cabin 5", "Cabin 6", "Cabin 7"};

inline std::map<std::string, int> spacesPerCabin{
		{"Tanager", 9},
		{"Woodpecker", 9},
		{"Calliope", 9},
		{"Stellar Jay", 8},
		{"Cabin 3", 8},
		{"Cabin 4", 6},
		{"Cabin 5", 8},
		{"Cabin 6", 8},
		{"Cabin 7", 8},
		{"Cabin 8", 8},
		{"Cabin 11", 10},
		{"Cabin 12", 10},
		{"Cabin 13", 10}
};

//cabinname, vector of people's name
inline std::map<std::string, std::vector<std::string>> output;
#endif