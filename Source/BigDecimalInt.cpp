#include "BigDecimalInt.h"

void BigDecimalInt::reverseString(string& str)
{
	char temp;
	for (int i = 0; i < str.length() / 2; i++)
	{
		temp = str[i];
		str[i] = str[str.length() - i - 1];
		str[str.length() - i - 1] = temp;
	}
}

void BigDecimalInt::removeLeftZeros(string& str)
{
    if (str[0] == '0')
    {
        int zeroCounter = 1;
        while (str[zeroCounter] == '0')
            zeroCounter++;

        if (zeroCounter == (str.length()))
            str = "0";
        else
            str.erase(0, zeroCounter);
    }

    else if ((str[0] == '-' || str[0] == '+') && str[1] == '0')
    {
        int zeroCounter = 1;
        while (str[zeroCounter + 1] == '0')
            zeroCounter++;
        if (zeroCounter == str.length() - 1)
            str = "0";
        else
            str.erase(1, zeroCounter);
    }
}

bool BigDecimalInt::isValid(string str)
{
	if (!((str[0] >= '0' && str[0] <= '9') || str[0] == '+' || str[0] == '-'))
		throw InvalidInput();
	for (int i = 1; i < str.length(); i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			throw InvalidInput();
	}
	return true;
}

char BigDecimalInt::getSign()
{
    if (number[0] == '-')
        return '-';
    else
        return '+';
}

BigDecimalInt BigDecimalInt::removeSign()
{
    string str = "";
    if (number[0] == '-' || number[0] == '+')
    {
        for (int i = 1; i < number.length(); i++)
        {
            str += number[i];
        }
        return BigDecimalInt(str);
    }
    else
        return *this;
}

// this function is designed to compare the magnitude only
char BigDecimalInt::compare(const BigDecimalInt& b)
{
    if (number.length() == b.number.length())
    {
        for (int i = 0; i < number.length(); i++)
        {
            if (number[i] > b.number[i])
                return '>';
            else if (number[i] < b.number[i])
                return '<';
        }
        return '=';
    }
    else if (number.length() > b.number.length())
        return '>';
    else
        return '<';
}

BigDecimalInt::BigDecimalInt(string decStr)
{
    if (decStr.length() == 0)
        number = decStr;
    else
    {
        if (isValid(decStr))
            number = decStr;
    }
}

BigDecimalInt::BigDecimalInt(int decInt)
{
	number = "";
	if (decInt > 0)
	{
		while (decInt > 0)
		{
			number += decInt % 10 + '0'; // using ASCII code
			decInt /= 10;
		}
	}
	else if (decInt == 0)
		number = '0';
	else
	{
		decInt *= -1;
		while (decInt > 0)
		{
			number += decInt % 10 + '0'; // using ASCII code
			decInt /= 10;
		}
		number += '-';
	}
	reverseString(number);
}

BigDecimalInt BigDecimalInt::operator+(BigDecimalInt anotherDec)
{
    if (this->getSign() == '-' && anotherDec.getSign() == '+')
    {
        return anotherDec - this->removeSign();
    }

    if (this->getSign() == '+' && anotherDec.getSign() == '-')
    {
        return *this - anotherDec.removeSign();
    }

    bool isNegative = this->getSign() == '-' && anotherDec.getSign() == '-';
    BigDecimalInt num1("");
    BigDecimalInt num2("");
    BigDecimalInt result("");
    if (this->removeSign().number.length() < anotherDec.removeSign().number.length())
    {
        num1 = this->removeSign();
        num2 = anotherDec.removeSign();
    }
    else
    {
        num1 = anotherDec.removeSign();
        num2 = this->removeSign();
    } // this way, num2 is always bigger or equals num1, so lengthDiff will be positive or 0
    //and the loop conditions will work properly in all cases.

    int lengthDiff = num2.number.length() - num1.number.length();
    int sum, carry = 0;

    for (int i = (num1.number.length() - 1); i >= 0; i--)
    {
        sum = num1.number[i] + num2.number[i + lengthDiff] - 2 * '0' + carry; // using ASCII code
        carry = 0;
        if (sum > 9)
        {
            sum -= 10;
            carry = 1;
        }
        result.number += sum + '0'; //using ASCII code
    }
    //If both have the same length, this loop will not function.
    for (int i = lengthDiff - 1; i >= 0; i--)
    {
        sum = num2.number[i] - '0' + carry; //using ASCII code
        carry = 0;
        if (sum > 9)
        {
            sum -= 10;
            carry = 1;
        }

        result.number += sum + '0'; //using ASCII code
    }
    if (carry == 1)
    {
        result.number += '1';
    }

    if (isNegative)
    {
        result.number += '-';
    }
    reverseString(result.number);
    return result;
}

BigDecimalInt BigDecimalInt::operator-(BigDecimalInt anotherDec)
{
    if (this->getSign() == '-' && anotherDec.getSign() == '+')
    {
        return anotherDec + ((*this - *this) - *this);// (-a) - (+b) = (-a) + (-b) = (-a) + (b-b-b)
    }
    if (this->getSign() == '+' && anotherDec.getSign() == '-')
    {
        return *this + anotherDec.removeSign();// (+a) - (-b) = (+a) + (+b)
    }
    if (this->getSign() == '-' && anotherDec.getSign() == '-')
    {
        return anotherDec.removeSign() - this->removeSign(); // (-a) - (-b) = (+b) - (+a)
    }

    BigDecimalInt num1("");
    BigDecimalInt num2("");
    BigDecimalInt result("");
    if (this->removeSign().compare(anotherDec.removeSign()) == '>')
    {
        num1 = this->removeSign();
        num2 = anotherDec.removeSign();
    }
    else
    {
        num1 = anotherDec.removeSign();
        num2 = this->removeSign();
    } // this way, num1 is always bigger than num2, so lengthDiff will be positive
    //and the loop conditions will work properly in all cases.

    int lengthDiff = num1.number.length() - num2.number.length();
    int sum, carry = 0;

    for (int i = (num2.number.length() - 1); i >= 0; i--)
    {
        sum = num1.number[i + lengthDiff] - num2.number[i] + carry;
        carry = 0;
        if (sum < 0)
        {
            sum += 10;
            carry--;
        }
        result.number += sum + '0';
    }

    //If both have the same length, this loop will not function.
    for (int i = lengthDiff - 1; i >= 0; i--)
    {
        sum = num1.number[i] + carry - '0';
        carry = 0;
        if (sum < 0)
        {
            sum += 10;
            carry--;
        }

        result.number += sum + '0';
    }

    if (anotherDec.removeSign().compare(this->removeSign()) == '>')
        result.number += '-';

    reverseString(result.number);
    removeLeftZeros(result.number);
    return result;
}

int BigDecimalInt::size()
{
	if (number[0] == '-' || number[0] == '+')
		return number.length() - 1;
	else
	    return number.length();
}

ostream& operator<<(ostream& out, BigDecimalInt b)
{
	out << b.number;
    return out;
}
