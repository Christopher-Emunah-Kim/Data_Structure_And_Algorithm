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
			//자식 노드 검색
			MyTreeNode<T>* child = *it;
			bool result = FindRecursive(data, child, outNode);

			if (result == true)
				return true;
		}

		//검색 실패
		*outNode = nullptr;
		return false;
	}

	bool RemoveRecursive(const T& data, MyTreeNode<T>* inNode)
	{
		MyTreeNode<T>* targetNode = nullptr;
		bool result = FindRecursive(data, inNode, &targetNode);

		//검색 성공시
		if (result == true)
		{
			//부모 노드의 자손 중 대상 노드 제거.
			MyTreeNode<T>* parent = targetNode->GetParent();
			if (parent != nullptr)
			{
				parent->GetChildren()->remove(targetNode);
			}

			//제거할 자손이 있는 경우
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

	//전위 순회
	void PreorderTraversal(MyTreeNode<T>* inNode, int depth = 0)
	{
		//탈출조건
		if(inNode == nullptr)
		{
			return;
		}

		//계층 보여주기용 깊이 출력
		for(int i = 0; i < depth; ++i)
		{
			std::cout << "--";
		}

		//부모 데이터 출력
		std::cout << inNode->GetData() << std::endl;

		//자식 데이터 출력
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

	//후위 순회
	void PostorderTraversal(MyTreeNode<T>* inNode, int depth = 0)
	{
		//탈출조건
		if (inNode == nullptr)
		{
			return;
		}
		//자식 데이터 출력
		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();
		
		if (children != nullptr && !children->empty())
		{
			for (auto it = children->begin(); it != children->end(); ++it)
			{
				MyTreeNode<T>* child = *it;
				PostorderTraversal(child, depth+1);
			}
		}

		//계층 보여주기용 깊이 출력
		for (int i = 0; i < depth; ++i)
		{
			std::cout << "--";
		}

		//부모 데이터 출력
		std::cout << inNode->GetData() << std::endl;
	}

	//삭제 재귀
	void DestroyRecursive(MyTreeNode<T>* inNode)
	{
		if (inNode == nullptr)
			return;

		// 자식 리스트 포인터
		std::list<MyTreeNode<T>*>* children = inNode->GetChildren();

		// [핵심 수정] 반복자(for) 사용 대신,
		// 리스트가 빌 때까지 항상 맨 앞 원소를 잡아 재귀 삭제
		while (children != nullptr && !children->empty())
		{
			MyTreeNode<T>* child = children->front(); // 한 번에 하나씩
			DestroyRecursive(child);                  // child 내부에서 자기 자신을 부모 리스트에서 제거함
			// 여기서 children은 이미 child가 remove된 상태가 됨
		}

		// 부모가 있으면 부모의 자식 목록에서 자신을 제거
		MyTreeNode<T>* parent = inNode->GetParent();
		if (parent != nullptr)
		{
			parent->GetChildren()->remove(inNode);
		}

		// 마지막으로 자기 자신 삭제
		SafeDelete(inNode);
	}

public:
	// 1. 루트 노드에 자식 추가
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

	// 2. 특정 데이터를 가진 부모에 자식 추가
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