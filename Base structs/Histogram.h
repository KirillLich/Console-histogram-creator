#pragma once
#include "Dictionary.h"
#include "..\Algorithms\HistogramAlgo.h"

//TElement may be Person
//TAttribute may be float
template <typename TElement, typename TAttribute>
class Histogram
{
private:
	using Range = std::pair<TAttribute, TAttribute>;

	using Sequence = std::vector<TElement>;

	using Feature = TAttribute(TElement::*)();

	IDictionary<Range, Sequence>* container;
	std::vector<Range> intervals;
public:
	~Histogram()
	{
		delete container;
	}

	Histogram(Sequence histigramBasis, Range dataInterval, std::size_t partitionQuantity, Feature method)
	{
		container = MakeDictionary<Range, Sequence>();

		TAttribute step = (dataInterval.second - dataInterval.first) / partitionQuantity;
		for (std::size_t i = 0; i < partitionQuantity; i++)
		{
			Range current(dataInterval.first + i * step, dataInterval.first + (i + 1) * step);
			if (i + 1 == partitionQuantity && dataInterval.first + (i + 1) * step < dataInterval.second)
				current.second = dataInterval.second;
			intervals.push_back(current);
			container->Add(current, Sequence());
		}

		for (std::size_t i = 0; i < histigramBasis.size(); i++)
		{
			TAttribute attribute = (histigramBasis[i].*method)();

			TAttribute rangeStart = 0, rangeEnd = 0;
			for (std::size_t i = 0; i < intervals.size(); i++)
			{
				if (
					attribute >= intervals[i].first &&
					attribute < intervals[i].second
					)
				{
					rangeStart = intervals[i].first;
					rangeEnd = intervals[i].second;
					break;
				}
			}

			Range current(rangeStart, rangeEnd);

			container->Get(current).push_back(histigramBasis[i]);
		}
	}

	std::size_t MaxSelection()
	{
		std::size_t max = container->Get(intervals[0]).size();
		for (size_t i = 0; i < intervals.size(); i++)
		{
			std::size_t current = container->Get(intervals[i]).size();
			if (max < current)max = current;
		}

		return max;
	}

	std::size_t IntervalsNumber()
	{
		return intervals.size();
	}

	Sequence& Get(Range interval)
	{
		return container->Get(interval);
	}

	std::vector<Range> GetIntervals()
	{
		return intervals;
	}
};