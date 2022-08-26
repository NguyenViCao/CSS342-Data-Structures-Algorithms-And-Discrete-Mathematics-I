#include <iostream>
#include <string>
#include "bank.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*
	//call the bank object
	Bank myBank;
	myBank.ReadFromFile("bank_trans_in.txt");

	//display all accounts
	myBank.Display();

	return 0;
	*/

	if (argc == NULL)
	{
		cout << "Please enter the name of the input text file!" << endl;
	}
	else
	{
		Bank myBank;
		myBank.ReadFromFile(argv[1]);

		//display all accounts
		myBank.Display();

		return 0;
	}
}

