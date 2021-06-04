// Assignment6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Dictionary.h"



int main()
{
	Dictionary<int> d(10);
	//d.Insert("Joao", 611);
	//d.Insert("Joao", 622);
	//d.Insert("Joao", 633);
	//d.Insert("Joao", 644);
	//d.Insert("Joao", 655);
	d.Insert("Joao", 666);
	d.Insert("Guilherme", 26);
	d.Insert("Mascaro", 65);
	d.Insert("Dantas", 37);
	d.Display();
}

