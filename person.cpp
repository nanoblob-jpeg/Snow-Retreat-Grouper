#include <string>
#include <memory>
#ifndef CPERSON
#define CPERSON

class Person{
public:
	int grade{};
	std::string name;
	std::shared_ptr<Person> one;
	std::shared_ptr<Person> two;
	std::shared_ptr<Person> three;

	Person(std::string iname, int igrade): grade{igrade}, name{iname}{
	}

	friend bool operator==(const Person &p1, const Person &p2){
		return (p1).name == (p2).name;
	}

	friend std::ostream& operator<<(std::ostream &out, std::shared_ptr<Person> person){
		out << person->name;
		return out;
	}
};
#endif