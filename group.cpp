#include "constants.h"
#include <set>
#include <algorithm>

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

void assignCabins(std::vector<Person*> &input){
	int spacesFree{};
	for (int i = 0; i < boyCabins.size(); ++i)
	{
		spacesFree += spacesPerCabin[boyCabins[i]];
	}
	spacesFree = std::abs(spacesFree - (int)input.size());

	



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
	assignCabins(compOutput);
};