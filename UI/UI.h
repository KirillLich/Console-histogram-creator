#ifndef UI_H
#define UI_H

#include "..\HistogramAlgo.h"
#include "..\Base structs\IDIctionary.h"
#include <iostream>
#include "..\Person.h"

class UserInterface
{
	template<typename T>
	T TakeItem(std::string errorMessage) 
	{
		T out;
		std::cin >> out;
		if (!std::cin.good() || (std::cin.peek() != '\n'))
		{
			std::cin.clear();

			std::cout << errorMessage << '\n';
			while (std::cin.get() != '\n') {}
			out = this->TakeItem<T>(errorMessage);
		}
		return out;
	}

	void PrintDialogMenu(const std::string dialogActions[], int n);
	
	std::vector<Person> ReadCsvData(const char* file);

	template <typename TAttribute>
	void MakingHistogram(std::vector<Person> people)
	{
		std::vector<Person> people = ReadCsvData();

		std::cout << "Choose attribute for histograam\n";
		TAttribute(Person:: * func)() = this->ChooseAttribute();

		if (func == Person::GetCourse)
		{
			return;
		}

		std::cout << "Write attribute range\n";
		Range<TAttribute> range(TakeItem<TAttribute>("Wrong type"), TakeItem<TAttribute>("Wrong type"));

		std::cout << "Write partition quantity range\n";
		std::size_t partition = TakeItem<std::size_t>("Wrong type");

		IDictionary<Range<std::size_t>, std::vector<Person>> histogram = CreateHistogram(people, partition, range, func);

		VisualizeHistogram(histogram, partition, range);
	}

	template <typename TAttribute>
	TAttribute (Person::*ChooseAttribute())()
	{
		const std::size_t numberOfActions = 4;
		const std::string dialogActions[] = { "1. Age", "2. Course", "3. GPA", "4. PE attestation"};
		while (!exit)
		{
			PrintDialogMenu(dialogActions, numberOfActions);
			switch (this->TakeItem<int>("Use numbers"))
			{
			case 1:
				return &(Person::GetAge);
				break;
			case 2:
				return &(Person::GetCourse);
				break;
			case 3:
				return &(Person::GetGPA);
				break;
			case 4:
				return &(Person::GetPEAttestation);
				break;
			default:
				std::cout << "Use number from 1 to 4\n";
				break;
			}
		}
	}
	
public:
	UserInterface() = default;

	void ChooseStartAction();
};

#endif