#pragma once
#include "HashTable.h"
#include "IDictionary.h"
#include <stdexcept>

template<typename TKey, typename TElement, typename Hash = std::hash<TKey>>
class Dictionary:public IDictionary <TKey, TElement>
{
private:
	HashTable<TKey, TElement, Hash> container;
	friend Dictionary;

	template <typename IKey, typename IElement>
	friend IDictionary<IKey, IElement>* MakeDictionary();
	template <typename IKey, typename IElement>
	friend IDictionary<IKey, IElement>* MakeDictionary(IDictionary<IKey, IElement>* DictionaryCopy);

	Dictionary(const Dictionary& list) :container(list.container){};
	Dictionary() :container(1) {};
public:

	std::size_t GetCount()
	{
		return container.Count();
	}
	std::size_t GetCapacity()
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


template <typename TKey, typename TElement>
inline IDictionary<TKey, TElement>* MakeDictionary()
{
	return new Dictionary<TKey, TElement>;
}

template <typename TKey, typename TElement>
inline IDictionary<TKey, TElement>* MakeDictionary(IDictionary<TKey, TElement>* DictionaryCopy)
{
	return new Dictionary<TKey, TElement>(DictionaryCopy);
}