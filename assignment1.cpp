//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

//////////////////////////////////////////////////////////////
//
//			Some common functions
//
//////////////////////////////////////////////////////////////
int intConverter(digitList *head){
	digitList *temp = head;
	if(temp == NULL)
		return 0;
	return temp->digit + 10*intConverter(temp->nextDigit);
}

digitList *factorial(int n){
	int k = n;
	if(n == 1)
		return new digitList(1, NULL);
	Integer *temp = new Integer(1, new digitList(n, NULL));
	return (temp->operator*(Integer(factorial(n - 1)))).digits;
}

digitList *exponent(digitList *head, int n){
	if(n == 0)
		return new digitList(1, NULL);
	Integer *temp = new Integer(head);
	return (temp->operator*(Integer(exponent((head), n - 1)))).digits;
}
digitList *digitize(char str[80])
{
	digitList*	L = 0;
	digitList*	node;

	int i;
	
	for(i = 0; i< strlen(str); i++)
	{
		if(str[i] < '0' || str[i] > '9'){
			if(str[i] == '!'){
				int n = intConverter(L);
				return factorial(n);
			}
			else if(str[i] == '^'){
				i++;
				string s;
				while(str[i] != '\0'){
					s += str[i];
					i++;
				}
				int n = stoi(s);
				return exponent(L, n);
			}
			break;
		}
		node = new digitList(str[i] - '0', L);
		L = node;
	}

	return L;

}

digitList *trimDigitList(digitList* L)
{
	if(L->nextDigit != NULL)
		L->nextDigit = trimDigitList(L->nextDigit);
	if(L->digit == 0 && L->nextDigit == NULL){
		delete L;
		return NULL;
	}
	return L;
}

digitList *subDigitLists(int b, digitList* L1, digitList* L2)
{
	// int compareResult = compareDigitLists(L1, L2);
	// if(compareResult == 1){
	// 	return subDigitListsRec(b, L1, L2);
	// }
	// else if (compareResult == -1){
	// 	return subDigitListsRec(b, L2, L1);
	// }
	// else{
	// 	return new digitList(0, NULL);
	// }
	if((L1 == NULL) & (L2 == NULL))	return digitize(b);
	else if(L2 == NULL)					
	{
		int t = L1->getDigit() - b;
		return new digitList(t % radix, subDigitLists( t / radix, L1->getNextDigit(), NULL));
	}
	else
	{
		int t;
		if(L1->getDigit() >= L2->getDigit() + b)
			t = L1->getDigit() - L2->getDigit() - b;
		else
			t = L1->getDigit() - L2->getDigit() - b + radix*2;
		return new digitList(t % radix, subDigitLists( t / radix, L1->getNextDigit(), L2->getNextDigit()));
	}
}

// digitList *subDigitListsRec(int b, digitList *L1, digitList *L2){
// 	if((L1 == NULL) & (L2 == NULL))	return digitize(b);
// 	else if(L2 == NULL)					
// 	{
// 		int t = L1->getDigit() - b;
// 		return new digitList(t % radix, addDigitLists( t / radix, L1->getNextDigit(), NULL));
// 	}
// 	else
// 	{
// 		int t;
// 		if(L1->getDigit() >= L2->getDigit() + b)
// 			t = L1->getDigit() - L2->getDigit();
// 		else
// 			t = L1->getDigit() - L2->getDigit() - b + radix*2;
// 		return new digitList(t % radix, subDigitLists( t / radix, L1->getNextDigit(), L2->getNextDigit()));
// 	}
// }

Integer computeValue(int operatorNum)
{
	Integer		L1, L2;

	L1 = operandArr[0];

	for(int i = 0; i<operatorNum; i++)
	{
		L2 = operandArr[i+1];
		switch(operatorArr[i])
		{
		case '+':
			L1 = L1 + L2;
			break;
		case '-':
			L1 = L1 - L2;
			break;	
		case '*':
			L1 = L1 * L2;
		break;		
		}
	}
	
	return L1;
}
///////////////////////////////////////////////////////////////////////////
//
//		Some methods of Integer class
//
////////////////////////////////////////////////////////////////////
Integer Integer::operator +(Integer L)
{
	// if(sign == L.sign)
	// 	return Integer(sign, addDigitLists(0, digits, L.digits));
	Integer *temp = new Integer(sign, this->digits);
	if(sign != L.sign){
		if(sign == 1){
			int compareResult = compareDigitLists(digits, L.digits);
			if(compareResult == 1){
				return (Integer(1, subDigitLists(0, digits, L.digits))).trimDigit();
			}
			else if (compareResult == -1){
				return (Integer(-1, subDigitLists(0, L.digits, digits))).trimDigit();
			}
			else
				return (Integer(1, new digitList(0, NULL))).trimDigit();
			}
		else{
			int compareResult = compareDigitLists(digits, L.digits);
			if(compareResult == 1){
				return (Integer(1, subDigitLists(0, digits, L.digits))).trimDigit();
			}
			else if (compareResult == -1){
				return (Integer(1, subDigitLists(0, L.digits, digits))).trimDigit();
			}
			else
				return (Integer(1, new digitList(0, NULL))).trimDigit();
			}
		}
	return Integer(sign, addDigitLists(0, digits, L.digits));
}

