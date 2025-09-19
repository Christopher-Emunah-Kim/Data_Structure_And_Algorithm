#pragma once
#include <stdexcept>
#include <utility>	

//배열 기반 스택 구현
template <typename T>
class MyStack
{
private:
	T* arr;
	int capacity;
	int top;
	static const int STACK_CAPACITY = 10;

public:
	explicit MyStack(int cap = STACK_CAPACITY)
		: arr(nullptr), capacity(cap <= 0 ? STACK_CAPACITY : cap), top(-1)
	{
		arr = new T[capacity];
	}

	~MyStack()
	{
		Release();
	}

	MyStack(const MyStack&) = delete;
	MyStack& operator=(const MyStack&) = delete;

	MyStack(MyStack&& other) noexcept
		: arr(other.arr), capacity(other.capacity), top(other.top)
	{
		other.arr = nullptr;
		other.capacity = 0;
		other.top = -1;
	}

	MyStack& operator= (MyStack&& other) noexcept
	{
		if (this == &other)
			return *this;

		delete[] arr;
		arr = other.arr;
		capacity = other.capacity;
		top = other.top;

		other.arr = nullptr;
		other.capacity = 0;
		other.top = -1;

		return *this;
	}

	T& Top()
	{
		if (IsEmpty())
		{
			throw std::out_of_range("Stack is empty");
		}

		return arr[top];
	}

	const T& Top() const
	{
		if (IsEmpty())
		{
			throw std::out_of_range("Stack is empty");
		}
		return arr[top];
	}

	void Push(const T& value)
	{
		if (top + 1 >= capacity)
		{
			throw std::overflow_error("Stack overflow");
		}
		arr[++top] = value;
	}

	void Push(T&& value)
	{
		if (top + 1 >= capacity)
		{
			throw std::overflow_error("Stack overflow");
		}
		arr[++top] = std::move(value);
	}

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::out_of_range("Stack is empty");
		}
		--top;
	}

	void Clear() noexcept
	{
		top = -1;
	}

	void Release()
	{
		if (!arr) return;
		delete[] arr;
		arr = nullptr;

		capacity = 0;
		top = -1;
	}

	void Reset(int newCap = STACK_CAPACITY)
	{
		Release();
		capacity = newCap <= 0 ? STACK_CAPACITY : newCap;
		arr = new T[capacity];
		top = -1;
	}

	inline bool IsEmpty() const { return top == -1; }

	inline int Size() const { return top + 1; }

	inline int Capacity() const { return capacity; }
};



//TEST CODE

//int main()
//{
//	//스택이 비어있는지 확인 isEmpty(), Size()사용 후 출력
//	MyStack<int> stack;
//	printf("IsEmpty: %d, Size: %d\n", stack.IsEmpty(), stack.Size());
//
//
//	//데이터(10) 넣고 top위치 값과 스택 크기출력
//	//데이터(20) 넣고 top위치 값과 스택 크기출력
//	//데이터(30) 넣고 top위치 값과 스택 크기출력
//	stack.Push(10);
//	printf("Top: %d, Size: %d\n", stack.Top(), stack.Size());
//	stack.Push(20);
//	printf("Top: %d, Size: %d\n", stack.Top(), stack.Size());
//	stack.Push(30);
//	printf("Top: %d, Size: %d\n", stack.Top(), stack.Size());
//
//
//	//Pop테스트. 데이터 하나 뺀값. 스택의 남은 top과 스택크기 출력
//	stack.Pop();
//	printf("After Pop - Top: %d, Size: %d\n", stack.Top(), stack.Size());
//	//Clear테스트. 스택이 비어있는지 확인 isEmpty(), Size()사용 후 출력
//	stack.Clear();
//	printf("After Clear - IsEmpty: %d, Size: %d\n", stack.IsEmpty(), stack.Size());
//
//	//스택 오버플로 테스트 스택 가득채우고 한번 더 넣어보기
//	try
//	{
//		for (int i = 1; i <= 11; ++i)
//		{
//			stack.Push(i * 10);
//			printf("Pushed %d - Top: %d, Size: %d\n", i * 10, stack.Top(), stack.Size());
//		}
//	}
//	catch (const std::overflow_error& e)
//	{
//		printf("Exception: %s\n", e.what());
//	}
//
//	//스택 언더플로 테스트. 스택 다 비우고 한번더 빼보기.
//	try
//	{
//		while (true)
//		{
//			printf("Popping - Top: %d, Size: %d\n", stack.Top(), stack.Size());
//			stack.Pop();
//		}
//	}
//	catch (const std::out_of_range& e)
//	{
//		printf("Exception: %s\n", e.what());
//	}
//
//	return 0;
//}