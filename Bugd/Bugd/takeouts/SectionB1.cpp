/**
#include<iostream>



int main()
{
	int Prices[5] = { 5,10,20,50,100 };
	int* PricesPointer;
	PricesPointer = &Prices[5];

	for (int i = 0; i < 5; i++) {
		std::cout << Prices << std::endl;
	}

}
**/