#pragma once
#include <list>
#include <iostream>
#include <string>

using namespace std;

class HashTable
{
	using myPair = pair<string, string>;

public:
	HashTable();
	~HashTable();

	bool	IsEmpty() const;
	void	Add(const string& key, const string& value);
	void	Delete(const string& key);
	myPair	Find(const string& key) const;
	void	PrintTable() const;

private:
	static const int hashCount = 19;
	list<myPair> table[hashCount];
};