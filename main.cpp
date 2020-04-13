#include <iostream>
#include <vector>
#include <string>
/*
BOYS
============
Tanager - 9
Woodpecker - 9
Cabin 3 - 8
Cabin  7 - 8
Cabin 5 - 8
Cabin 6 - 8
Cabin 4 - 6

GIRLS
============
Stellar Jay - 8
Calliope - 9
Cabin  8 - 8
Cabin 11 - 10
Cabin 12 - 10
Cabin 13 - 10
 */

using plist = std::vector<std::vector<std::string>>;
using p = std::vector<std::string>;

int getNumberOfParticipants(){
	int i{};
	while(i <= 0 || std::cin.fail()){
		std::cout << "Please indicate the number of participants: ";
		std::cin >> i;
	}
	return i;
}

void getList(plist &people, int population){
	std::cout << "Please copy and paste a list of of the participants, an example list is provided below\n";
	std::cout << "No spaces please\n";
	std::cout << "Format: FirstName LastName, GradeLevel, Gender(M/F), FirstRequenst, SecondRequest, ThirdRequest, first time(Y/N)\n";
	std::cout << "Jason Chang,10,M,John Lu,Jacob Zhang,Daniel Xu,N\n";
	std::cout << "Lucy Jin,12,F,Claire Wong,Caroline Li,Amy Bing,Y\n";
	for (int i{}; i < population; ++i)
	{
		int oldIndex{0};
		std::string buffer;
		std::getline(std::cin, buffer);
		std::cin;
		p temp(7);
		for (int j = 0; j < 7; ++j)
		{
			int index{static_cast<int>(buffer.find(',', oldIndex))};
			temp[j] = buffer.substr(oldIndex, index - oldIndex);
			oldIndex = index + 1;
		}
		people.push_back(temp);
	}
}


int main(){
	int population{getNumberOfParticipants()};
	std::cin.ignore('\n', 10);
	plist people;
	getList(people, population);

	return 0;
}