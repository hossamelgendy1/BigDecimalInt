#include "BigDecimalInt.h"

int main()
{
	int choice = 0;
	while (choice != 3)
	{
		cout << "Welcome to FCI Calculator\n"
			<< "---------------------------\n"
			<< "1- Perform Addition\n"
			<< "2- Perform Subtraction\n"
			<< "3- Exit\n\n";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			try
			{
				string n1;
				getline(cin, n1);
				BigDecimalInt num1(n1);
				cout << "num1 = " << num1 << endl;
				string n2;
				getline(cin, n2);
				BigDecimalInt num2(n2);
				cout << "num2 = " << num2 << endl;
				cout << "num1 + num2 = " << num1 + num2 << endl << endl;
			}
			catch (BigDecimalInt::InvalidInput)
			{
				cout << "Error: invalid input was entered for num1 or num2!\n\n";
			}
			break;
		}
		case 2:
		{
			try
			{
				string n1;
				getline(cin, n1);
				BigDecimalInt num1(n1);
				cout << "num1 = " << num1 << endl;
				string n2;
				getline(cin, n2);
				BigDecimalInt num2(n2);
				cout << "num2 = " << num2 << endl;
				cout << "num1 - num2 = " << num1 - num2 << endl << endl;
			}
			catch (BigDecimalInt::InvalidInput)
			{
				cout << "Error: invalid input was entered for num1 or num2!\n";
			}
			break;
		}
		case 3:
			break;
		default:
			cout << "Invalid choice!\n";
			break;
		}
	}
}

