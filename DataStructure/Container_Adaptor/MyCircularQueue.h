#pragma once
#include <iostream>

constexpr size_t QUEUE_CAPACITY = 10;

template <typename T>
class MyCircularQueue
{
public:
	explicit MyCircularQueue()
		: front(0), rear(0), size(QUEUE_CAPACITY + 1)
	{

	}

	explicit MyCircularQueue(size_t capacity)
		: front(0), rear(0), size(capacity + 1)
	{
		
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		return (rear + 1) % size == front;
	}

	bool Enqueue(const T& value)
	{
		if (IsFull() == true)
		{
			std::cout << "Queue is full, cannot enqueue " << value << std::endl;
			return false;
		}

		rear = (rear + 1) % size;
		arr[rear] = value;

		return true;
	}

	bool Dequeue(T& value)
	{
		if(IsEmpty() == true)
		{
			std::cout << "Queue is empty, cannot dequeue" << std::endl;
			return false;
		}

		front = (front + 1) % size;
		value = arr[front];
		arr[front] = T();

		return true;
	}


	T Peek() const
	{
		if(IsEmpty() == true)
		{
			throw std::out_of_range("Queue is empty, cannot peek");
		}
		else
		{
			return arr[(front + 1) % size];
		}
	}

	void Display() const
	{
		if (IsEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			return;
		}
		std::cout << "Queue contents: ";

		for (int i = (front + 1) % size; i != (rear + 1) % size; i = (i + 1) % size)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	int front;
	int rear;
	size_t size;
	T* arr;
};
