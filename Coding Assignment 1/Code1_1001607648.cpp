// Kimberly Duffy - 1001607648 - Coding Assignment 1
#include <iostream>

#define MAX_INPUT 8

using namespace std;

void ConvertDecimalToBinary(char OutputArray[])
{
	int DecimalNum;
	int AskAgain = 1;
	int i;
	int BitArray[8];
	
	while (AskAgain)
	{
		cout << "Please enter a decimal number between 0 and 255 " << endl;
		cin >> DecimalNum;
	
		if (DecimalNum >= 0 && DecimalNum <= 255)
			AskAgain = 0;
		else
		{
			AskAgain = 1;
			cout << "\nYou entered a number not between 0 and 255\n\n" << endl;
		}
	}
	
	BitArray[7] = DecimalNum;
	
	/* Divide by 2 with a right bitshift */
	for (i = 6; i >= 0; i--)
	{
		BitArray[i] = BitArray[i+1] >> 1;
	}

	/* check for even/odd and translate decimal values to character */
	for (i = 0; i <= 7; i++)
	{
		BitArray[i] = (BitArray[i] & 1) ? 1 : 0;
		OutputArray[i] = BitArray[i] + '0';
	}
}

int main(void)
{
	char OutputArray[MAX_INPUT] = {};

	ConvertDecimalToBinary(OutputArray);
	cout << "\n\n" << OutputArray << "\n\n" << endl;

	return 0;
}
