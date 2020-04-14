#include "constants.h"
#include <set>
#include <algorithm>

void group(olist &people,std::vector<std::string> &cabins){
	std::vector<std::set<Person*>> groups;
	while(people.size() > 0){
		std::set<Person*> temp;
		int index{};
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

	for (int i = 0; i < groups.size(); ++i)
	{
		//implement the second grouping operation here
	}
};