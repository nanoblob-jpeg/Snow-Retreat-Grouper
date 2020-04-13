#include "setup.h"
#include "constants.h"
#include "group.h"
#include "output.h"
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



int main(){
	int population{getNumberOfParticipants()};
	std::cin.ignore('\n', 10);

	//finding counselors per cabin
	std::map<std::string, int> counselorsPerCabin;
	getCounselor(counselorsPerCabin);

	//finding spaces left in each cabin
	setSpacesPerCabin(spacesPerCabin, counselorsPerCabin);

	//creating list of the participants
	plist people;
	getList(people, population);


	plist girls, guys;
	for (int i = 0; i < people.size(); ++i)
	{
		if(!people[i][2].compare("M"))
			guys.push_back(people[i]);
		else
			girls.push_back(people[i]);
	}

	group(girls, girlCabins);
	group(guys, boyCabins);

	writeFile();

	return 0;
}