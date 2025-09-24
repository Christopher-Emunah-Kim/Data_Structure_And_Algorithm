#include "HashTable.h"

//해싱 함수
int GenerateKey(const string& key)
{
	int hash = 0;
	for (char ch : key)
	{
		//jdk 방식
		hash = hash*31 + ch;
	}
	return std::abs(hash);
}


HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

bool HashTable::IsEmpty() const
{
	size_t sum = 0;
	for (int i = 0; i < hashCount; ++i)
	{
		sum += table[i].size();
	}
	return sum == 0;
}

void HashTable::Add(const string& key, const string& value)
{
	//1. key로 해싱함수 호출
	int bucketIdx = GenerateKey(key) % hashCount;

	//2. 해당 버킷에 key가 존재하는지 확인
	list<myPair>& position = table[bucketIdx];

	for(auto iter = position.begin(); iter != position.end(); ++iter)
	{
		if (iter->first == key && iter->second == value)
		{
			cout << "이미 존재하는 key, value 쌍입니다.\n";
			return;
		}
	}

	position.emplace_back(myPair(key, value));
}

void HashTable::Delete(const string& key)
{
	int bucketIdx = GenerateKey(key) % hashCount;

	list<myPair>& position = table[bucketIdx];

	for (auto iter = position.begin(); iter != position.end(); ++iter)
	{
		if (iter->first == key)
		{
			position.erase(iter);
			return;
		}
	}

	cout << "존재하지 않는 key입니다.\n";
}

HashTable::myPair HashTable::Find(const string& key) const
{
	//검색
	int bucketIdx = GenerateKey(key) % hashCount;
	if (table[bucketIdx].size() == 0)
	{
		cout << "존재하지 않는 key입니다.\n";
		return myPair("", "");
	}

	//순회
	for(auto iter = table[bucketIdx].begin(); iter != table[bucketIdx].end(); ++iter)
	{
		if (iter->first == key)
		{
			return *iter;
		}
	}

	cout << "존재하지 않는 key입니다.\n";
	return myPair("", "");
}

void HashTable::PrintTable() const
{
	for (int i = 0; i < hashCount; ++i)
	{
		if (table[i].size() == 0)
			continue;

		for(auto iter = table[i].begin(); iter != table[i].end(); ++iter)
		{
			cout << "key: " << iter->first << ", value: " << iter->second << "\n";
		}
	}
}


//int main()
//{
//	HashTable hashTable;
//
//	hashTable.Add("name", "kim");
//	hashTable.Add("age", "20");
//	hashTable.Add("address", "seoul");
//	hashTable.Add("hobby", "soccer");
//	hashTable.Add("food", "pizza");
//
//	hashTable.PrintTable();
//
//	auto p = hashTable.Find("name");
//
//	cout << "Find name: " << p.first << ", " << p.second << "\n";
//
//	hashTable.Delete("age");
//
//	hashTable.PrintTable();
//
//	return 0;
//}