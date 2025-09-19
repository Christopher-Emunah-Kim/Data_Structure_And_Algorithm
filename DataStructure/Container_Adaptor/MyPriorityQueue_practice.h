#pragma once
#include <vector>
#include <iostream>

template <typename T, typename Compare = std::less<T>>
class MyPriorityQueue
{
public:
	MyPriorityQueue() = default;

	explicit MyPriorityQueue(const Compare& compareFunc)
		: data(), comp(compareFunc)
	{

	}

	explicit MyPriorityQueue(std::vector<T> initial, const Compare& cmp = std::less<T>)
		: data(std::move(initial)), comp(cmp)
	{
		Heapify();
	}

private:
	//삽입시 힙 올리기(새로 들어온 원소 위로 올리기)
	void SiftUp(size_t i)
	{
		while (i > 0)
		{
			size_t p = parent(i);

			if(!comp(data[p], data[i])) // 부모가 더 크면 멈춤
				break;
			std::swap(data[p], data[i]);

			i = p;
		}
	}

	//삭제시 힙 내리기(루트 원소 아래로 내리기)
	void SiftDown(size_t i)
	{
		size_t n = data.size();

		while (true)
		{
			size_t l = left(i);
			size_t r = right(i);
			size_t largest = i;

			if (l < n && comp(data[largest], data[l]))
				largest = l;
			if (r < n && comp(data[largest], data[r]))
				largest = r;

			if (largest == i) // 자식이 더 크지 않으면 멈춤
				break;

			std::swap(data[i], data[largest]);

			i = largest;
		}
	}

public:
	inline bool IsEmpty() const noexcept { return data.empty(); }
	inline size_t Size() const noexcept { return data.size(); }

	const T& Top() const
	{
		if (IsEmpty())
			throw std::out_of_range("Priority Queue is empty");

		return data[0];
	}

	void Push(const T& value)
	{
		data.push_back(value);

		SiftUp(data.size() - 1);
	}

	void Push(T&& value)
	{
		data.push_back(std::move(value));

		SiftUp(data.size() - 1);
	}
	
	void Pop()
	{
		if (IsEmpty())
			throw std::out_of_range("Priority Queue is empty");

		//루트 원소와 마지막 원소 교체 후 마지막 원소 제거
		std::swap(data[0], data.back());

		data.pop_back();

		if (!IsEmpty())
			SiftDown(0);
	}
	 
	void Clear() noexcept
	{
		data.clear();
	}

	void Reserve(size_t newCap)
	{
		data.reserve(newCap);
	}

	void Heapify()
	{
		if (data.empty())
			return;

		for (size_t i = parent(data.size() - 1); i < data.size(); --i)
		{
			SiftDown(i);
			if (i == 0)
				break;
		}
	}



private:
	std::vector<T> data;
	Compare comp; // 기본 비교 함수 객체 (최대 힙)

	static constexpr size_t parent(size_t i) { return (i - 1) / 2; }
	static constexpr size_t left(size_t i) { return 2 * i + 1; }
	static constexpr size_t right(size_t i) { return 2 * i + 2; }
};

//
//int main()
//{
//	MyPriorityQueue<int> pq; // 기본: 최대 힙
//	pq.Push(10);
//	pq.Push(40);
//	pq.Push(20);
//	pq.Push(30);
//
//	// 가장 큰 값부터 나오게 됨: 40, 30, 20, 10
//	while (!pq.IsEmpty())
//	{
//		std::cout << pq.Top() << " ";
//		pq.Pop();
//	}
//	std::cout << "\n";
//
//	// 최소 힙으로 쓰고 싶다면 비교자를 std::greater로 지정
//	MyPriorityQueue<int, std::greater<int>> minq;
//	minq.Push(10);
//	minq.Push(40);
//	minq.Push(20);
//	minq.Push(30);
//
//	// 가장 작은 값부터: 10, 20, 30, 40
//	while (!minq.IsEmpty())
//	{
//		std::cout << minq.Top() << " ";
//		minq.Pop();
//	}
//	std::cout << "\n";
//}