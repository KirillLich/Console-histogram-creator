#pragma once
#include "Base structs\IDIctionary.h"
#include <iostream>
#include <utility>

template <typename Key>
struct std::hash<std::pair<Key,Key>>
{
	template<typename T1, typename T2>
	std::size_t operator()(std::pair<T1, T2>& pair)
	{
		std::size_t first = std::hash<T1>()(pair.first);
		std::size_t second = std::hash<T2>()(pair.second);
		return first ^ second;
	}
};

template <typename TAttribute>
using Range = std::pair<TAttribute, TAttribute>;

template <typename TElement>
using Sequence = std::vector<TElement>;

template <typename TAttribute>
using Feature = TAttribute(*)();

using Amount = std::size_t;

//Range values имеет смысл оставить чтобы можно было строить гистограмму для выборки, попадающей в этот диапазон

template <typename TElement, typename TAttribute>
IDictionary<Range<TAttribute>, std::vector<TElement>> CreateHistogram(
	std::vector<TElement> items,
	std::size_t partitionQuantity,
	Range<TAttribute> values,
	TAttribute (TElement::*func)())
{
	IDictionary<Range<TAttribute>, std::vector<TElement>> histogram;

	TAttribute step = (values.second - values.first) / partitionQuantity;
	for (std::size_t i = 0; i < partitionQuantity; i++)
	{
		Range<TAttribute>current(values.first + i * step, values.first + (i + 1) * step);
		histogram.Add(current, std::vector<TElement>());
	}

	for (std::size_t i = 0; i < items.size(); i++)
	{
		TAttribute attribute = (items[i].*func)();
		TAttribute rangeStart = values.first + step * (std::size_t)((attribute - values.first) /step);
		Range<TAttribute>current(rangeStart, rangeStart + step);
		if (rangeStart == values.second)
		{
			current.first = rangeStart - step;
			current.second = rangeStart;
		}

		if(histogram.ContainsKey(current)) histogram.Get(current).push_back(items[i]);
	}

	return histogram;
}

template <typename TElement, typename TAttribute>
Amount MaxSelection(IDictionary<Range<TAttribute>, std::vector<TElement>>& histogram, std::size_t partitionQuantity, Range<TAttribute> values)
{
	TAttribute step = (values.second - values.first) / partitionQuantity;
	Amount max = (histogram.Get(Range<TAttribute>(values.first, values.first + step)).size());

	for (TAttribute i = values.first; i < values.second; i+=step)
	{
		Amount current = (histogram.Get(Range<TAttribute>(i, i + step)).size());
		if (current > max)max = current;
	}

	return max;
}

template <typename TElement, typename TAttribute>
void VisualizeHistogram(IDictionary<Range<TAttribute>, std::vector<TElement>>& histogram, std::size_t partitionQuantity, Range<TAttribute> values)
{
	Amount max = MaxSelection(histogram, partitionQuantity, values);
	TAttribute step = (values.second - values.first) / partitionQuantity;

	for (int height = max; height > 0; height--)
	{
		std::cout << height << "|\t";

		for (TAttribute i = values.first; i < values.second; i += step)
		{
			Amount current = (histogram.Get(Range<TAttribute>(i, i + step)).size());
			if (current >= height)
			{
				std::cout << "X\t";
			}
			else
			{
				std::cout << '\t';
			}
		}
		std::cout << '\n';
	}

	std::cout << "\t";
	for (TAttribute i = values.first; i < values.second; i += step)
	{
		std::cout << i << '-' << i + step << '\t';
	}

}