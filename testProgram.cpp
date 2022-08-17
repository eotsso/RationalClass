/*

9.15 (Rational Class)

Create a class called `Rational` for performing arithmetic with fractions. 
Write a program to test your class.

Use integer variables to represent private data of the class--the numerator and the denominator. 

Provide a constructor that enables an object of this class to be initialized when it's declared. 
The constructor should contain default values in case no initializers are provided and should store the fraction in reduced form. 
For example, 2/4 should be stored as 1 in the numerator, and 2 in the denominator. 

Provide a public member functions that perform each of the following tasks:

a) Adding two Rational numbers. The result stored in reduced.
b) Subtracting two Rational numbers. The result stored in reduced.
c) Multiplying two Rational numbers. The result stored in reduced.
d) Dividing two Rational numbers. The result stored in reduced.
Printing Rational numbers in form a/b. 
f) Printing rational numbers in floating-point format. 


*/

#include <iostream>
#include <iomanip>
#include <cmath> // abs() function 
using namespace std;

class Rational 
{
public:
	
	Rational();      //default constructor
	Rational(int, int);    //constructor int, int parameter 
	~Rational() { } // inline default destructor 
	
	
	int getNum() const { return numerator; }
	void setNum(int x) { numerator = x; }

	int getDen() const { return denominator; }
	void setDen(int y) { denominator = (y != 0) ? y : 1; }		
	
	void Print() const; 
	void printFloat(); 
	
	Rational Reduction(Rational &); //reduction function prototype--pass by reference
	
	Rational operator+(Rational &); // overloaded +
	Rational operator-(Rational &); // overloaded -
	Rational operator*(Rational &); // overloaded *
	Rational operator/(Rational &); // overloaded /
	
private:
	int numerator;
	int denominator; 
	int greatestDiv(int, int); // helper function 

};

/************************************************************/
Rational::Rational():     //default values 
numerator(0), denominator(1)
{ }

Rational::Rational(int x, int y)
{
	///Store numbers in reduced form inside constructor
	int g; 
	g = greatestDiv(x, y);
	x = x / g;
	y = y / g;
	
	setNum(x); 
	setDen(y);		
}

void Rational::Print() const 
{
	cout << numerator << "/" << denominator;
}

void Rational::printFloat() 
{
	double doubleVal; 
	doubleVal = (double)numerator / denominator;
	cout << fixed << setprecision(3) << doubleVal; 
}

int Rational::greatestDiv(int x, int y)     // ONLY WORKS FOR NON-NEGATIVE NUMBERS....?
{
	while(abs(x) != abs(y))          //Euclid's 
	{
		if (abs(y) > abs(x))
			y = y - x;
		else
			x = x - y; 
	}	
	
	return x;
	
}

Rational Rational::Reduction(Rational &rhs) 
{
	int g;
	g = greatestDiv(rhs.getNum(), rhs.getDen()); 
	
	rhs.numerator = rhs.numerator / g; 
	rhs.denominator = rhs.denominator / g;
	
}

Rational Rational::operator+(Rational &rhs) //returns an object with both left and right objects added for numerator
{
	/********Equalizes for addition and subtraction ***********/
	int b; 
	b = denominator; 
	
	numerator = numerator * rhs.denominator; 
	denominator = denominator * rhs.denominator; 
	
	rhs.numerator = rhs.numerator * b; 
	rhs.denominator = rhs.denominator * b;
	/********************************************************/
	
	Rational fractionTotal; 
	fractionTotal.numerator = numerator + rhs.numerator; 
	fractionTotal.denominator = denominator; // unchanged
	
	Reduction(fractionTotal); 
	
	return fractionTotal; 
}

Rational Rational::operator-(Rational &rhs)
{
	/********Equalizes for addition and subtraction ***********/
	int b; 
	b = denominator; 
	
	numerator = numerator * rhs.denominator; 
	denominator = denominator * rhs.denominator; 
	
	rhs.numerator = rhs.numerator * b; 
	rhs.denominator = rhs.denominator * b;
	/********************************************************/
	
	Rational fractionTotal; 	
	fractionTotal.numerator = numerator - rhs.numerator; 
	fractionTotal.denominator = (denominator != 0) ? denominator : 11111; //checks for 0, if 0, prints 11111 


	Reduction(fractionTotal); 
	
	return fractionTotal; 
}

Rational Rational::operator*(Rational &rhs)
{
	Rational fractionTotal; 	
	fractionTotal.numerator = numerator * rhs.numerator;
	fractionTotal.denominator = denominator * rhs.denominator; 
	
	Reduction(fractionTotal); 

	return fractionTotal; 
}

Rational Rational::operator/(Rational &rhs)
{	
	Rational fractionTotal;
	fractionTotal.numerator = numerator * rhs.denominator; 
	fractionTotal.denominator = denominator * rhs.numerator; 
	
	Reduction(fractionTotal);
	
	return fractionTotal;
	
	
}




/********************mainDriver***********************************************/

int main()
{
	int a, b, c, d;
	a = 30;
	b = 20;
	c = 10; 
	d = 50; 
	
	{
		Rational ratOne(a, b), ratTwo(c, d), ratThree; 
		ratThree = ratOne + ratTwo; 
		
		cout << "The value when adding Rational (" << a << ", " << b << ") and Rational (" << c << ", " << d << ") in its reduced form is:  ";
		ratThree.Print();
		cout << '\n' << "The corresponding float value is: ";
		ratThree.printFloat();
		cout << "\n\n";
	}
	
	{
		Rational ratOne(a, b), ratTwo(c, d), ratThree;  
		ratThree = ratOne - ratTwo; 
		
		cout << "The value when subtracting Rational (" << a << ", " << b << ") and Rational (" << c << ", " << d << ") in its reduced form is: ";
		ratThree.Print();
		cout << '\n' << "The corresponding float value is: ";
		ratThree.printFloat();
		cout << "\n\n";
	}	
	
	{
		Rational ratOne(a, b), ratTwo(c, d), ratThree;  
		ratThree = ratOne * ratTwo; 
		
		cout << "The value when multiplying Rational (" << a << ", " << b << ") and Rational (" << c << ", " << d << ") in its reduced form is: ";
		ratThree.Print();
		cout << '\n' << "The corresponding float value is: ";
		ratThree.printFloat();
		cout << "\n\n";
	}	
	
	{
		Rational ratOne(a, b), ratTwo(c, d), ratThree;  
		ratThree = ratOne / ratTwo; 
		
		cout << "The value when dividng Rational (" << a << ", " << b << ") and Rational (" << c << ", " << d << ") in its reduced form is: ";
		ratThree.Print();
		cout << '\n' << "The corresponding float value is: ";
		ratThree.printFloat();
		cout << "\n\n";
	}			
	
	return 0;

}



