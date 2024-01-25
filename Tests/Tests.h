#pragma once
#include "..\Base structs\Dictionary.h"
#include <assert.h>


class DictionaryTests //tests
{
	void TestEmpty()
	{
		IDictionary<int, char>* dict = MakeDictionary<int,char>();
		try
		{
			dict->Get(5);
		}
		catch (const std::exception& e) 
		{
			std::string errorName = e.what();
			assert(errorName == "No suitable element for key");
		};
	}

	void TestContainsKey()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		dict->Add(-7, 'r');
		assert(dict->ContainsKey(-7));
		assert(!dict->ContainsKey(13));
	}

	void TestAdd()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		assert(dict->ContainsKey(-7));
		dict->Add(-7, 'r');
		assert(dict->ContainsKey(-7));
	}

	void TestGetCount()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		dict->Add(1, 'r');
		dict->Add(5, 'p');
		dict->Add(18, 'o');
		assert(dict->GetCount() == 3);
	}

	void TestGetCapacity()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		dict->Add(1, 'r');
		dict->Add(5, 'p');
		dict->Add(18, 'o');
		assert(dict->GetCapacity() == 4);
		dict->Add(4, 'n');
		assert(dict->GetCapacity() == 8);
	}

	void TestGet()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		dict->Add(1, 'r');
		dict->Add(5, 'p');
		assert(dict->Get(5) == 'p');
	}


	void TestRemove()
	{
		IDictionary<int, char>* dict = MakeDictionary<int, char>();
		dict->Add(1, 'r');
		dict->Add(5, 'p');
		dict->Remove(1);
		try
		{
			dict->Get(1);
		}
		catch (const std::exception& e)
		{
			std::string errorName = e.what();
			assert(errorName == "No suitable element for key");
		};
	}


public:
	void RunTests()
	{
		this->TestEmpty();
		this->TestGet();
		this->TestGetCount();
		this->TestRemove();
	};
	DictionaryTests() = default;
};