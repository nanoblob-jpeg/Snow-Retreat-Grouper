#include <string>

#ifndef CPERSON
#define CPERSON

class Person{
public:
	int grade{};
	std::string name;
	Person *one;
	Person *two;
	Person *three;

	Person(std::string iname, int igrade): grade{igrade}, name{iname}{
		one = nullptr;
		two = nullptr;
		three = nullptr;
	}
};
#endif