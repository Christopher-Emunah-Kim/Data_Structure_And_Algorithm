#pragma once
#include <vector>
#include <algorithm>

struct SortTest
{
	int num;
	char name;
};

void LambdaPractice()
{
	//1. ���ٽ����� Sort�� �������� ���� �����
	std::vector<SortTest> test = { {1,'a'},{3,'c'},{2,'b'} };
	std::sort(test.begin(), test.end(), 
		[] (const SortTest& a, const SortTest& b) 
		{ return a.num > b.num; });
}

void LambdaPractice2()
{
	//2. Ư�� ������ �����ϴ� ù��° ���� ã��
	std::vector<int> nums = { 1,2,3,4,5,6,7,8,9,10 };

	int threshold = 5;
	std::vector<int>::iterator iter = std::find_if(nums.begin(), nums.end(),
		[threshold](int num) { return num > threshold; });
}