#pragma once
#include <vector>
#include <iostream>

class BloomFilter
{
public:
	BloomFilter(int n)
		: nBits(n)
	{
		data = std::vector<bool>(nBits, false);
	}

private:
	int Hash(int num, int key)
	{
		//해시함수 3개
		switch (num)
		{
		case 0: return key % nBits;
		case 1: return (key / 7) % nBits;
		case 2: return (key / 11) % nBits;
		}

		return 0;
	}

public:
	void Find(int key)
	{
		bool result = data[Hash(0, key)] && data[Hash(1, key)] && data[Hash(2, key)];

		if(result)
			std::cout << key << " is in the set (maybe)" << std::endl;
		else
			std::cout << key << " is not in the set" << std::endl;
	}

	void Insert(int key)
	{
		data[Hash(0, key)] = true;
		data[Hash(1, key)] = true;
		data[Hash(2, key)] = true;

		std::cout << key << " inserted" << std::endl;

		for(auto a : data)
			std::cout << a << " ";
		std::cout << std::endl;
	}

	//삭제 함수는 만들 수 없음

	void Print()
	{
		for(auto a : data)
			std::cout << a << " ";
		std::cout << std::endl;
	}


private:
	std::vector<bool> data;
	int nBits;
};

int main()
{
	BloomFilter bloomFilter(7);

	bloomFilter.Print();

	std::cout << std::endl;

	bloomFilter.Insert(100);
	bloomFilter.Insert(54);
	bloomFilter.Insert(82);

	std::cout << std::endl;

	bloomFilter.Print();

	std::cout << std::endl;

	bloomFilter.Find(5);
	bloomFilter.Find(50);
	bloomFilter.Find(20);
	bloomFilter.Find(54);

	bloomFilter.Print();
	std::cout << std::endl;

	return 0;
}