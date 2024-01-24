#pragma once
#include "HashTable.h"
#include <stdexcept>

template<typename TKey, typename TElement, typename Hash = std::hash<TKey>>
class IDictionary
{
private:
	HashTable<TKey, TElement, Hash> container;
	friend IDictionary;
public:
	IDictionary(const IDictionary& list) :container(list.container){};
	IDictionary() :container(1) {};

	int Count()
	{
		return container.Count();
	}
	int GetCapacity()
	{
		return container.GetCapacity();
	}

	TElement& Get(TKey key)
	{
		if (container.ContainsKey(key))
			return container.Get(key);
		else
			throw std::runtime_error("No suitable element for key");
	}

	bool ContainsKey(TKey key)
	{
		return container.ContainsKey(key);
	}

	void Add(TKey key, TElement element)
	{
		if (!container.ContainsKey(key))
			container.Add(key, element);
		else
			throw std::runtime_error("Key is already in use");
	}

	void Remove(TKey key)
	{
		if (container.ContainsKey(key))
			container.Remove(key);
		else
			throw std::runtime_error("No suitable element for key");
	}
};