
#include <iostream>
#include <string>
#include "DataStructure/Nonlinear_Structures/Tree/MyDefaultTree.h"

using namespace std;

int main()
{
	//트리 생성
	MyDefaultTree<string>* tree = new MyDefaultTree<string>("Root");
	tree->AddChild("B");
	tree->AddChild("B", "E");
	tree->AddChild("B", "F");

	tree->AddChild("C");
	tree->AddChild("C", "G");

	tree->AddChild("D");
	tree->AddChild("D", "H");
	tree->AddChild("D", "I");


	//순회
	cout << "Pre-order Traversal:" << endl;
	tree->PreOrderTraverse();
	cout << "Pre-order Traversal End" << endl << endl;

	cout << "Post-order Traversal:" << endl;
	tree->PostOrderTraverse();
	cout << "Post-order Traversal End" << endl << endl;

	//검색
	MyTreeNode<string>* outNode;
	if (tree->Find("I", &outNode))
	{
		cout << "검색 성공, 부모 : " 
			<< (outNode->GetParent() ? outNode->GetParent()->GetData() : "None") 
			<< ", 자식 수 : " << outNode->GetChildren()->size() << endl;
	}
	else
	{
		cout << "검색 실패" << endl;
	}

	//삭제
	if(tree->Remove("B"))
	{
		cout << "노드 B 삭제 성공" << endl;
		cout << "삭제 후 Pre-order Traversal:" << endl;
		tree->PreOrderTraverse();
		cout << "Pre-order Traversal End" << endl << endl;
	}
	else
	{
		cout << "노드 B 삭제 실패" << endl;
	}

	delete tree;

	//종료 대기
	std::cin.get();
}