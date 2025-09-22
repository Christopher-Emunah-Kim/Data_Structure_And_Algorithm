
#include <iostream>
#include <string>
#include "DataStructure/Nonlinear_Structures/Tree/MyBinarySearchTree.h"

using namespace std;

int main()
{
	//트리 생성
	MyBinarySearchTree<int> tree;

	//삽입
    tree.InsertNode(50);
    tree.InsertNode(30);
    tree.InsertNode(20);
    tree.InsertNode(40);
    tree.InsertNode(70);
    tree.InsertNode(60);
    tree.InsertNode(80);
    tree.InsertNode(100);
    tree.InsertNode(120);
    tree.InsertNode(130);
    tree.InsertNode(110);
    tree.InsertNode(150);
    tree.InsertNode(170);
    tree.InsertNode(140);

    //전위
	tree.PreOrderTraverse();
    //중위
    tree.InOrderTraverse();
    //후위
    tree.PostOrderTraverse();

    //탐색
	int value = 30;
    if(tree.SearchNode(value))
        cout << value << " exists in the tree." << endl;
    else
		cout << value << " does not exist in the tree." << endl;

    //삭제
	int deleteValue = 20;
    tree.DeleteNode(deleteValue);
    cout << "After deleting " << deleteValue << ":" << endl;
	tree.InOrderTraverse();

    deleteValue = 50;
	tree.DeleteNode(deleteValue);
    cout << "After deleting " << deleteValue << ":" << endl;
    tree.InOrderTraverse();

    deleteValue = 100;
    tree.DeleteNode(deleteValue);
    cout << "After deleting " << deleteValue << ":" << endl;
	tree.InOrderTraverse();
	

	//종료 대기
	std::cin.get();
}