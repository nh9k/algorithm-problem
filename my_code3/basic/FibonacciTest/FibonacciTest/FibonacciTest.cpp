#include <iostream>
#include <vector>

int Fibonaci(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else {
		return Fibonaci(n - 1) + Fibonaci(n - 2);
	}
}

std::vector <int> memorize(46);
int FibonacciUpgrade(int n)
{
	if (memorize[n] != 0)
		return memorize[n];
	else if (n == 0)
	{
		memorize[n] = 0;
		return 0;
	}
	else if (n == 1)
	{
		memorize[n] = 1;
		return 1;
	}
	else
	{
		memorize[n] = FibonacciUpgrade(n - 1) + FibonacciUpgrade(n - 2);
		return memorize[n];
	}
}

int main(void)
{
	int n;
	std::cin >> n;

	//Original Fibonacci Solution
	//std::cout << Fibonaci(n);

	//Upgraded Fibonacci Solution with memorize
	memorize.resize(n+1);
	std::cout << FibonacciUpgrade(n);

	return 0;
}