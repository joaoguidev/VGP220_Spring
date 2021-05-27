#pragma once
#include <iostream>
//Assignment 5: Implement a templatized priority queue, using a Max Heap for operations 
//like Enqueue and Daqueue

template<typename T>
class PriorityQueue
{

public:

	struct Data
	{
		int priority;
		T data;
	};

	//Data* mDataArray;
	//int mCapacity;
	//int mSize;
	//Data mEmptyValue;

	PriorityQueue(Data emptyValue) : mCapacity(10), mSize(0)
	{
		//TODO_1: Implement the constructor of this priority queue
		//Look to do this, look at the member variables that you have.
		//You can default initiliaze your capacity with 10 elements.
		mDataArray = new Data[10];
		//Data d = emptyValue;
		//d.priority = INT_MIN;
		//d.data = "ERROR";
		mEmptyValue = emptyValue;

	}

	~PriorityQueue()
	{
		//TODO_2: Implement the destructor of this priority queue
		//Remember that whatever you "new" you have to "delete"
		delete[] mDataArray;
		mDataArray = nullptr;

	}

	void Enqueue(Data data)
	{
		//TODO_3: Implement an Enqueue method for this priority queue.
		//This enqueue should follow the same insertion method that
		//a max heap has.
		//
		//Remember:
		//Heaps Insertion: Place the element at the end of the array,
		//In a loop, check yourself against you parent.priority. 
		//If yours is bigger, swap;
		if (mSize != mCapacity)
		{
			mDataArray[mSize] = data;
			int i = mSize;
			//for (int i = 0; i < mSize; i++)
			//{
			//	std::cout << mDataArray[i].priority << "  ";
			//}
			++mSize;
			while (i != 0 && mDataArray[GetParent(i)].priority < mDataArray[i].priority)
			{
				swap(&mDataArray[i], &mDataArray[GetParent(i)]);
				i = GetParent(i);
			}
		}
		else
		{
			std::cout << "Not Enough Space";
		}
	}

	Data Dequeue()
	{
		//TODO_4: Implement a Dequeue method for this priority queue.
		//This Dequeue should follow the same RemoveMax method that
		//a max heap has.
		//
		//Remember:
		//Heaps RemoveMax: Make the first element to receive the last
		//element from your array. After this, Heapfy.
		//If the queue is empty, return mEmptyValue

		if (mSize != 0)
		{
			--mSize;
			if (mSize == 1)
			{
				return mDataArray[0];
			}
			Data root = mDataArray[0];
			mDataArray[0] = mDataArray[mSize];
			Heapfy(0);
			return root;
		}

		return mEmptyValue;
	}

	int GetSize() const
	{
		return mSize;
	}

private:
	Data* mDataArray;
	int mCapacity;
	int mSize;
	Data mEmptyValue;

	int GetParent(int index) const
	{
		return (index - 1) / 2;
	}

	int GetLeft(int index) const
	{
		return (index * 2) + 1;
	}

	int GetRight(int index) const
	{
		return (index * 2) + 2;
	}

	void swap(Data* a, Data* b)
	{
		Data temp = *a;
		*a = *b;
		*b = temp;
	}

	void Heapfy(int index)
	{
		//TODO_5: Implement Heapfy
		//
		//Remember:
		//Heapfy: In a loop, checks which one is bigger in priority between left and right. and select.
		//Then compares with it's priority. If parent priority is smaller, Swap.
		int leftIndex = GetLeft(index);
		int rightIndex = GetRight(index);
		int smallest = index;
		if (leftIndex < mSize -1 && mDataArray[leftIndex].priority > mDataArray[smallest].priority)
		{
			smallest = leftIndex;
		}
		if (rightIndex < mSize - 1 && mDataArray[rightIndex].priority > mDataArray[smallest].priority)
		{
			smallest = rightIndex;
		}

		if (smallest != index)
		{
			swap(&mDataArray[index], &mDataArray[smallest]);
			Heapfy(smallest);
		}

	}
};
