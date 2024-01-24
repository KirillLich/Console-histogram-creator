#pragma once
#include <functional>
#include <vector>

template <
	typename Key,
	typename T,
	typename Hash = std::hash<Key>
>
class HashTable
{
	struct Node
	{
		Key key;
		T item;
		Node* next;
	};

	class List
	{
		Node* first = nullptr;
		Node* last = nullptr;
		friend List;
	public:
		List() = default;
		List(const List& list)
		{
			Node* currentNode = list.first;
			while (currentNode)
			{
				Node insertingNode{ currentNode->key,currentNode->item,nullptr };
				this->PushBack(insertingNode);
				currentNode = currentNode->next;
			}
		}

		Node* GetLast() { return last; }
		Node* GetFirst() { return first; }

		void PushBack(Node node)
		{
			Node* insertingNode = new Node(node);
			if (!first)
			{
				first = insertingNode;
			}
			if (!last)
			{
				last = insertingNode;
			}
			else
			{
				last->next = insertingNode;
				last = insertingNode;
			}
		}
		void Pop(Key key)
		{
			Node* currentNode = first,*previousNode = nullptr;
			while (currentNode->key != key)
			{
				previousNode = currentNode;
				currentNode = currentNode->next;
			}

			if (previousNode)
			{
				previousNode->next = currentNode->next;
			}
			if (currentNode == first)
			{
				first = currentNode->next;
			}
			if (currentNode == last)
			{
				last = previousNode;
			}
			delete currentNode;
		}

		T& Get(Key key)
		{
			Node* currentNode = first;
			while (currentNode->key != key)
				currentNode = currentNode->next;
			return currentNode->item;
		}

		bool TryGet(Key key)
		{
			Node* currentNode = first;
			while (currentNode)
			{
				if (currentNode->key == key) return true;
				currentNode = currentNode->next;
			}
			return false;
		}

		~List()
		{
			if (first == nullptr)return;

			Node* currentNode = first, * nextNode = currentNode->next;
			while (currentNode)
			{
				delete currentNode;
				currentNode = nextNode;
				if (currentNode) nextNode = currentNode->next;
			}
		}
	};

	std::size_t capacity;
	std::size_t count;

	const std::size_t expansionCoeff = 2;
	const std::size_t extraCapacityCoeff = 2;

	std::vector<List> container;

	void IncreaseCapacity()
	{
		capacity *= expansionCoeff;
	}

	void DecreaseCapacity()
	{
		capacity /= expansionCoeff;
	}

	void Rearrangement()
	{
		std::vector<List> newContainer(container);
		container.clear();
		container.resize(capacity);
		for (List list:newContainer)
		{
			Node* currentNode = list.GetFirst();
			while (currentNode)
			{
				Key key = currentNode->key;
				T item = currentNode->item;
				std::size_t index = Hash{}(key) % capacity;
				Node node{ key,item,nullptr };
				container[index].PushBack(node);
				currentNode = currentNode->next;
			}
		}
	}
	
public:
	HashTable() = delete;
	HashTable(std::size_t capacity) : capacity(capacity), count(0) 
	{
		container.resize(capacity);
	}

	std::size_t Count() { return count; }
	std::size_t GetCapacity() { return capacity; }

	void Add(Key key, T item)
	{
		std::size_t index = Hash{}(key) % capacity;
		Node node{ key,item,nullptr };
		container[index].PushBack(node);
		count++;
		if (count == capacity)
		{
			IncreaseCapacity();
			Rearrangement();
		}
	}

	T& Get(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		return container[index].Get(key);
	}

	void Remove(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		container[index].Pop(key);
		count--;
		if (count < capacity/extraCapacityCoeff)
		{
			DecreaseCapacity();
			Rearrangement();
		}
	}

	bool ContainsKey(Key key)
	{
		std::size_t index = Hash{}(key) % capacity;
		return container[index].TryGet(key);
	}
};