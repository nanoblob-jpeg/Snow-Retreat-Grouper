#include "constants.h"


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
	std::cout << "No spaces except first and last name please\n";
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

void getCounselor(std::map<std::string, int> &counselorsPerCabin){
	for (int i = 0; i < cabinNames.size(); ++i)
	{
		short num;
		std::cout << "How many counselors are going to be in " << cabinNames[i] << "?: ";
		std::cin >> num;
		while(std::cin.fail()){
			std::cin.clear();
			std::cin.ignore('\n', 10);
			std::cout << "How many counselors are going to be in " << cabinNames[i] << "?: ";
			std::cin >> num;
		}
		counselorsPerCabin[cabinNames[i]] = num;
	}

}

void setSpacesPerCabin(std::map<std::string, int> &spacesPerCabin, std::map<std::string, int> &counselorsPerCabin){
	for (int i = 0; i < spacesPerCabin.size(); ++i)
	{
		if(counselorsPerCabin[cabinNames[i]] > spacesPerCabin[cabinNames[i]]){
			std::cout << "\nError, negative number of spaces in cabin\n";
			exit(1);
		}
		else
			spacesPerCabin[cabinNames[i]] -= counselorsPerCabin[cabinNames[i]];
	}
}