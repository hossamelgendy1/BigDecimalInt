#include <iostream>
#include <string>
using namespace std;

class BigDecimalInt
{
private: 
	string number;
	void reverseString(string& str);
	void removeLeftZeros(string& str);
	bool isValid(string str);
	char getSign();
	BigDecimalInt removeSign();
	char compare(const BigDecimalInt& b);
public:
	BigDecimalInt(string decStr); // Initialize from string and rejects bad input
	BigDecimalInt(int decInt); // Initialize from integer
	BigDecimalInt operator+ (BigDecimalInt anotherDec);
	BigDecimalInt operator- (BigDecimalInt anotherDec);
	int size();
	friend ostream& operator << (ostream& out, BigDecimalInt b);
	//Exception class
	class InvalidInput{};
};

