#pragma once
#include "Base structs\IDIctionary.h"
#include <assert.h>


class IDictionaryTests //tests
{
	void TestEmpty()
	{
		IDictionary<int, char> dict;
		try
		{
			dict.Get(5);
		}
		catch (const std::exception& e) 
		{
			std::string errorName = e.what();
			assert(errorName == "No suitable element for key");
		};
	}

	void TestGet()
	{
		IDictionary<int, char> dict;
		dict.Add(1, 'r');
		dict.Add(5, 'p');
		assert(dict.Get(5) == 'p');
	}

	void TestRemove()
	{
		IDictionary<int, char> dict;
		dict.Add(1, 'r');
		dict.Add(5, 'p');
		dict.Remove(1);
		try
		{
			dict.Get(1);
		}
		catch (const std::exception& e)
		{
			std::string errorName = e.what();
			assert(errorName == "No suitable element for key");
		};
	}

	void Count()
	{
		IDictionary<int, char> dict;
		dict.Add(1, 'r');
		dict.Add(5, 'p');
		dict.Add(18, 'o');
		assert(dict.Count() == 3);
	}

public:
	void RunTests()
	{
		this->TestEmpty();
		this->TestGet();
		this->Count();
		this->TestRemove();
	};
	IDictionaryTests() = default;
};