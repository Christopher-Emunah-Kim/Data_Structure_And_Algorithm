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
			std::cout << "ù ��° �ؽ� �Լ��� " << key << "��(��) �ֽ��ϴ�.\n";
			return data1.begin() + hash_value1;
		}

		auto hash_value2 = hash2(key);
		if (data2[hash_value2] == key)
		{
			std::cout << "�� ��° �ؽ� �Լ��� " << key << "��(��) �ֽ��ϴ�.\n";
			return data2.begin() + hash_value2;
		}

		//�Ѵ� ���� ��� data2�� end() ��ȯ
		return data2.end();
	}

	void Erase(int key)
	{
		auto iter = find(key);

		if (iter != data2.end())
		{
			*iter = -1;
			std::cout << key << "��(��) �����Ǿ����ϴ�.\n";
		}
		else
		{
			std::cout << key << "��(��) �������� �ʽ��ϴ�.\n";
		}
	}

	//������ ��ͷ� �̷�����Ƿ� ���� Ƚ�� ����
	//�ִ� ���ȣ��Ƚ���� ���̺� ũ��� ���� ����
	void Insert(int key)
	{
		Insert_imp1(key, 0, 1);
	}

	void Insert_imp1(int key, int cnt, int table)
	{
		if(cnt >= size)
		{
			std::cout << "���� ��ȯ �߻�! ���ؽ��� �ʿ��մϴ�!\n";
			return;
		}

		if (table == 1)
		{
			int hash_value = hash1(key);
			if(data1[hash_value] == -1)
			{
				data1[hash_value] = key;
				std::cout << key << "��(��) ù ��° �ؽ� �Լ��� ���ԵǾ����ϴ�.\n";
			}
			else
			{
				int displaced_key = data1[hash_value];
				data1[hash_value] = key;
				std::cout << key << "��(��) ù ��° �ؽ� �Լ��� ���ԵǾ����ϴ�. " 
						  << displaced_key << "��(��) �Ѱܳ����ϴ�.\n";
				Insert_imp1(displaced_key, cnt + 1, 2);
			}
		}
		else
		{
			int hash_value = hash2(key);
			if(data2[hash_value] == -1)
			{
				data2[hash_value] = key;
				std::cout << key << "��(��) �� ��° �ؽ� �Լ��� ���ԵǾ����ϴ�.\n";
			}
			else
			{
				int displaced_key = data2[hash_value];
				data2[hash_value] = key;
				std::cout << key << "��(��) �� ��° �ؽ� �Լ��� ���ԵǾ����ϴ�. " 
						  << displaced_key << "��(��) �Ѱܳ����ϴ�.\n";
				Insert_imp1(displaced_key, cnt + 1, 1);
			}
		}
	}

	void Print() const
	{
		std::cout << "ù ��° �ؽ� �Լ� ���̺�:\n";
		for (int i = 0; i < size; ++i)
		{
			if (data1[i] != -1)
				std::cout << "[" << i << "] : " << data1[i] << "\n";
			else
				std::cout << "[" << i << "] : " << "�������\n";
		}
		std::cout << "�� ��° �ؽ� �Լ� ���̺�:\n";
		for (int i = 0; i < size; ++i)
		{
			if (data2[i] != -1)
				std::cout << "[" << i << "] : " << data2[i] << "\n";
			else
				std::cout << "[" << i << "] : " << "�������\n";
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
//	hashMap.Insert(14); //<-- ��ȯ �߻�!
//}