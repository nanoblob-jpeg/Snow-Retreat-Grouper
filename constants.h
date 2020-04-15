#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "person.cpp"

#ifndef CONSTANTS
#define CONSTANTS
using plist = std::vector<std::vector<std::string>>;
using p = std::vector<std::string>;
using olist = std::vector<std::shared_ptr<Person>>;

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

//biases for grades per cabin, vector includes 12,11,10,9,8,7,6
inline std::map<std::string, std::vector<int>> bias{
		{"Tanager", {20,10,1,0,0,-50,-50}},
		{"Woodpecker", {18,8,0,0,0,-50,-50}},
		{"Calliope", {20,10,1,0,0,-50,-50}},
		{"Stellar Jay", {18,8,0,0,0,-50,-50}},
		{"Cabin 3", {8,7,5,4,0,0,0}},
		{"Cabin 4", {-5,-3,2,3,6,10,10}},
		{"Cabin 5", {-5,-3,2,3,6,6,6}},
		{"Cabin 6", {-5,-3,2,3,6,6,6}},
		{"Cabin 7", {8,7,5,4,0,0,0}},
		{"Cabin 8", {8,7,5,4,0,0,0}},
		{"Cabin 11", {-5,-3,2,3,6,6,6}},
		{"Cabin 12", {-5,-3,2,3,6,6,6}},
		{"Cabin 13", {-5,-3,2,3,6,10,10}}
};

//cabinname, vector of people's name
inline std::map<std::string, std::vector<std::string>> output;
#endif