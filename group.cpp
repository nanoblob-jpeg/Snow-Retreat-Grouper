#include "constants.h"
#include <set>
#include <algorithm>
#include "output.h"
#include <iterator>

static int ccc{};

std::vector<std::shared_ptr<Person>> compress(std::vector<std::vector<std::vector<std::shared_ptr<Person>>>> &uncompOutput){
	//std::vector<std::vector<std::set<Person*>>> uncompOutput
	std::vector<std::shared_ptr<Person>> output;
	for(int i{}; i < uncompOutput.size(); ++i){
		for(int j{}; j < uncompOutput[i].size(); ++j){
			for(int k{}; k < uncompOutput[i][j].size(); ++k){
				output.push_back(uncompOutput[i][j][k]);
			}
		}
	}
	return output;
}

int calculatescore(std::vector<int> &counter, std::vector<std::shared_ptr<Person>> &input, std::vector<std::string> &cabins){
	++ccc;
	std::map<std::string, int> tempSpacesPerCabin = spacesPerCabin;
	//adjusting the sizes of the cabins
	for (int i = 0; i < counter.size(); ++i)
	{
		--tempSpacesPerCabin[cabins[counter[i]]];
	}
	int track{};
	int score{};
	for(int i{}; i < cabins.size(); ++i){
		std::vector<std::shared_ptr<Person>> temp;
		//adding people to the cabins
		for(int j{}; j < tempSpacesPerCabin[cabins[i]]; ++j){
			temp.push_back(input[track]);
			++track;
		}

		//adding to score with biases for grade levels
		for (int j = 0; j < temp.size(); ++j)
		{
			int a{temp[j]->grade};
			score += bias[cabins[i]][12-a];
		}
		//adding to score with number of connections within cabin
		for (int j = 0; j < temp.size(); ++j)
		{
			if(temp[j]->one){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[j]->one->name;
				}))
					score += 2;
			}
			if(temp[j]->two){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[j]->two->name;
				}))
					score += 2;
			}
			if(temp[j]->three){
				if(temp.end() != std::find_if(temp.begin(), temp.end(), [&](std::shared_ptr<Person> p){
					return p->name == temp[j]->three->name;
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
		if(ccc % 1000 == 0){
			std::cout << ccc << " trials have been done. Please wait while we optimize\n";
		}
		++counter[counter.size()-1];
		for (int i = 0; i < counter.size(); ++i)
		{
			if(counter[counter.size() - 1 - i] == cabins.size()){
				++counter[counter.size() - i-2];
				counter[counter.size() - 1 - i] = 0;
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
void print(std::vector<std::shared_ptr<Person>> const &s)
{
    std::copy(s.begin(),
            s.end(),
            std::ostream_iterator<std::shared_ptr<Person>>(std::cout, " "));
}

bool insertIfUnique(std::vector<std::shared_ptr<Person>>& vector, std::shared_ptr<Person> const& newValue){
	if(std::find(vector.begin(), vector.end(), newValue) == vector.end()){
		vector.push_back(newValue);
		return true;
	}
	return false;
}

void group(olist &people,std::vector<std::string> &cabins){
	std::vector<std::vector<std::shared_ptr<Person>>> groups;
	int number{static_cast<int>(people.size())};
	while(people.size() > 0){
		std::vector<std::shared_ptr<Person>> temp;
		temp.push_back(people[0]);
		people.erase(people.begin());
		
		for (int i = 0; i < temp.size(); ++i)
		{
			if(temp[i]->one){
				if(std::find(people.begin(), people.end(), temp[i]->one) != people.end()){
					if(insertIfUnique(temp, temp[i]->one)){
						for (int j = 0; j < people.size(); ++j)
						{
							if(temp[i]->one->name == people[j]->name){
								people.erase(people.begin() + j);
								break;
							}
						}
					}
				}
			}
			if(temp[i]->two){
				if(std::find(people.begin(), people.end(), temp[i]->two) != people.end()){
					if(insertIfUnique(temp, temp[i]->two)){
						for (int j = 0; j < people.size(); ++j)
						{
							if(temp[i]->two->name == people[j]->name){
								people.erase(people.begin() + j);
								break;
							}
						}
					}
				}
			}
			if(temp[i]->three){
				if(std::find(people.begin(), people.end(), temp[i]->three) != people.end()){
					if(insertIfUnique(temp, temp[i]->three)){
						for (int j = 0; j < people.size(); ++j)
						{
							if(temp[i]->three->name == people[j]->name){
								people.erase(people.begin() + j);
								break;
							}
						}
					}
				}
			}
		}
		groups.push_back(temp);
	}

	std::sort(groups.begin(), groups.end(), [](const std::vector<std::shared_ptr<Person>> a, const std::vector<std::shared_ptr<Person>> b){
		return (*a.begin())->grade > (*b.begin())->grade;
	});

	std::vector<std::vector<std::vector<std::shared_ptr<Person>>>> uncompOutput;
	for (int i = 0; i < groups.size(); ++i)
	{
		//implement the second grouping operation here
		//not done yet
		if(groups[i].size() <= 2){
			uncompOutput.push_back(std::vector<std::vector<std::shared_ptr<Person>>>{groups[i]});
			continue;
		}
		std::vector<std::vector<std::shared_ptr<Person>>> gofg;
		while(groups[i].size() > 0){
			std::vector<std::shared_ptr<Person>> temp;
			temp.push_back(*groups[i].begin());
			groups[i].erase(groups[i].begin());

			for (int i = 0; i < temp.size(); ++i)
			{
				if(temp[i]->one){
					if(temp[i]->one->one){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->one) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->one)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->one->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->one->two){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->one) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->one)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->one->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->one->three){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->one) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->one)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->one->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
				}
				if(temp[i]->two){
					if(temp[i]->two->one){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->two) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->two)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->two->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->two->two){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->two) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->two)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->two->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->two->three){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->two) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->two)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->two->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
				}
				if(temp[i]->three){
					if(temp[i]->three->one){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->three) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->three)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->three->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->three->two){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->three) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->three)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->three->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
					else if(temp[i]->three->three){
						if(std::find(groups[i].begin(), groups[i].end(), temp[i]->three) != groups[i].end()){
							if(insertIfUnique(temp, temp[i]->three)){
								for (int j = 0; j < groups[i].size(); ++j)
								{	
									if(temp[i]->three->name == groups[i][j]->name){
										groups[i].erase(groups[i].begin() + j);
									}
								}
							}
						}
					}
				}
			}
			gofg.push_back(temp);
		}
		std::sort(gofg.begin(), gofg.end(), [](const std::vector<std::shared_ptr<Person>> a, const std::vector<std::shared_ptr<Person>> b){
				return (*a.begin())->grade > (*b.begin())->grade;
			});
		uncompOutput.push_back(gofg);
	}

	std::vector<std::shared_ptr<Person>> compOutput{compress(uncompOutput)};
	assignCabins(compOutput, cabins);
};