#pragma once
#include "..\Base structs\Dictionary.h"
#include "..\Base structs\Histogram.h"
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
void VisualizeHistogram(Histogram<TElement,TAttribute>& histogram)
{
	Amount max = histogram.MaxSelection();
	std::vector<std::pair<TAttribute, TAttribute>> intervals = histogram.GetIntervals();

	for (std::size_t height = max; height > 0; height--)
	{
		std::cout << height << "|\t";

		for (std::size_t i = 0; i < histogram.IntervalsNumber(); i++ )
		{
			std::size_t current = histogram.Get(intervals[i]).size();
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
	for (std::size_t i = 0; i < histogram.IntervalsNumber(); i++ )
	{
		std::cout << intervals[i].first << '-' << intervals[i].second << '\t';
	}

}