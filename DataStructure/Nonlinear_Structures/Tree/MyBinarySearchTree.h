#pragma once
#include <iostream>

using namespace std;

template<typename T>
class MyBSTNode
{
	template<typename T>
	friend class MyBinarySearchTree;

public:
	MyBSTNode()
		: data(), parent(nullptr), left(nullptr), right(nullptr)
	{
	}

	MyBSTNode(const T& data, MyBSTNode<T>* parent = nullptr)
		: data(data), parent(parent), left(nullptr), right(nullptr)
	{
	}

	~MyBSTNode()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

private:
	T data;
	MyBSTNode<T>* parent;
	MyBSTNode<T>* left;
	MyBSTNode<T>* right;
};



template<typename T>
class MyBinarySearchTree
{
public:
	MyBinarySearchTree()
		: root(nullptr)
	{
	}
	~MyBinarySearchTree()
	{
		Destroy();
	}
	
private:
	//재귀삽입처리(node : 현재 비교 노드, parent : node 부모)
	MyBSTNode<T>* InsertNodeRecursive(MyBSTNode<T>* node, MyBSTNode<T>* parent, const T& newData)
	{
		if (node == nullptr) //종료조건
		{
			return new MyBSTNode<T>(newData, parent);
		}

	
		if (node->data > newData)	//추가값이 비교 노드보다 작으면. 왼쪽.
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}
		else		//크면 오른쪽
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	//삭제재귀처리
	MyBSTNode<T>* DeleteNodeRecursive(MyBSTNode<T>* node, const T& deleteData)
	{
		if (node == nullptr) //종료 조건
		{
			return nullptr;
		}

		//작거나 크면 왼쪽-오른쪽 재귀탐색
		if (node->data > deleteData)
		{
			node->left = DeleteNodeRecursive(node->left, deleteData);
		}
		else if (node->data < deleteData)
		{
			node->right = DeleteNodeRecursive(node->right, deleteData);
		}
		else //찾으면 삭제
		{
			//자식이 없는 경우
			if (node->left == nullptr && node->right == nullptr)
			{
				//노드만 삭제후 종료.
				delete node;
				return nullptr;
			}

			//자식이 둘다 있을때
			if (node->left != nullptr && node->right != nullptr)
			{
				//삭제되는 노드 오른쪽에서 가장 작은 값을 검색해 삭제할 노드값 업데이트
				node->data = SearchMinValue(node->right)->data;
				//오른쪽 서브트리에서 업데이트된 값의 노드를 삭제.
				node->right = DeleteNodeRecursive(node->right, node->data);
			}
			//자식이 한쪽만 있을떄
			else
			{
				if (node->left == nullptr)
				{
					MyBSTNode<T>* right = node->right;
					delete node;
					return right;
				}
				else if (node->right == nullptr)
				{
					MyBSTNode<T>* left = node->left;
					delete node;
					return left;
				}
			}
		}

		return node;
	}


	//전위 순회
	void PreOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//종료 조건
		if (node == nullptr)
		{
			for(int i=0; i<depth; i++)
				cout << "  ";

			cout << "nullptr" << endl;
			return;
		}

		for (int i = 0; i < depth; i++)
			cout << "  ";

		cout << node->data << endl;

		PreOrderTraverseRecursive(node->left, depth + 1);
		PreOrderTraverseRecursive(node->right, depth + 1);
	}

	//중위 순회
	void InOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//종료 조건
		if (node == nullptr)
		{
			for (int i = 0; i < depth; i++)
				cout << "  ";

			cout << "nullptr" << endl;
			return;
		}

		InOrderTraverseRecursive(node->left, depth + 1);

		for (int i = 0; i < depth; i++)
			cout << "  ";

		cout << node->data << endl;

		InOrderTraverseRecursive(node->right, depth + 1);
	}

	//후위 순회
	void PostOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//종료 조건
		if (node == nullptr)
		{
			for (int i = 0; i < depth; i++)
				cout << "  ";

			cout << "nullptr" << endl;

			return;
		}

		PostOrderTraverseRecursive(node->left, depth + 1);
		PostOrderTraverseRecursive(node->right, depth + 1);

		for (int i = 0; i < depth; i++)
			cout << "  ";

		cout << node->data << endl;
	}

	void Destroy()
	{
		if (root == nullptr)
		{
			return;
		}

		DestroyRecursive(root);
	}

	void DestroyRecursive(MyBSTNode<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (node->left == nullptr && right == nullptr)
		{
			delete node;
			return;
		}

		DestroyRecursive(node->left);
		DestroyRecursive(node->right);

		delete node;
	}

public:
	bool InsertNode(const T& data)
	{
		if (SearchNode(data) == true)
		{
			cout << "이미 존재하는 값입니다." << endl;
			return false;
		}

		if (root == nullptr)
		{
			root = new MyBSTNode<T>(data);
			return true;
		}

		root = InsertNodeRecursive(root, nullptr, data);
		return true;
	}

	void DeleteNode(const T& data)
	{
		if (SearchNode(data) == false)
		{
			cout << "존재하지 않는 값입니다." << endl;
			return;
		}

		root = DeleteNodeRecursive(root, data);
	}

	MyBSTNode<T>* SearchMinValue(MyBSTNode<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		MyBSTNode<T>* current = node;

		while (current->left != nullptr)
		{
			current = current->left;
		}

		return current;
	}

	bool SearchNode(const T& data)
	{
		return SearchNodeRecursive(root, data);
	}

	bool SearchNodeRecursive(MyBSTNode<T>* node, const T& data)
	{
		if (node == nullptr) //종료 조건
		{
			return false;
		}

		if (node->data == data) //찾음
		{
			return true;
		}
		else if (node->data > data) //작으면 왼쪽
		{
			return SearchNodeRecursive(node->left, data);
		}
		else //크면 오른쪽
		{
			return SearchNodeRecursive(node->right, data);
		}
	}

	void PreOrderTraverse()
	{
		cout << "PreOrder Traversal Start" << endl;
		PreOrderTraverseRecursive(root);
		cout << "PreOrder Traversal End" << endl;
	}

	void InOrderTraverse()
	{
		cout << "InOrder Traversal Start" << endl;
		InOrderTraverseRecursive(root);
		cout << "InOrder Traversal End" << endl;
	}

	void PostOrderTraverse()
	{
		cout << "PostOrder Traversal Start" << endl;
		PostOrderTraverseRecursive(root);
		cout << "PostOrder Traversal End" << endl;
	}


private:
	MyBSTNode<T>* root;
};