#pragma once

template<typename TKey, typename TElement>
class IDictionary
{
public:
	virtual std::size_t GetCount() = 0;
	virtual std::size_t GetCapacity() = 0;
	
	virtual TElement& Get(TKey key) = 0;

	virtual bool ContainsKey(TKey key) = 0;
	virtual void Add(TKey key, TElement element) = 0;
	virtual void Remove(TKey key) = 0;

	virtual ~IDictionary() {};
};