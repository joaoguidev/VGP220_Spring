#pragma once
#include <iostream>
#include <string>
#include <list>

//Solve collision with chaining
//This Dictionary does not allows similar keys.

//This struct represents the Data that will be inserted into your dictionary(Hash Map)
template<typename T>
struct Data
{
	std::string key;
	T value;
};

template<typename T>
class Dictionary
{


	//Data<T>** mData;
	//int mCapacity;
	//int mCurrentSize;
public:
	Dictionary(int capacity)
		: mCapacity(capacity)
		, mCurrentSize(0)
	{

		rowCurrentSize = new int[mCapacity];
		rowCapacity = 5;
		//Task 1: Implement the new constructor.
		//	Initialize mData with the capacity: for example:
		//      - mData = new...*[capacity];
		//  Then loop through mData initializing each one of the arrays with size 5. This can be done in 2 ways:
		//      I) mData[i] = new... *[5];   or
		//     II) mData[i] = new...[5];
		//  If you choose I, nested for loop to initialize each element of the sub arrays with nullptr:
		//        mData[i][j] = nullptr;
		//  If you choose II, nested for loop to initialize each key as empty:
		//        mData[i][j].key = "";
		//This initialization is required that you can check if the position for insertion is available or not

		////====================== Way 1 ===================
		//mData = new Data<T>*[mCapacity];

		//for (int i = 0; i < mCapacity; i++)
		//{
		//	mData[i] = new Data<T>*[5];
		//	for (int j = 0; j < 5; j++)
		//	{
		//		mData[i][j] = nullptr;
		//	}
		//}

		//====================== Way 2 ===================
		mData = new Data<T>*[mCapacity];

		for (int i = 0; i < mCapacity; i++)
		{
			mData[i] = new Data<T>[rowCapacity];
			for (int j = 0; j < rowCapacity; j++)
			{
				mData[i][j].key = "";
			}
		}


		for (int i = 0; i < mCapacity; i++)
		{
			rowCurrentSize[i] = 0;
		}


	}

	~Dictionary()
	{
		//Task 2
		// Implement the destructor for this class.
		// Don't forget that if you "new" a data, you have to "delete" this data;
		for (int i = 0; i < mCapacity; i++)
		{
			delete[] mData[i];
		}
		delete[] mData;

		delete[] rowCurrentSize;
	}

	//Task 3 - This hash function receives a key and transforms this key into a int that
	//will be used as an index. Since you have one array with multiples arrays inside, you need at least 
	//one modifiable hash function or 2 different hash functions, that gives you different indices for the same 
	//key.

	//Your task is to:
	// I) Implement a second Hash function, different than this one 
	//                              OR 
	// II) Modify this one in a way, that you can send a parameter 
	//to this function and this hash returns a different index for the same key.

	//If you choose the I, you can keep this Hash, and implement a new one:
	//   example:  int Hash_2(const std::string& key)

	// If you choose II, one of the variables that you can use as parameter is the seed.
	//  example: int Hash(const std::string& key, int seed)
	int Hash(const std::string& key, bool seedForColumn)
	{

		int seed = seedForColumn ? 45 : 79;

		int hash = 0;
		for (int i = 0; i < key.length(); ++i)
		{
			//You don't need to cast, since hash is an integer and you are adding
			//a character, the cast is implicit. static_cast<int> in this case is ambiguous.
			hash += key[i];
		}
		hash *= seed;

		if (seedForColumn)
		{
			return hash % mCapacity;
		}
		return hash % rowCapacity;
	}

	void Insert(const std::string& key, T value)
	{
		//Task 4: This is the hardest method to be implemented. You will need to hash 2 times.
		// Make sure to find two indices (Using your hash functions) and insert to the next available position. If you don't 
		//	have an available position, print a message to the user saying:
		// "Element cannot be inserted. Bucket at index %s is full." %s = hashIndex. 
		if (key.empty())
		{
			std::cout << "Empty keys are not allowed. Please provide a valid key." << std::endl;
			return;
		}
		//if (mCurrentSize == mCapacity)
		//{
		//	std::cout << "Map is full" << std::endl;
		//	return;
		//}
		int hashIndexColumn = Hash(key, true);
		int hashIndexRow = Hash(key, false);
		if (rowCurrentSize[hashIndexColumn] == rowCapacity)
		{
			std::cout << "Row is full" << std::endl;
			return;
		}

		if (mData[hashIndexColumn][hashIndexRow].key.empty())
		{
			mData[hashIndexColumn][hashIndexRow].key = key;
			mData[hashIndexColumn][hashIndexRow].value = value;
			rowCurrentSize[hashIndexColumn]++;
		}
		else 
		{
			hashIndexRow = 0;
			//Dangerous. Yes.
			while (!mData[hashIndexColumn][hashIndexRow].key.empty())
			{
				hashIndexRow++;
			}
			mData[hashIndexColumn][hashIndexRow].key = key;
			mData[hashIndexColumn][hashIndexRow].value = value;
			rowCurrentSize[hashIndexColumn]++;
		}
		return;

	}

	void Display()
	{
		for (int i = 0; i < mCapacity; i++)
		{
			std::cout << "Row " << i;
			for (int j = 0; j < rowCapacity; j++)
			{
				if (!mData[i][j].key.empty())
				{
					std::cout << " | Key:" <<  mData[i][j].key << " Value:" << mData[i][j].value;
				}
				else
				{
					std::cout << " EMPTY ";
				}
			}

			std::cout << "\n";
		}
	}

private:
	//mData is an array of arrays.
	Data<T>** mData;
	int* rowCurrentSize;
	int rowCapacity;
	//Capacity should keep track of the total size of mData. (Number of Arrays * Number of Elements)
	int mCapacity;
	//Current size starts with zero elements and keep track of current size of the data structure.
	int mCurrentSize;
};
