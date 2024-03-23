#include "fraction.h"

void Fraction::simplify(){
    sign = 1;                           // Initialize to a positive number
	if(denominator == 0){               // Illegal denominator
        valid = 0;
        cout << "ERROR! The denominator can't be 0!" << endl;
		system("PAUSE");
		exit(0);
    }
    else if(numerator == 0) return;     // If it simplifies to 0
    // To find the common divisor, make numerator and denominator positive
	else if(numerator < 0 && denominator < 0){
		sign = 1;
		numerator = -numerator;
		denominator = -denominator;
	}
	else if(numerator > 0 && denominator < 0){
		sign = -1;
		denominator = -denominator;
	}
	else if(numerator < 0 && denominator > 0){
		sign = -1;
        numerator = -numerator;
	}
	int Common_Divisor = gcd();         // To find the common divisor
    if(Common_Divisor > 1){
        numerator /= Common_Divisor;
        denominator /= Common_Divisor;
    }
    numerator *= sign;                  // Restore the original sign
}

int Fraction::gcd()                     // To find the common divisor
{
    int temp_num = numerator;
    int temp_den = denominator;
    while (temp_num != temp_den){
        if (temp_num > temp_den) temp_num -= temp_den;
        else temp_den -= temp_num;
    }
    return temp_num;
}

Fraction Fraction::operator+(const Fraction& b){    // Additive arithmetic operation
    Fraction c;
    c.numerator = this->numerator * b.denominator + b.numerator * this->denominator;
    c.denominator = this->denominator * b.denominator;
    c.simplify();                                   // Simplify the result
    return c;
}

Fraction Fraction::operator-(const Fraction& b){    // Subtraction arithmetic operation
    Fraction c;
    c.numerator = this->numerator * b.denominator - b.numerator * this->denominator;
    c.denominator = this->denominator * b.denominator;
    c.simplify();
    return c;
}

Fraction Fraction::operator*(const Fraction& b){    // Multiplication arithmetic operation
    Fraction c;
    c.numerator = this->numerator * b.numerator;
    c.denominator = this->denominator * b.denominator;
    c.simplify();
    return c;
}

Fraction Fraction::operator/(const Fraction& b){    // Division arithmetic operation
    Fraction c;
    c.numerator = this->numerator * b.denominator;
    c.denominator = this->denominator * b.numerator;
    if(c.denominator != 0) c.simplify();
    return c;
}

bool Fraction::operator<(const Fraction& b){    // Less-than relation operation
    if(b.denominator * this->denominator > 0)
        return (this->numerator * b.denominator < b.numerator * this->denominator);
    else
        return (this->numerator * b.denominator > b.numerator * this->denominator);
}

bool Fraction::operator<=(const Fraction& b){   // Less than or equal relation operation
    if(b.denominator * this->denominator > 0)
        return (this->numerator * b.denominator <= b.numerator * this->denominator);
    else
        return (this->numerator * b.denominator >= b.numerator * this->denominator);
}

bool Fraction::operator>(const Fraction& b){    // More-than relation operation
    if(b.denominator * this->denominator > 0)
        return (this->numerator * b.denominator > b.numerator * this->denominator);
    else
        return (this->numerator * b.denominator < b.numerator * this->denominator);
}

bool Fraction::operator>=(const Fraction& b){   // More than or equal relation operation
    if(b.denominator * this->denominator > 0)
        return (this->numerator * b.denominator >= b.numerator * this->denominator);
    else
        return (this->numerator * b.denominator <= b.numerator * this->denominator);
}

bool Fraction::operator==(const Fraction& b){    // Equal relation operation
    return (this->numerator * b.denominator == b.numerator * this->denominator);
}

bool Fraction::operator!=(const Fraction& b){    // Not equal to relational operations
    return (this->numerator * b.denominator != b.numerator * this->denominator);
}

string Fraction::strings() const{    // Convert to string
    stringstream s;
    s << numerator << "/" << denominator;
    return s.str();
}
