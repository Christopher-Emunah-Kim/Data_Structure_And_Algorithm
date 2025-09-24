
#include <iostream>
#include <string>
#include "DataStructure/Associative Container/BloomFilter.h"

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