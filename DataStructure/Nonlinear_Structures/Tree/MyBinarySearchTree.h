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
	//��ͻ���ó��(node : ���� �� ���, parent : node �θ�)
	MyBSTNode<T>* InsertNodeRecursive(MyBSTNode<T>* node, MyBSTNode<T>* parent, const T& newData)
	{
		if (node == nullptr) //��������
		{
			return new MyBSTNode<T>(newData, parent);
		}

	
		if (node->data > newData)	//�߰����� �� ��庸�� ������. ����.
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}
		else		//ũ�� ������
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	//�������ó��
	MyBSTNode<T>* DeleteNodeRecursive(MyBSTNode<T>* node, const T& deleteData)
	{
		if (node == nullptr) //���� ����
		{
			return nullptr;
		}

		//�۰ų� ũ�� ����-������ ���Ž��
		if (node->data > deleteData)
		{
			node->left = DeleteNodeRecursive(node->left, deleteData);
		}
		else if (node->data < deleteData)
		{
			node->right = DeleteNodeRecursive(node->right, deleteData);
		}
		else //ã���� ����
		{
			//�ڽ��� ���� ���
			if (node->left == nullptr && node->right == nullptr)
			{
				//��常 ������ ����.
				delete node;
				return nullptr;
			}

			//�ڽ��� �Ѵ� ������
			if (node->left != nullptr && node->right != nullptr)
			{
				//�����Ǵ� ��� �����ʿ��� ���� ���� ���� �˻��� ������ ��尪 ������Ʈ
				node->data = SearchMinValue(node->right)->data;
				//������ ����Ʈ������ ������Ʈ�� ���� ��带 ����.
				node->right = DeleteNodeRecursive(node->right, node->data);
			}
			//�ڽ��� ���ʸ� ������
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


	//���� ��ȸ
	void PreOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//���� ����
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

	//���� ��ȸ
	void InOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//���� ����
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

	//���� ��ȸ
	void PostOrderTraverseRecursive(MyBSTNode<T>* node, int depth = 0)
	{
		//���� ����
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
			cout << "�̹� �����ϴ� ���Դϴ�." << endl;
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
			cout << "�������� �ʴ� ���Դϴ�." << endl;
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
		if (node == nullptr) //���� ����
		{
			return false;
		}

		if (node->data == data) //ã��
		{
			return true;
		}
		else if (node->data > data) //������ ����
		{
			return SearchNodeRecursive(node->left, data);
		}
		else //ũ�� ������
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


////�׽�Ʈ �ڵ�
//int main()
//{
//	//Ʈ�� ����
//	MyBinarySearchTree<int> tree;
//
//	//����
//	tree.InsertNode(50);
//	tree.InsertNode(30);
//	tree.InsertNode(20);
//	tree.InsertNode(40);
//	tree.InsertNode(70);
//	tree.InsertNode(60);
//	tree.InsertNode(80);
//	tree.InsertNode(100);
//	tree.InsertNode(120);
//	tree.InsertNode(130);
//	tree.InsertNode(110);
//	tree.InsertNode(150);
//	tree.InsertNode(170);
//	tree.InsertNode(140);
//
//	//����
//	tree.PreOrderTraverse();
//	//����
//	tree.InOrderTraverse();
//	//����
//	tree.PostOrderTraverse();
//
//	//Ž��
//	int value = 30;
//	if (tree.SearchNode(value))
//		cout << value << " exists in the tree." << endl;
//	else
//		cout << value << " does not exist in the tree." << endl;
//
//	//����
//	int deleteValue = 20;
//	tree.DeleteNode(deleteValue);
//	cout << "After deleting " << deleteValue << ":" << endl;
//	tree.InOrderTraverse();
//
//	deleteValue = 50;
//	tree.DeleteNode(deleteValue);
//	cout << "After deleting " << deleteValue << ":" << endl;
//	tree.InOrderTraverse();
//
//	deleteValue = 100;
//	tree.DeleteNode(deleteValue);
//	cout << "After deleting " << deleteValue << ":" << endl;
//	tree.InOrderTraverse();
//
//
//	//���� ���
//	std::cin.get();
//}