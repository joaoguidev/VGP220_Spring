#include <iostream>
#include <assert.h>

//Name: Joao Dantas
//StudentId: 2032559

int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
int PrintFibonacciLessThan15(int n);
int printRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);

int main(int argc, char* argv[])
{
	//Tests:
	std::cout << RecursiveMultiplication(2, 5) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(5) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(7); //Expected result: 0 1 1 2 3 5 8 13
	//std::cout << PrintFibonacciLessThan15(7) << std::endl;

	std::cout << std::endl;// ->Adding an extra line

	printRecursiveFactorialLessThan50(10);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1

	return 0;
}

int RecursiveMultiplication(int a, int b)
{
	//TODO: Write a recursive function to multiply two positive integers
	//without using the operator *
	//You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
	//should minimize the number of those operations.



	return 0;
}

int NonRecursiveFibonacci(int n)
{
	//TODO: Convert the recursive fibonacci that we did in class
	//to a non recursive method, using a bottom-up approach.
	//f(0) = 0           = 0
	//f(1) = 1           = 1
	//f(2) = f(0) + f(1) = 1
	//f(3) = f(1) + f(2) = 2
	//f(4) = f(2) + f(3) = 3
	//f(n) = f(n-2) + f(n-1)

	assert(n >= 0);
	int current = 0;
	if (n <= 1)
	{
		return n;
	}
	else {
		for (int index = 2, fibA = 0 , fibB = 1 ; index <= n; index++)
		{
			current = fibA + fibB;
			fibA = fibB; // f(n-2)
			fibB = current; // f(n-1)
		}
	}
	return current;
}

int PrintFibonacciLessThan15(int n)
{
	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.
	assert(n >= 0);
	int fibA = 0;
	int fibB = 0;
	if (n <= 1)
	{
		return n;
	}
	else {
		fibA = PrintFibonacciLessThan15(n - 2);
		fibB = PrintFibonacciLessThan15(n - 1);
		std::cout << fibA + fibB << " ";
		return fibA + fibB;
	}
	return 0;

}

int printRecursiveFactorialLessThan50(int n)
{
	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".
	return 0;
}

//TODO: Show with dynamic programming, the results and calls for DynamicProgrammingFunc(10)
//Identify repeated calls. This question you can do in a piece of paper drawing the calls
//and results and saving an image on your git repo.
int DynamicProgrammingFunc(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	return DynamicProgrammingFunc(n - 3) - (DynamicProgrammingFunc(n - 1) * DynamicProgrammingFunc(n - 2));
}