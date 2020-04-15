#include "constants.h"
#include <set>
#include <algorithm>
#include "output.h"
#include <iterator>

std::vector<std::shared_ptr<Person>> compress(std::vector<std::vector<std::set<std::shared_ptr<Person>>>> &uncompOutput){
	//std::vector<std::vector<std::set<Person*>>> uncompOutput
	std::vector<std::shared_ptr<Person>> output;
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

int calculatescore(std::vector<int> &counter, std::vector<std::shared_ptr<Person>> &input, std::vector<std::string> &cabins){
	std::map<std::string, int> tempSpacesPerCabin = spacesPerCabin;
	//adjusting the sizes of the cabins
	for (int i = 0; i < counter.size(); ++i)
	{
		--tempSpacesPerCabin[cabins[counter[i]]];
	}
	int track{};
	int score{};
	for(int i{}; i < cabins.size(); ++i){
		std::vector<std::shared_ptr<Person>> temp(cabins[i].size());
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
			if(temp[i]->one){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[i]->one->name;
				}))
					score += 2;
			}
			if(temp[i]->two){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[i]->two->name;
				}))
					score += 2;
			}
			if(temp[i]->two){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[i]->three->name;
				}))
					score += 2;
			}
		}
	}
	return score;
}

void assignCabins(std::vector<std::shared_ptr<Person>> &input, std::vector<std::string> &cabins){
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
void print(std::set<std::shared_ptr<Person>> const &s)
{
    std::copy(s.begin(),
            s.end(),
            std::ostream_iterator<std::shared_ptr<Person>>(std::cout, " "));
}

void group(olist &people,std::vector<std::string> &cabins){
	std::vector<std::set<std::shared_ptr<Person>>> groups;
	int number{static_cast<int>(people.size())};
	while(people.size() > 0){
		std::set<std::shared_ptr<Person>> temp;
		temp.insert(people[0]);
		people.erase(people.begin());
		print(temp);
		for (auto itr = temp.begin(); itr != temp.end(); ++itr)
		{
			std::cout << *itr << " " << temp.size() << " " << groups.size() << "   " << people.size() << "   ";
			print(temp);
			std::cout << '\n';
			if((*itr)->one){
				temp.insert((*itr)->one);
				for (int j = 0; j < people.size(); ++j)
				{
					if((*itr)->one->name == people[j]->name){
						people.erase(people.begin() + j);
						break;
					}
				}
				// people.erase(std::find_if(people.begin(), people.end(), [&](std::shared_ptr<Person> p){
				// 	return p->name == (*it)->one->name;
				// }));
			}
			if((*itr)->two){
				temp.insert((*itr)->two);
				for (int j = 0; j < people.size(); ++j)
				{
					if((*itr)->two->name == people[j]->name){
						people.erase(people.begin() + j);
						break;
					}
				}
				// people.erase(std::find_if(people.begin(), people.end(), [&](std::shared_ptr<Person> p){
				// 	return p->name == (*it)->two->name;
				// }));
			}
			if((*itr)->three){
				temp.insert((*itr)->three);
				for (int j = 0; j < people.size(); ++j)
				{
					if((*itr)->three->name == people[j]->name){
						people.erase(people.begin() + j);
						break;
					}
				}
				// people.erase(std::find_if(people.begin(), people.end(), [&](std::shared_ptr<Person> p){
				// 	return p->name == (*it)->three->name;
				// }));
			}
		}

		groups.push_back(temp);
	}

	std::sort(groups.begin(), groups.end(), [](const std::set<std::shared_ptr<Person>> a, const std::set<std::shared_ptr<Person>> b){
		return (*a.begin())->grade > (*b.begin())->grade;
	});

	std::cout << "made it through first";
	std::vector<std::vector<std::set<std::shared_ptr<Person>>>> uncompOutput;
	for (int i = 0; i < groups.size(); ++i)
	{
		//implement the second grouping operation here
		//not done yet
		if(groups[i].size() <= 2){
			uncompOutput.push_back(std::vector<std::set<std::shared_ptr<Person>>>{groups[i]});
			continue;
		}
		std::vector<std::set<std::shared_ptr<Person>>> gofg;
		while(groups[i].size() > 0){
			std::set<std::shared_ptr<Person>> temp;
			temp.insert(*groups[i].begin());
			groups[i].erase(groups[i].begin());

			for (int i = 0; i < temp.size(); ++i)
			{
				auto it = temp.begin();
				std::advance(it, i);
				if((*it)->one){
					if((*it)->one->one){
						if((*it)->one->one->name == (*it)->name){
							temp.insert((*it)->one);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->one->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->one->name;
							// }));
						}
					}
					else if((*it)->one->two){
						if((*it)->one->two->name == (*it)->name){
							temp.insert((*it)->one);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->one->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->one->name;
							// }));
						}
					}
					else if((*it)->one->three){
						if((*it)->one->three->name == (*it)->name){
							temp.insert((*it)->one);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->one->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->one->name;
							// }));
						}
					}
				}
				if((*it)->two){
					if((*it)->two->one){
						if((*it)->two->one->name == (*it)->name){
							temp.insert((*it)->two);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->two->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->two->name;
							// }));
						}
					}
					else if((*it)->two->two){
						if((*it)->two->two->name == (*it)->name){
							temp.insert((*it)->two);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->two->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->two->name;
							// }));
						}
					}
					else if((*it)->two->three){
						if((*it)->two->three->name == (*it)->name){
							temp.insert((*it)->two);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->two->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->two->name;
							// }));
						}
					}
				}
				if((*it)->three){
					if((*it)->three->one){
						if((*it)->three->one->name == (*it)->name){
							temp.insert((*it)->three);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->three->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->three->name;
							// }));
						}
					}
					else if((*it)->three->two){
						if((*it)->three->two->name == (*it)->name){
							temp.insert((*it)->three);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->three->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->three->name;
							// }));
						}
					}
					else if((*it)->three->three){
						if((*it)->three->three->name == (*it)->name){
							temp.insert((*it)->three);
							for (int j = 0; j < groups[i].size(); ++j)
							{	
								auto iter = groups[i].begin();
								std::advance(iter, j);
								if((*it)->three->name == (*iter)->name){
									groups[i].erase(iter);
								}
							}
							// groups[i].erase(std::find_if(groups[i].begin(), groups[i].end(), [&](std::shared_ptr<Person> p){
							// 	return p->name == (*it)->three->name;
							// }));
						}
					}
				}
			}
			gofg.push_back(temp);
		}
		uncompOutput.push_back(gofg);
	}
	std::cout << "made it through second";
	std::cout << "\n\n\n\n\n\n";
	for(int i{}; i < uncompOutput.size(); ++i){
		for(int j{}; j < uncompOutput[i].size(); ++j){
			for(int k{}; k < uncompOutput[i][j].size(); ++k){
				auto it = uncompOutput[i][j].begin();
				std::advance(it, k);
				std::cout << (*it)->name;
			}
		}
	}


	std::vector<std::shared_ptr<Person>> compOutput{compress(uncompOutput)};
	assignCabins(compOutput, cabins);
};