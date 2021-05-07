#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue
{
private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;

public:
	Queue() 
	{
		mCapacity = 1;
		mCurrentSize = 0;
		mData = new T[mCapacity];
		front = mCapacity - 1;
		rear = mCapacity - 1;
	};
	Queue(int mCapacity)
		:mCapacity(mCapacity), mCurrentSize(0)
	{
		mData = new T[mCapacity];
		front = mCapacity - 1;
		rear = mCapacity - 1;
	}
	~Queue()
	{
		delete[] mData;
		mData = nullptr;
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (rear < 0)
		{
			std::cout << "Stack Overflow \n";
			return;
		}
		mData[rear] = data;
		if (rear != 0) {
			rear--;
		}
	}

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (isEmpty())
		{
			std::cout << "Empty Array \n";
			return false;
		}
		if (rear == mCapacity)
		{
			std::cout << "Stack Underflow \n";
			return false;
		}


		for (int i = front; i < rear; i--)
		{
			if (i < rear - 1)
			{
				mData[i] = mData[i - 1];
			}

		}
		rear++;
		/*for (int i = rear; i < mCapacity; i++)
		{
			if (i < mCapacity - 1)
			{
				mData[i] = mData[i + 1];
			}
	
		}*/
		
		return true;

		//I didn't understand what is expected here. If i misinterpreted what was expected please consider the commented code bellow
		//The expected is to select one of the items, including on the midle of the array to be taken out??
		// Or shouldit respect FIFO where the first to come out is the fist that came in ? 
		//int itemIndex = FindItemIndex(output);
		//if (itemIndex == -1) {
		//	return false;
		//}
		//for (int i = itemIndex; i < mCapacity; i++)
		//{

		//	if (i < mCapacity - 1)
		//	{
		//		mData[i] = mData[i + 1];
		//	}
		//}
		//rear++;



		//return &mData[front + 1];

	}

	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		if (front == rear) {
			return true;
		}
		return false;
	}
	//Return the index of the searched item in the array or for -1 not found
	int FindItemIndex(int find) {
		if (isEmpty()) 
		{
			return -1;
		}
		for (int i = rear; i < mCapacity; i++)
		{
			if (mData[i] == find)
			{
				return i;
			}
	
		}
		return -1;
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{
		if (isEmpty())
		{
			std::cout << "Empty Array \n";
			return;
		}
		int f = front;
		int r = rear;
		std::cout << "Front -> ";
		for (int i = front; i >= rear; i--)
		{
			std::cout << mData[i];
			if (i >= rear + 1) {
				std::cout << " ,";
			}
		}
		std::cout << " <-Rear \n";
	}

};
