#pragma once
#include <iostream>

template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;
	};

private:
	Node* mHead;

	Node* CreateNode(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		return newNode;
	}

public:
	LinkedList()
		: mHead(nullptr)
	{}

	~LinkedList()
	{
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}

	void Insert(T data)
	{
		Node* newNode = CreateNode(data);
		if (IsEmpty())
		{
			mHead = newNode;
			return;
		}

		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->next == nullptr)
			{
				currentNode->next = newNode;
				currentNode = nullptr;
				break;
			}
			currentNode = currentNode->next;
		}
	}

	void Remove(T data)
	{
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		if (mHead->data == data)
		{
			Node* temp = mHead->next;
			delete mHead;
			mHead = temp;
			temp = nullptr;
			return;
		}

		Node* currentNode = mHead->next;

		while (currentNode->next->data != data && currentNode != nullptr)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			std::cout << "The element is not in the list.\n";
			return;
		}
		Node* temp = currentNode->next;
		currentNode->next = temp->next;
		delete temp;
		temp = nullptr;

	}

	bool IsEmpty()
	{
		return mHead == nullptr;
	}

	//Displays all the elements of the linked list
	void DisplayList()
	{
		// TODO: 1
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}
		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			std::cout << "Displaying List: " << currentNode->data << "\n";
			currentNode = currentNode->next;
		}

	}

	//Error: -5. You should not change mHead value in a display function. Display functions should not change member data.
	//A better way to implement is to use a recursive call. 
	/*void printReverse(Node* node)
	{
		if (node->next != nullptr)
		{
			printReverse(node->next);
		}

		std::cout << node->data << " ";
	}*/

	//And inside the DisplayReverseList, you call printReverse(mHead);

	//Displays all the elements of the linked list in reverse order
	void DisplayReverseList()
	{
		// TODO: 2
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}
		if (mHead->next == nullptr)
		{
			std::cout << "Displaying List Reverse: " << mHead->data << "\n";
			return;
		}

		Node* currentNode = mHead;
		Node* previousNode = nullptr;
		Node* temp;


		while (currentNode != nullptr)
		{
			//Save reference to the next node from where current is
			temp = currentNode->next;
			//Now current next can point to the previous pointer without losing ref of the ->next because temp stores it
			currentNode->next = previousNode;
			//Previous points to the current so current can advance to temp and preserve the pointer to the previous
			previousNode = currentNode;
			currentNode = temp;
		}
		mHead = previousNode;

		//std::cout << "Displaying List Reverse:  " << "\n";
		//DisplayList();
	}

	//This function allows the user to modify an existance data
	//Returns true if the conten was modified and false if it wasn't.
	bool ModifyContent(T content, T newContent)
	{
		// TODO: 3
		if (IsEmpty())
		{
			return false;
		}
		if (mHead->next == nullptr )
		{
			if (mHead->data == content)
			{
				mHead->data == newContent;
				return true;
			}
			else {
				return false;
			}
		}
		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->data == content)
			{
				currentNode->data = newContent;
				return true;
			}
			currentNode = currentNode->next;
		}
		return false;

	}

	//Clear all the data from the linked list
	void ClearList()
	{
		// TODO: 4
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}


};
