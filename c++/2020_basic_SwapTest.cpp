#include <iostream>

//Call by Value�� Swap


//Call by reference�� Swap
void SwapRef(int &num1, int &num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
//Call by address�� Swap
void SwapAdd(int *p1, int *p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
//���� ������(double pointer)�� Swap
void SwapDou(int **p1, int **p2)
{
	int *temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void main(void)
{
	int a = 3;
	int b = 6;
	std::cout << a << " "<< b << std::endl;

	SwapRef(a, b);
	std::cout << a << " " << b << std::endl;

	SwapAdd(&a, &b);
	std::cout << a << " " << b << std::endl;

	int *pa = &a, *pb = &b;
	SwapDou(&pa, &pb);
	std::cout << *pa << " " << *pb << std::endl;
}