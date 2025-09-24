#pragma once
#include <iostream>
#include <vector>

class HashMap
{
public:
	HashMap(int n)
		: size(n)
	{
		data1 = std::vector<int>(n, -1);
		data2 = std::vector<int>(n, -1);
	}

public:
	int hash1(int key) const
	{
		return key % size;
	}

	int hash2(int key) const
	{
		return (key / size) % size;
	}

	std::vector<int>::iterator find(int key)
	{
		auto hash_value1 = hash1(key);
		if (data1[hash_value1] == key)
		{
			std::cout << "첫 번째 해시 함수에 " << key << "가(이) 있습니다.\n";
			return data1.begin() + hash_value1;
		}

		auto hash_value2 = hash2(key);
		if (data2[hash_value2] == key)
		{
			std::cout << "두 번째 해시 함수에 " << key << "가(이) 있습니다.\n";
			return data2.begin() + hash_value2;
		}

		//둘다 없는 경우 data2의 end() 반환
		return data2.end();
	}

	void Erase(int key)
	{
		auto iter = find(key);

		if (iter != data2.end())
		{
			*iter = -1;
			std::cout << key << "가(이) 삭제되었습니다.\n";
		}
		else
		{
			std::cout << key << "가(이) 존재하지 않습니다.\n";
		}
	}

	//삽입이 재귀로 이루어지므로 삽입 횟수 제한
	//최대 재귀호출횟수를 테이블 크기와 같게 설정
	void Insert(int key)
	{
		Insert_imp1(key, 0, 1);
	}

	void Insert_imp1(int key, int cnt, int table)
	{
		if(cnt >= size)
		{
			std::cout << "삽입 순환 발생! 재해싱이 필요합니다!\n";
			return;
		}

		if (table == 1)
		{
			int hash_value = hash1(key);
			if(data1[hash_value] == -1)
			{
				data1[hash_value] = key;
				std::cout << key << "가(이) 첫 번째 해시 함수에 삽입되었습니다.\n";
			}
			else
			{
				int displaced_key = data1[hash_value];
				data1[hash_value] = key;
				std::cout << key << "가(이) 첫 번째 해시 함수에 삽입되었습니다. " 
						  << displaced_key << "가(이) 쫓겨났습니다.\n";
				Insert_imp1(displaced_key, cnt + 1, 2);
			}
		}
		else
		{
			int hash_value = hash2(key);
			if(data2[hash_value] == -1)
			{
				data2[hash_value] = key;
				std::cout << key << "가(이) 두 번째 해시 함수에 삽입되었습니다.\n";
			}
			else
			{
				int displaced_key = data2[hash_value];
				data2[hash_value] = key;
				std::cout << key << "가(이) 두 번째 해시 함수에 삽입되었습니다. " 
						  << displaced_key << "가(이) 쫓겨났습니다.\n";
				Insert_imp1(displaced_key, cnt + 1, 1);
			}
		}
	}

	void Print() const
	{
		std::cout << "첫 번째 해시 함수 테이블:\n";
		for (int i = 0; i < size; ++i)
		{
			if (data1[i] != -1)
				std::cout << "[" << i << "] : " << data1[i] << "\n";
			else
				std::cout << "[" << i << "] : " << "비어있음\n";
		}
		std::cout << "두 번째 해시 함수 테이블:\n";
		for (int i = 0; i < size; ++i)
		{
			if (data2[i] != -1)
				std::cout << "[" << i << "] : " << data2[i] << "\n";
			else
				std::cout << "[" << i << "] : " << "비어있음\n";
		}
	}

private:
	std::vector<int> data1;
	std::vector<int> data2;
	int size;
};


//
//int main()
//{
//	HashMap hashMap(7);
//
//	hashMap.Print();
//	std::cout << std::endl;
//
//	hashMap.Insert(10);
//	hashMap.Insert(20);
//	hashMap.Insert(30);
//	std::cout << std::endl;
//
//	hashMap.Print();
//	std::cout << std::endl;
//
//	hashMap.Insert(104);
//	hashMap.Insert(2);
//	hashMap.Insert(70);
//	hashMap.Insert(9);
//	hashMap.Insert(90);
//	hashMap.Insert(2);
//	hashMap.Insert(7);
//	std::cout << std::endl;
//
//	hashMap.Print();
//	std::cout << std::endl;
//
//	hashMap.Insert(14); //<-- 순환 발생!
//}