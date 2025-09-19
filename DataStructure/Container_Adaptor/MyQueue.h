#pragma once
#include <iostream>

class MyQueue
{
private:
	struct Node
	{
		int value;
		Node* prev;
		Node* next;
	};

public:
	MyQueue()
		: front(nullptr), rear(nullptr), size(0), capacity(QUEUE_CAPACITY)
	{
		front = new Node();
		front->prev = nullptr;
		front->next = nullptr;
		rear = front;
	}

	~MyQueue()
	{
		Clear();
		delete front;
		front = nullptr;
		rear = nullptr;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}

	bool IsFull() const
	{
		return size >= capacity;
	}

	void Enqueue(int value)
	{
		if (IsFull())
		{
			std::cout << "Queue is full, cannot enqueue " << value << std::endl;
		}
		
		Node* newNode = new Node();
		newNode->value = value;
		newNode->prev = rear;
		newNode->next = nullptr;

		rear->next = newNode;
		rear = newNode;

		++size;
	}

	void Dequeue()
	{	
		if (IsEmpty())
		{
			std::cout << "Queue is empty, cannot dequeue" << std::endl;
			return;
		}

		Node* temp = front->next;
		if (temp)
		{
			front->next = temp->next;

			if (temp->next)
			{
				temp->next->prev = front;
			}
			else
			{
				rear = front; 
			}
			delete temp;
			--size;
		}
	}

	int Peek() const
	{
		if (IsEmpty())
		{
			throw std::out_of_range("Queue is empty, cannot peek");
		}
		return front->next->value;
	}

	void Clear() noexcept
	{
		while (!IsEmpty())
		{
			Dequeue();
		}
	}

	void TestPrintQueue() const
	{
		Node* current = front->next;
		std::cout << "Queue contents: ";
		while (current)
		{
			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

private:

	static const size_t QUEUE_CAPACITY = 10;
	size_t size;
	int capacity;

	Node* front;
	Node* rear;
};

//
//int main()
//{
//	//테스트용 메뉴 만들기
//	//1. Enqueue
//	//2. Dequeue
//	//3. Peek
//	//4. TestPrintQueue
//	//5. 종료
//	MyQueue q;
//
//	while (true)
//	{
//		printf("큐 테스트 프로그램\n");
//		printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. TestPrintQueue\n5. 종료\n");
//
//		int choice;
//		std::cin >> choice;
//
//		switch (choice)
//		{
//		case 1:
//		{
//			int value;
//			std::cout << "Enqueue할 값 입력: ";
//			std::cin >> value;
//			q.Enqueue(value);
//			q.TestPrintQueue();
//			break;
//		}
//		case 2:
//		{
//			q.Dequeue();
//			q.TestPrintQueue();
//			break;
//		}
//		case 3:
//		{
//			try
//			{
//				int frontValue = q.Peek();
//				std::cout << "Peek한 값: " << frontValue << std::endl;
//			}
//			catch (const std::out_of_range& e)
//			{
//				std::cout << e.what() << std::endl;
//			}
//		}
//		case 4:
//		{
//			q.TestPrintQueue();
//			break;
//		}
//		case 5:
//		{
//			std::cout << "프로그램 종료" << std::endl;
//			return 0;
//		}
//		}
//	}
//}