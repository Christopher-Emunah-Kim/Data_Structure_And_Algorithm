#pragma once
#include <iostream>

template<typename T>
class DoubleLinkedList
{
	struct ListNode
	{
		T Data{};
		ListNode* Next = nullptr;
		ListNode* Prev = nullptr;

		explicit ListNode(const T& InData)
			: Data(InData)
		{
		};

		explicit ListNode(T&& InData) noexcept
			: Data(std::move(InData))
		{
		};
	}

public:
	DoubleLinkedList() = default;

	~DoubleLinkedList()
	{
		Clear();
	}

	void Push_Front(const T& InData)
	{
		ListNode* NewNode = new ListNode(InData);
		NewNode->Next = Head;
		Head->Prev = NewNode;
		Head = NewNode;

		if (Tail == nullptr)
		{
			Tail = Head;
		}
		++Size;
	}

	void Push_Back(const T& InData)
	{
		ListNode* NewNode = new ListNode(InData);
		NewNode->Prev = Tail;
		if (Tail)
		{
			Tail->Next = NewNode;
		}

		Tail = NewNode;
		if (!Head)
		{
			Head = Tail;
		}
		++Size;
	}

	void Pop_Front()
	{
		if (Head == nullptr)
		{
			return;
		}

		ListNode* Temp = Head;
		Head = Head->Next;

		if (Head)
		{
			Head->Prev = nullptr;
		}
		else
		{
			Tail = nullptr;
		}

		delete Temp;
		--Size;
	}

	void Pop_Back()
	{
		if (Tail == nullptr)
		{
			return;
		}

		ListNode* Temp = Tail;
		Tail = Tail->Prev;
		if (Tail)
		{
			Tail->Next = nullptr;
		}
		else
		{
			Head = nullptr;
		}

		delete Temp;
		--Size;
	}

	void Emplace_Front(T&& InData) noexcept
	{
		ListNode* NewNode = new ListNode(std::move(InData));
		newMode->next = Head;
		if (Head)
		{
			Head->Prev = NewNode;
		}

		Head = NewNode;

		if (Tail == nullptr)
		{
			Tail = Head;
		}

		++Size;
	}

	void Emplace_Back(T&& InData) noexcept
	{
		ListNode* NewNode = new ListNode(std::move(InData));
		NewNode->Prev = Tail;
		if (Tail)
		{
			Tail->Next = NewNode;
		}
		Tail = NewNode;
		if (Head == nullptr)
		{
			Head = Tail;
		}
		++Size;
	}

	void Insert_At(const T& InData, std::size_t Position)
	{
		if (Position <= 0 || Head == nullptr)
		{
			Push_Front(InData);
			return;
		}
		if (Position >= Size)
		{
			Push_Back(InData);
			return;
		}

		ListNode* Current = Head;
		for (__int32 i = 0; i < Position - 1; ++i)
		{
			Current = Current->Next;
		}
		ListNode* NewNode = new ListNode(InData);
		NewNode->Next = Current->Next;
		NewNode->Prev = Current;
		Current->Next->Prev = NewNode;
		Current->Next = NewNode;
		++Size;
	}

	void Remove(const T& InData)
	{
		if (Head == nullptr)
		{
			return;
		}
		if (Head->Data == InData)
		{
			Pop_Front();
			return;
		}
		if (Tail->Data == InData)
		{
			Pop_Back();
			return;
		}

		ListNode* Current = Head->Next;
		while (Current)
		{
			if (Current->Data == InData)
			{
				Current->Prev->Next = Current->Next;
				if (Current->Next)
				{
					Current->Next->Prev = Current->Prev;
				}
				delete Current;

				--Size;
				return;
			}
			Current = Current->Next;
		}
	}

	void Remove_At(std::size_t Position)
	{
		if (Head == nullptr || Position < 0 || Position >= Size)
		{
			return;
		}
		if (Position == 0)
		{
			Pop_Front();
			return;
		}
		if (Position == Size - 1)
		{
			Pop_Back();
			return;
		}

		ListNode* Current = Head;
		for (__int32 i = 0; i < Position; ++i)
		{
			Current = Current->Next;
		}
		Current->Prev->Next = Current->Next;
		if (Current->Next)
		{
			Current->Next->Prev = Current->Prev;
		}
		delete Current;
		--Size;
	}

	T* Search(const T& InData) const
	{
		ListNode* Current = Head;

		while (Current != nullptr)
		{
			if (Current->Data == InData)
			{
				return &Current->Data;
			}
			Current = Current->Next;
		}

		return nullptr;
	}

	const T* Search(const T& InData)
	{
		ListNode* Current = Head;
		while (Current != nullptr)
		{
			if (Current->Data == InData)
			{
				return &Current->Data;
			}
			Current = Current->Next;
		}
		return nullptr;
	}

	void Clear()
	{
		while (Head != nullptr)
		{
			Pop_Front();
		}
	}

	__int32 GetSize() const
	{
		return Size;
	}

	bool IsEmpty() const
	{
		return Size == 0;
	}

	void PrintList() const
	{
		ListNode* Current = Head;
		while (Current != nullptr)
		{
			std::cout << Current->Data << " <-> ";
			Current = Current->Next;
		}
		std::cout << "nullptr" << std::endl;
	}


private:
	ListNode* Head = nullptr;
	ListNode* Tail = nullptr;
	__int32 Size = 0;
};