Integer Integer::operator -(Integer L)
{
	int compareResult = compareDigitLists(digits, L.digits);

	if(sign == L.sign){
		if(sign == 1){
			if(compareResult == 1){
				return (Integer(1, subDigitLists(0, digits, L.digits))).trimDigit();
			}
			else if (compareResult == -1){
				return (Integer(-1, subDigitLists(0, L.digits, digits))).trimDigit();
			}
			else
				return (Integer(1, new digitList(0, NULL))).trimDigit();
			}
		else if(sign == -1){
			if(compareResult == 1){
                return (Integer(-1, subDigitLists(0, digits, L.digits))).trimDigit();
            }
            else if (compareResult == -1){
                return (Integer(1, subDigitLists(0, L.digits, digits))).trimDigit();
            }
            else
                return (Integer(-1, new digitList(0, NULL))).trimDigit();
        }
	}
	else if(sign != L.sign){
		if(sign == -1)
			return (Integer(-1, addDigitLists(0, digits, L.digits))).trimDigit();
		else
			return (Integer(1, addDigitLists(0, digits, L.digits))).trimDigit();
	}
	return (Integer(1, subDigitLists(0, digits, L.digits))).trimDigit();
}

Integer Integer::leftDigits(int n)
{
	return Integer(sign, digits->leftDigits(n));
}

Integer Integer::rightDigits(int n)
{
	return Integer(sign, digits->rightDigits(n));
}

Integer	Integer::shift(int n)
{
	if(n == 0)
		return this->copy();

	digitList *L = new digitList(0, this->digits);
	this->digits = L;
	return shift(n-1);
}

digitList* reverseShift(int n, digitList *head){
	digitList *temp = head;
	while(temp->nextDigit != NULL){
		temp = temp->nextDigit;
	}
	for (int i = 0; i < n; i++){
		temp->nextDigit = new digitList(0, NULL);
		temp = temp->nextDigit;
	}
	return head;
}

Integer Integer::operator *(Integer Y)
{	
	int xLength = this->length();
	int yLength = Y.length();

	if(xLength == 1)
		if(this->digits->digit == 0)
			return Integer(0, this->digits);
	if(yLength == 1)
		if(Y.digits->digit == 0)
			return Integer(0, Y.digits);

	if(xLength == yLength && xLength == 1)
		return Integer(sign, digitize(this->digits->digit * Y.digits->digit));
	
	if(xLength > yLength)
		Y.digits = reverseShift(xLength - yLength, Y.digits);
		// Y = Y.shift(xLength - yLength);
	else if(yLength > xLength){
		Integer temp = this->copy();
		int tempLength = xLength;
		xLength = yLength;
		yLength = tempLength;
		this->digits = Y.digits;
		this->sign = Y.sign;
		// Y = temp.shift(xLength - yLength);
		Y.digits = reverseShift(xLength - yLength, temp.digits);
	}

	Integer xLeft = this->leftDigits(xLength/2);
	Integer yLeft = Y.leftDigits(xLength/2);
	int xTop;
	
	if(xLength % 2 != 0)
		xTop = xLength/2 + 1;
	else xTop = xLength/2;

	Integer xRight = this->rightDigits(xTop);
	Integer yRight = Y.rightDigits(xTop);

	Integer xLyL = xLeft.operator*(yLeft);
	Integer xRyL = xRight.operator*(yLeft);
	Integer xLyR = xLeft.operator*(yRight);
	Integer xRyR = xRight.operator*(yRight);
	Integer xyOP = xRyL.operator+(xLyR);
	Integer xyOP10 = xyOP.shift(xLength/2);
	Integer xRyR100 = xRyR.shift((xLength/2)*2);
	Integer result = xLyL.operator+(xyOP10).operator+(xRyR100);
	if(sign != Y.sign)
		return Integer(-1, result.trimDigit().digits);
	return result.trimDigit();
	// return ((xLeft.operator*(yLeft))
		// 		.operator+(((xRight.operator*(yLeft))
		// 		.operator+(xLeft.operator*(yRight))).shift(xLength/2)))
		// 		.operator+((xRight.shift(xLength*2)).operator*(yRight));
	// }
	// else{
	// 	Integer xLyL = xLeft.operator*(yLeft);
	// 	Integer xRyL = xRight.operator*(yLeft);
	// 	Integer xLyR = xLeft.operator*(yRight);
	// 	Integer xRyR = xRight.operator*(yRight);
	// 	Integer xyOP = xRyL.operator+(xLyR);
	// 	Integer xyOP10 = xyOP.shift(xTop);
	// 	Integer xRyR10 = xRyR.shift(2*xTop);
	// 	return Integer(1, (xLyL.operator+(xyOP10).operator+(xRyR10)).digits);
	// }
		// return Integer(-1, (((xLeft.operator*(yLeft))
		// 					.operator+(((xRight.operator*(yLeft)).operator+(xLeft.operator*(yRight))).shift(xLength/2)))
		// 					.operator+((xRight.shift(xLength*2)).operator*(yRight))).digits);
}
