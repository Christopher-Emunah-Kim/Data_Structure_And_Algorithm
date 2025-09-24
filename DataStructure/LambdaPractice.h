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
	//1. 람다식으로 Sort의 내림차순 정렬 만들기
	std::vector<SortTest> test = { {1,'a'},{3,'c'},{2,'b'} };
	std::sort(test.begin(), test.end(), 
		[] (const SortTest& a, const SortTest& b) 
		{ return a.num > b.num; });
}

void LambdaPractice2()
{
	//2. 특정 조건을 만족하는 첫번째 원소 찾기
	std::vector<int> nums = { 1,2,3,4,5,6,7,8,9,10 };

	int threshold = 5;
	std::vector<int>::iterator iter = std::find_if(nums.begin(), nums.end(),
		[threshold](int num) { return num > threshold; });
}