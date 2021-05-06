#pragma once
#include <iostream>
#include "Item.h"
#include <assert.h>

class Inventory
{
public:
	Inventory() 
		: mSlotsOccupied(0)
		, mMaxSlots(5)
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mInventory = new Item[5];
		std::cout << "TEST -> DEFAULT CONSTRUCTOR Called with mMaxSlots if 5"<< std::endl;

	}
	Inventory(uint32_t capacity)
		: mSlotsOccupied(0)
		, mMaxSlots(capacity)
	{
		////TODO: Implement a non default constructor for the Inventory class where 
		////all the slots are free (They are not occupied).
		mInventory = new Item[capacity];
		std::cout << "TEST -> NON DEFAULT CONSTRUCTOR Called with mMaxSlots defined by the user" << std::endl;

	}
	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
		CopyingElement(other);

		std::cout << "TEST -> COPY CONSTRUCTOR Called" << std::endl;
	}

	//==>!!!IMPORTANT!!! Because the move constructor is O(1) and copy constructor is O(n) <===
	//==> ALWAYS PREFER using the move to perform tasks !!!!!!!!!!!!!!!!!!!!!!<====
	Inventory(Inventory&& other)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
		MoveElement(std::move(other));
		std::cout << "TEST -> MOVE CONSTRUCTOR Called" << std::endl;
	}
	~Inventory()
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
		mInventory = nullptr;
		std::cout << "TEST -> DESTRUCTOR Called" << std::endl;
	}

	//TODO: Implement a copy assignment operator

	Inventory& operator=(const Inventory& rhs)
	{
		if (this != &rhs) 
		{
			CopyingElement(rhs);
		}
		std::cout << "TEST -> COPY ASSIGNMENT OPERATOR Called" << std::endl;
		return *this;
	}
	
	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& rhs)
	{
		if (this != &rhs)
		{
			MoveElement(std::move(rhs));
		}
		std::cout << "TEST -> MOVE ASSIGNMENT OPERATOR Called" << std::endl;
		return *this;
	}
		
	Item& operator[](uint32_t index)
	{
		bool isValid = index >= 0 && index < mSlotsOccupied;
		assert(isValid && "Access violation");
		return *(mInventory + index);
	}



	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
		// 
		//First it searches for this item to see if the item exists.
		int itemIndex = SearchItemByName(newItem.name); //If -1 item doesn't exist otherwise the item index in the mInventory
		int IndexItemLessThan50 = SearchItemByNameLessThan50(newItem.name);


		if (itemIndex == -1)
		{
		//If the item exists it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP
				//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;
			//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
			//should expand adding 5 more empty slots for the user.
			
			if (newItem.type == ItemType::Charm)
			{
				Expansion(5);
				mInventory[mSlotsOccupied] = newItem;
				mSlotsOccupied++;
			}
			else if (mSlotsOccupied == mMaxSlots)
			{
				std::cout << "Inventory is Full" << std::endl;
				//Expansion(mMaxSlots);
			}
			else {
				mInventory[mSlotsOccupied] = newItem;
				mSlotsOccupied++;
			}
		}

		else if (IndexItemLessThan50 != -1)
		{
			uint32_t quantityOnItemFound = mInventory[IndexItemLessThan50].quantity;
			if (quantityOnItemFound + newItem.quantity <= 50)
			{
				mInventory[IndexItemLessThan50].quantity += newItem.quantity;
			}
			else {
				newItem.quantity = (quantityOnItemFound + newItem.quantity) - 50;
				mInventory[IndexItemLessThan50].quantity = 50;
				if (mSlotsOccupied == mMaxSlots)
				{
					std::cout << "Inventory is Full! Discarting " << newItem.quantity << " " << newItem.name <<std::endl;
					//Expansion(mMaxSlots);
				}
				else 
				{
					mInventory[mSlotsOccupied] = newItem;
					mSlotsOccupied++;
				}
			}

		}


		std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
		//PrintInventory();
	}

	void RemoveItem(std::string itemName, int quantity)
	{
		PrintInventory();
		int itemWith50 = SearchItemByNameWith50(itemName);
		int itemIndex = SearchItemByName(itemName);

		if (itemWith50 > -1 && quantity >= 50) 
		{
			RemovingElementOfIndex(itemWith50);
		} 
		else if (itemIndex > -1)
		{
			if (quantity < mInventory[itemIndex].quantity)
			{
				mInventory[itemIndex].quantity -= quantity;
			}
			else {
				RemovingElementOfIndex(itemIndex);
			}
		}
		if (itemName == "Charm") 
		{
			for (int i = 0; i < 5; i++)
			{
				RemovingElementOfIndex(mMaxSlots);
			}
			
		}
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.


		PrintInventory();
		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.
	}

	Item* UseItem(std::string itemName)
	{
		int itemIndex = SearchItemByName(itemName);
		if (itemIndex > -1 )
		{
			if (mInventory[itemIndex].type == ItemType::Potion) {
				mInventory[itemIndex].quantity -= 1;
				Item* returnMe = new Item{ itemName, 1, ItemType::Potion };
				return returnMe;
			}
			if (mInventory[itemIndex].type == ItemType::Utility) {
				mInventory[itemIndex].quantity -= 1;
				Item* returnMe = new Item{ itemName, 1, ItemType::Utility };
				return returnMe;
			}
			
		}
		else {
			nullptr;
		}
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.
		std::cout << "Using " << itemName << "\n";
	}

private:

	void PrintInventory()
	{
		std::cout << "===========================================" << "\n";
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			std::cout << "name: " <<   mInventory[i].name << " Quantity: " << mInventory[i].quantity <<"\n";
		}
		std::cout << "===========================================" << "\n";
	}

	void Expansion(int additionalCapacity)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots + additionalCapacity];
		mMaxSlots += additionalCapacity;

		for (int i = 0; i < mSlotsOccupied; i++)
		{
			mInventory[i] = temp[i];
		}
		delete[] temp;
		temp = nullptr;
	}


	void CopyingElement(const Inventory& other)
	{
		mSlotsOccupied = other.mSlotsOccupied;
		mMaxSlots = other.mMaxSlots;
		delete[] mInventory;
		mInventory = nullptr;
		mInventory = new Item[other.mMaxSlots];
		for (int i = 0; i < other.mSlotsOccupied; i++)
		{
			mInventory[i] = other.mInventory[i];
		}
	}
	void RemovingElementOfIndex( int indexOfElementOut)
	{
		assert(indexOfElementOut <= mMaxSlots && indexOfElementOut >= 0);
		Item* tempInventory = new Item[mMaxSlots-1];
		int inneCounter = 0;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (i != indexOfElementOut)
			{
				tempInventory[inneCounter] = mInventory[i];
				inneCounter++;
			}
		}
		delete[] mInventory;
		mInventory = nullptr;
		mInventory = tempInventory;
		tempInventory = nullptr;
		mSlotsOccupied -= 1;
		mMaxSlots -= 1;
	}

	void MoveElement(Inventory&& other)
	{
		mSlotsOccupied = other.mSlotsOccupied;
		other.mSlotsOccupied = 0;
		mMaxSlots = other.mMaxSlots;
		other.mMaxSlots = 0;
		delete[] mInventory;
		mInventory = nullptr;
		mInventory = other.mInventory;
		other.mInventory = nullptr;
	}
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;


	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	int SearchItemByNameWith50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity == 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};