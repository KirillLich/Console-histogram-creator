#include "UI.h"
#include "..\Tests\Tests.h"
#include <string>
#include <fstream>
#include <regex>

void UserInterface::PrintDialogMenu(const std::string dialogActions[], int n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << dialogActions[i] << std::endl;
	}
}

void UserInterface::ChooseStartAction() 
{
	const std::size_t numberOfActions = 4;
	const std::string dialogActions[] = { "1. Run tests", "2. Work with csv", "3. Exit" };
	bool exit = false;
	while (!exit)	
	{
		PrintDialogMenu(dialogActions, numberOfActions);
		switch (this->TakeItem<int>("Use numbers"))
		{
		case 1:
			IDictionaryTests tester;
			tester.RunTests();
			std::cout << "\n\tAll tests finished. No errors found.\n\n";
			break;
		case 2:
			//MakingHistogram(ReadCsvData("Persons.csv"));
			break;
		case 3:
			exit = true;
			break;
		default:
			std::cout << "Use number from 1 to 7\n";
			break;
		}
	}
}

std::vector<Person> UserInterface::ReadCsvData(const char* file)
{
	std::ifstream fout;
	fout.open(file);

	std::vector<Person> out;
	std::string helpingString;
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

		out.push_back(Person(age, course, GPA, PE, name));
		if (fout.peek() == '\n')fout.get();
	}
	fout.close();
	return out;
}