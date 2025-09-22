#pragma once
#include <iostream>
#include <algorithm>

struct Node
{
	int data;
	Node* next;
};

struct Singly_LL_Iterator
{
private:
	Node* ptr;
public:
	Singly_LL_Iterator(Node* p) : ptr(p) {}
	int& operator*() { return ptr->data; }
	Node* GetNode() { return ptr; }

	Singly_LL_Iterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	Singly_LL_Iterator operator++(int)
	{
		Singly_LL_Iterator result = *this;
		++(*this);
		return result;
	}

	friend bool operator==(const Singly_LL_Iterator& a, const Singly_LL_Iterator& b)
	{
		return a.ptr == b.ptr;
	}

	friend bool operator!=(const Singly_LL_Iterator& a, const Singly_LL_Iterator& b)
	{
		return a.ptr != b.ptr;
	}
};

class SinglyLinkedList
{
public:
	SinglyLinkedList() = default;

	SinglyLinkedList(const SinglyLinkedList& other)
		: head(nullptr)
	{
		if (other.head)
		{
			head = new Node{ 0, nullptr };
			auto current = head;
			auto it = other.begin();

			while (true)
			{
				current->data = *it;
				auto temp = it;
				++temp;
				if (temp == other.end())
				{
					break;
				}

				current->next = new Node{ 0, nullptr };
				current = current->next;
				it = temp;
			}
		}
	}

	SinglyLinkedList(const std::initializer_list<int>& initlist)
		: head(nullptr)
	{
		for (auto it = std::rbegin(initlist); it != std::rend(initlist); ++it)
		{
			Push_Front(*it);
		}
	}

	void Push_Front(int val)
	{
		auto newNode = new Node{ val, nullptr };
		if (head != nullptr)
		{
			newNode->next = head;
		}
		head = newNode;
	}

	void Pop_Front()
	{
		auto first = head;
		if (head)
		{
			head = head->next;
			delete first;
		}
	}

	Singly_LL_Iterator begin() { return Singly_LL_Iterator(head); }
	Singly_LL_Iterator end() { return Singly_LL_Iterator(nullptr); }
	Singly_LL_Iterator begin() const { return Singly_LL_Iterator(head); }
	Singly_LL_Iterator end() const { return Singly_LL_Iterator(nullptr); }

private:
	Node* head;
};
