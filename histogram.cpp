#include <iostream>
#include <string>
#include "Base structs\IDIctionary.h"
#include "HistogramAlgo.h"
#include <utility>
#include <fstream>
#include <regex>
#include "Tests.h"
#include "UI\UI.h"

std::vector<Person> CsvReader()
{
	std::ifstream fout;
	fout.open("Persons.csv");

	std::vector<Person> out;
	std::string helpingString;
	char c;
	std::getline(fout, helpingString);

	while (!fout.eof())
	{
		std::string name;
		std::size_t course;
		std::size_t age;
		float GPA;
		std::size_t PE;
		std::regex reg("[,]");
		std::getline(fout, helpingString, '\n');

		std::sregex_token_iterator iter(helpingString.begin(), helpingString.end(), reg, -1);
		std::sregex_token_iterator end;
		name = iter->str();
		iter++;
		course = std::stoi(iter->str());
		iter++;
		age = std::stoi(iter->str());
		iter++;
		GPA = std::stod(iter->str());
		iter++;
		PE = std::stoi(iter->str());
		if (name == "Жанна") 
			std::cout << "";
		out.push_back(Person(age, course, GPA, PE, name));
		if (fout.peek() == '\n')fout.get();
	}
	return out;
}
//интерфейс дикшнри, сам интерфейс, класс гистограмма, побольше тестов
int main()
{
	std::vector<Person> people = CsvReader();

	Range<float> minMaxInterval(5, 10);
	std::size_t partitionQuantity = 5;  

	IDictionary<Range<float>, std::vector<Person>> histogram = CreateHistogram(people, partitionQuantity, minMaxInterval, &(Person::GetGPA));

	VisualizeHistogram(histogram, partitionQuantity, minMaxInterval);


	/*IDictionaryTests tester;
	tester.RunTests();*/

	//UserInterface interf;
	//interf.ChooseStartAction();

}