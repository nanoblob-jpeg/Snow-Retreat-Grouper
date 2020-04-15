#include "constants.h"
#include "setup.h"
#include "group.h"
#include <fstream>
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
	std::ofstream outf{"output.txt", std::ofstream::trunc};
	outf.close();

	int population{getNumberOfParticipants()};
	std::cin.ignore('\n', 10);

	//finding counselors per cabin
	std::map<std::string, int> counselorsPerCabin;
	getCounselor(counselorsPerCabin);

	//finding spaces left in each cabin
	setSpacesPerCabin(spacesPerCabin, counselorsPerCabin);

	std::cin.ignore('\n', 10);
	//creating list of the participants
	plist people;
	getList(people, population);

	plist girls, guys;
	for (int i = 0; i < population; ++i)
	{
		if(!people[i][2].compare("M"))
			guys.push_back(people[i]);
		else
			girls.push_back(people[i]);
	}
	std::cout <<"separated lists";
	//todo add error checking for the sizes of the girl and boy lists
	/*
	







	 */
	olist ogirls;
	createObjects(girls, ogirls);
	
	olist oguys;
	createObjects(guys, oguys);
	
	for (int i = 0; i < ogirls.size(); ++i)
	{
		std::cout << ogirls[i]<<"1)";
		if(ogirls[i]->one)
			std::cout << ogirls[i]->one;
		std::cout << "    2)";
		if(ogirls[i]->two)
			std::cout << ogirls[i]->two;
		std::cout << "    3)";
		if(ogirls[i]->three)
			std::cout << ogirls[i]->three;
		std::cout << '\n';
	}

	std::cout << "created objects";
	group(ogirls, girlCabins);
	group(oguys, boyCabins);

	std::cout << "ALL DONE";
	return 0;
}