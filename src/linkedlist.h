#pragma once
#include "bullet.h"
#include "enemy.h"

template <class T>
class LinkedList
{
public:
	struct Node
	{
		Node(T* data) : data(data), next(nullptr) {}
		T* data;
		Node* next;
	};

	LinkedList() : mHead(nullptr), mTail(nullptr), mSize(0) {}
	~LinkedList()
	{
		Node* temp = mHead;
		while (temp)
		{
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
	}
	void push_back(T* data)
	{
		Node* newNode = new Node(data);
		if (!mHead)
		{
			mHead = newNode;
		}
		else
		{
			mTail->next = newNode;
		}
		mTail = newNode;
		mSize++;
	}
	void erase(Node* node)
	{
		if (node == mHead)
		{
			mHead = mHead->next;
			delete node->data;
			delete node;
		}
		else
		{
			Node* temp = mHead;
			while (temp->next != node)
			{
				temp = temp->next;
			}
			temp->next = node->next;
			delete node->data;
			delete node;
		}
		mSize--;
	}
	Node* head() { return mHead; }
	Node* last() { return mTail; }
	int size() { return mSize; }
private:
	Node* mHead;
	Node* mTail;
	int mSize;
};
