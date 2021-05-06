#include <iostream>
#include <assert.h>

//Name: Joao Dantas
//StudentId: 2032559
//Grade: 100/100

int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
int PrintFibonacciLessThan15(int n);
int printRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);

int main(int argc, char* argv[])
{
	//Tests:
	std::cout << RecursiveMultiplication(2,0) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(7) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(5); //Expected result: 0 1 1 2 3 5 8 13

	std::cout << std::endl;// ->Adding an extra line

	printRecursiveFactorialLessThan50(49);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
	//DynamicProgrammingFunc(10);
	return 0;
}

//COMMENT: In this case, you don't need to check for b==0. But it's all good!
int RecursiveMultiplication(int a, int b)
{
	//TODO: Write a recursive function to multiply two positive integers
	//without using the operator *
	//You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
	//should minimize the number of those operations.
	if (a == 0 || b == 0) {
		return 0;
	} 
	if (a > 1)
	{
		return b + RecursiveMultiplication(a - 1, b);
	}
	if (a <= -1)
	{
		return RecursiveMultiplication(-a, -b);
	}
	return b;
	
}

//COMMENT: GOOD!
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

//COMMENT: GREAT!
int PrintFibonacciLessThan15(int n)
{
	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.
	assert(n>=0);//This assert is redundant
	int maxFib = NonRecursiveFibonacci(n);
	int index = 0;
	assert(maxFib < 15);

	while (index <= n-1)
	{
		std::cout << NonRecursiveFibonacci(index) << " ";
		++index;
	}
	std::cout << maxFib << " ";
	return 0;

}
//COMMENT: GOOD!
int printRecursiveFactorialLessThan50(int n)
{
	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".
	//0! = 1 //Due to the definition
	//1! = 1
	//2! = 2 * 1 = 2
	//3! = 3 * 2 * 1 = 6
	//n! = n * (n-1) * (n-2) ...n
	assert(n >= 0 && n < 50);
	if (n == 0)
	{
		return 1;
	}
	std::cout << n;
	if (n > 1) {
		std::cout << " * ";
	}
	return printRecursiveFactorialLessThan50(n-1);
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