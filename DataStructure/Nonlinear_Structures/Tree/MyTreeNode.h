#pragma once
#include <list>


template<typename T>
void SafeDelete(T*& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
class MyTreeNode
{
public:
	MyTreeNode()
		: data(), parent(nullptr)
	{
		children = new std::list<MyTreeNode<T>*>();
	}

	MyTreeNode(const T& inData)
		: data(inData), parent(nullptr)
	{
		children = new std::list<MyTreeNode<T>*>();
	}

	MyTreeNode(const MyTreeNode& other) = delete;
	MyTreeNode& operator=(const MyTreeNode& other) = delete;

	~MyTreeNode()
	{
		parent = nullptr;
		SafeDelete(children);
	}

private:
	void RemoveChildRecursive(MyTreeNode<T>* child)
	{
		if (child == nullptr || children->empty())
		{
			return;
		}

		//하위 노드 체크
		std::list<MyTreeNode<T>*>* childList = child->GetChildren();

		//children이 null인 경우
		//children이 null은 아니나 비어있는 경우
		if(childList == nullptr || childList->empty())
		{
			//부모의 자손목록에서 자신을 제거
			child->GetParent()->GetChildren()->remove(child);
			SafeDelete(child);
			return;
		}

		//children이 있는 경우
		while(childList != nullptr && !childList->empty())
		{
			RemoveChildRecursive(childList->front());
		}

		//모든 자손 제거 후 자기자신 제거
		child->GetParent()->GetChildren()->remove(child);
		SafeDelete(child);
	}

public:
	void AddChild(const T & inData)
	{
		AddChild(new MyTreeNode<T>(inData));
	}

	void AddChild(MyTreeNode<T>*child)
	{
		if (child == nullptr)
		{
			return;
		}
		child->parent = this;
		children->push_back(child);
	}

	void RemoveChild(MyTreeNode<T>*child)
	{
		RemoveChildRecursive(child);
	}

	int GetCount()
	{
		int count = 1; //include self

		if (children == nullptr || children->empty())
		{
			return count;
		}

		for (auto it = children->begin(); it != children->end(); ++it)
		{
			if (*it)
				count += (*it)->GetCount();
		}

		return count;
	}

	inline T GetData() const { return data; }
	inline std::list<MyTreeNode<T>*>* GetChildren() const { return children; }
	inline MyTreeNode<T>* GetParent() const { return parent; }
	inline void SetParent(MyTreeNode<T>*newParent) { parent = newParent; }


private:
	T data;
	MyTreeNode<T>* parent;
	std::list<MyTreeNode<T>*>* children;
};