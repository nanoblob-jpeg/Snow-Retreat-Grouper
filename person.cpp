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

	friend bool operator==(const Person &p1, const Person &p2){
		return (p1).name == (p2).name;
	}

	friend std::ostream& operator<<(std::ostream &out, Person *person){
		out << person->name;
		return out;
	}
};
#endif