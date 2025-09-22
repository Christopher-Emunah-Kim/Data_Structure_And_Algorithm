#pragma once

#include <iostream>
#include <list>
#include "MyTreeNode.h"

template<typename T>
class MyDefaultTree
{
public:
	MyDefaultTree(const T& data)
	{
		root = new MyTreeNode<T>(data);
	}

	~MyDefaultTree()
	{
		DestroyRecursive(root);
	}

private:
	bool FindRecursive(const T& data, MyTreeNode<T>* inNode, MyTreeNode<T>** outNode)
	{
		if (inNode == nullptr)
		{
			*outNode = nullptr;
			return false;
		}

		if (inNode->GetData() == data)
		{
			*outNode = inNode;
			return true;
		}

		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();
		if (children == nullptr)
		{
			*outNode = nullptr;
			return false;
		}

		for (auto it = children->begin(); it != children->end(); ++it)
		{
			//�ڽ� ��� �˻�
			MyTreeNode<T>* child = *it;
			bool result = FindRecursive(data, child, outNode);

			if (result == true)
				return true;
		}

		//�˻� ����
		*outNode = nullptr;
		return false;
	}

	bool RemoveRecursive(const T& data, MyTreeNode<T>* inNode)
	{
		MyTreeNode<T>* targetNode = nullptr;
		bool result = FindRecursive(data, inNode, &targetNode);

		//�˻� ������
		if (result == true)
		{
			//�θ� ����� �ڼ� �� ��� ��� ����.
			MyTreeNode<T>* parent = targetNode->GetParent();
			if (parent != nullptr)
			{
				parent->GetChildren()->remove(targetNode);
			}

			//������ �ڼ��� �ִ� ���
			std::list<MyTreeNode<T>*>* children = targetNode->GetChildren();
			while(children != nullptr && !children->empty())
			{
				targetNode->RemoveChild(children->front());
			}

			SafeDelete(targetNode);

			return true;
		}

		return false;
	}

	//���� ��ȸ
	void PreorderTraversal(MyTreeNode<T>* inNode, int depth = 0)
	{
		//Ż������
		if(inNode == nullptr)
		{
			return;
		}

		//���� �����ֱ�� ���� ���
		for(int i = 0; i < depth; ++i)
		{
			std::cout << "--";
		}

		//�θ� ������ ���
		std::cout << inNode->GetData() << std::endl;

		//�ڽ� ������ ���
		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();
		if(children == nullptr || children->empty())
		{
			return;
		}

		for (auto it = children->begin(); it != children->end(); ++it)
		{
			MyTreeNode<T>* child = *it;
			PreorderTraversal(child, depth+1);
		}
	}

	//���� ��ȸ
	void PostorderTraversal(MyTreeNode<T>* inNode, int depth = 0)
	{
		//Ż������
		if (inNode == nullptr)
		{
			return;
		}
		//�ڽ� ������ ���
		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();
		
		if (children != nullptr && !children->empty())
		{
			for (auto it = children->begin(); it != children->end(); ++it)
			{
				MyTreeNode<T>* child = *it;
				PostorderTraversal(child, depth+1);
			}
		}

		//���� �����ֱ�� ���� ���
		for (int i = 0; i < depth; ++i)
		{
			std::cout << "--";
		}

		//�θ� ������ ���
		std::cout << inNode->GetData() << std::endl;
	}

	//���� ���
	void DestroyRecursive(MyTreeNode<T>* inNode)
	{
		if (inNode == nullptr)
			return;

		// �ڽ� ����Ʈ ������
		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();

		// [�ٽ� ����] �ݺ���(for) ��� ���,
		// ����Ʈ�� �� ������ �׻� �� �� ���Ҹ� ��� ��� ����
		while (children != nullptr && !children->empty())
		{
			MyTreeNode<T>* child = children->front(); // �� ���� �ϳ���
			DestroyRecursive(child);                  // child ���ο��� �ڱ� �ڽ��� �θ� ����Ʈ���� ������
			// ���⼭ children�� �̹� child�� remove�� ���°� ��
		}

		// �θ� ������ �θ��� �ڽ� ��Ͽ��� �ڽ��� ����
		MyTreeNode<T>* parent = inNode->GetParent();
		if (parent != nullptr)
		{
			parent->GetChildren()->remove(inNode);
		}

		// ���������� �ڱ� �ڽ� ����
		SafeDelete(inNode);
	}

public:
	// 1. ��Ʈ ��忡 �ڽ� �߰�
	void AddChild(const T& childData)
	{
		if (root == nullptr) {
			std::cout << "Root node is null." << std::endl;
			return;
		}

		MyTreeNode<T>* childNode = new MyTreeNode<T>(childData);
		childNode->SetParent(root);
		root->AddChild(childNode);
	}

	// 2. Ư�� �����͸� ���� �θ� �ڽ� �߰�
	void AddChild(const T& parentData, const T& childData)
	{
		MyTreeNode<T>* parentNode = nullptr;
		bool result = FindRecursive(parentData, root, &parentNode);

		if (result && parentNode != nullptr)
		{
			MyTreeNode<T>* childNode = new MyTreeNode<T>(childData);
			childNode->SetParent(parentNode);
			parentNode->AddChild(childNode);
		}
		else
		{
			std::cout << "Parent node with data " << parentData << " not found." << std::endl;
		}
	}

	bool Remove(const T& data)
	{
		if (root != nullptr && root->GetData() == data) 
		{
			std::cout << "Cannot remove root node." << std::endl;
			return false;
		}
		return RemoveRecursive(data, root);
	}

	void PreOrderTraverse(int depth = 0)
	{
		PreorderTraversal(root, depth);
	}

	void PostOrderTraverse(int depth = 0)
	{
		PostorderTraversal(root, depth);
	}

	bool Find(const T& data, MyTreeNode<T>** outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	std::list<MyTreeNode<T>*>* GetChildren() const { return root? root->GetChildren() : nullptr; }

private:
	MyTreeNode<T>* root = nullptr;

};