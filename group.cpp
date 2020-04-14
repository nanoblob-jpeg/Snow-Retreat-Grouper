#include "constants.h"
#include <set>
#include <algorithm>
#include "output.h"

std::vector<Person*> compress(std::vector<std::vector<std::set<Person*>>> &uncompOutput){
	//std::vector<std::vector<std::set<Person*>>> uncompOutput
	std::vector<Person*> output;
	for(int i{}; i < uncompOutput.size(); ++i){
		for(int j{}; j < uncompOutput[i].size(); ++j){
			for(int k{}; k < uncompOutput[i][j].size(); ++k){
				auto it = uncompOutput[i][j].begin();
				std::advance(it, k);
				output.push_back(*it);
			}
		}
	}
	return output;
}

int calculatescore(std::vector<int> &counter, std::vector<Person*> &input, std::vector<std::string> &cabins){
	std::map<std::string, int> tempSpacesPerCabin = spacesPerCabin;
	//adjusting the sizes of the cabins
	for (int i = 0; i < counter.size(); ++i)
	{
		--tempSpacesPerCabin[cabins[counter[i]]];
	}
	int track{};
	int score{};
	for(int i{}; i < cabins.size(); ++i){
		std::vector<Person*> temp(cabins[i].size());
		//adding people to the cabins
		for(int j{}; j < tempSpacesPerCabin[cabins[i]]; ++j){
			temp.push_back(input[track]);
			++track;
		}

		//adding to score with biases for grade levels
		for (int i = 0; i < temp.size(); ++i)
		{
			score += bias[cabins[i]][12-temp[i]->grade];
		}

		//adding to score with number of connections within cabin
		for (int i = 0; i < temp.size(); ++i)
		{
			if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](Person *p){
				return p->name == temp[i]->one->name;
			}))
				score += 2;
			if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](Person *p){
				return p->name == temp[i]->two->name;
			}))
				score += 2;
			if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](Person *p){
				return p->name == temp[i]->three->name;
			}))
				score += 2;
		}
	}
	return score;
}

void assignCabins(std::vector<Person*> &input, std::vector<std::string> &cabins){
	int spacesFree{};
	int max{};
	for (int i = 0; i < cabins.size(); ++i)
	{
		spacesFree += spacesPerCabin[cabins[i]];
	}
	spacesFree = std::abs(spacesFree - (int)input.size());

	std::vector<int> counter(spacesFree);
	std::vector<int> maxVec(spacesFree);
	while(spacesFree > 0 && counter[0] != cabins.size() - 1){
		for (int i = 0; i < counter.size(); ++i)
		{
			if(counter[counter.size() - 1 - i] == cabins.size() - 1){
				++counter[counter.size() - i-2];
				counter[counter.size() - 1 - i] = counter[counter.size() - i-2];
			} else{
				++counter[counter.size() - 1];
			}
		}

		if(max < calculatescore(counter, input, cabins)){
			for (int i = 0; i < counter.size(); ++i)
			{
				maxVec[i] = counter[i];
			}
		};
	}

	writeFile(input, cabins, maxVec);
}

void group(olist &people,std::vector<std::string> &cabins){
	std::vector<std::set<Person*>> groups;
	int number{static_cast<int>(people.size())};
	while(people.size() > 0){
		std::set<Person*> temp;
		temp.insert(people[0]);
		people.erase(people.begin());

		for (int i = 0; i < temp.size(); ++i)
		{
			auto it = temp.begin();
			std::advance(it, i);
			temp.insert((*it)->one);
			people.erase(std::find_if(people.begin(), people.end(), [&](Person *p){
				return p->name == (*it)->one->name;
			}));
			temp.insert((*it)->two);
			people.erase(std::find_if(people.begin(), people.end(), [&](Person *p){
				return p->name == (*it)->two->name;
			}));
			temp.insert((*it)->three);
			people.erase(std::find_if(people.begin(), people.end(), [&](Person *p){
				return p->name == (*it)->three->name;
			}));
		}

		groups.push_back(temp);
	}

	std::sort(groups.begin(), groups.end(), [](const std::set<Person*> a, const std::set<Person*> b){
		return (*a.begin())->grade > (*b.begin())->grade;
	});

	std::vector<std::vector<std::set<Person*>>> uncompOutput;
	for (int i = 0; i < groups.size(); ++i)
	{
		//implement the second grouping operation here
		//not done yet
		if(groups[i].size() <= 2)
			continue;
		std::vector<std::set<Person*>> gofg;
		while(groups[i].size() > 0){
			std::set<Person*> temp;
			temp.insert(*groups[i].begin());
			groups[i].erase(groups[i].begin());

			for (int i = 0; i < temp.size(); ++i)
			{
				auto it = temp.begin();
				std::advance(it, i);

				if((*it)->one->one->name == (*it)->name || (*it)->one->three->name == (*it)->name ||(*it)->one->two->name == (*it)->name){
					temp.insert((*it)->one);
					groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](Person *p){
						return p->name == (*it)->one->name;
					}));
				}
				if((*it)->two->one->name == (*it)->name || (*it)->two->three->name == (*it)->name ||(*it)->two->two->name == (*it)->name){
					temp.insert((*it)->two);
					groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](Person *p){
						return p->name == (*it)->two->name;
					}));
				}
				if((*it)->three->one->name == (*it)->name || (*it)->three->three->name == (*it)->name ||(*it)->three->two->name == (*it)->name){
					temp.insert((*it)->three);
					groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](Person *p){
						return p->name == (*it)->three->name;
					}));
				}
			}
			gofg.push_back(temp);
		}
		uncompOutput.push_back(gofg);
	}

	std::vector<Person*> compOutput{compress(uncompOutput)};
	assignCabins(compOutput, cabins);
};