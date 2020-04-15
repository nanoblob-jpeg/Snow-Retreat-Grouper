#include "constants.h"
#include <fstream>

void writeFile(std::vector<std::shared_ptr<Person>> &input, std::vector<std::string> &cabins,std::vector<int> &maxVec){

	std::ofstream outf{"output.txt", std::ofstream::app};
	std::map<std::string, int> tempSpacesPerCabin = spacesPerCabin;
	//adjusting the sizes of the cabins
	for (int i = 0; i < maxVec.size(); ++i)
	{
		--tempSpacesPerCabin[cabins[maxVec[i]]];
	}

	int track{};
	for (int i = 0; i < cabins.size(); ++i)
	{
		outf << cabins[i] << ": ";
		for (int j = 0; j < tempSpacesPerCabin[cabins[i]]; ++j)
		{
			outf << input[track] << ", ";
			++track;
		}
		outf << '\n';
	}
	outf.close();
};
