#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class Fraction {
private:
    int sign;           // The positivity of the fraction
    int valid;          // If the denominator is 0, valid = 0
    int numerator;
    int denominator;

public:
    void initvalid() {valid = 1;}                                           // Initialize to valid=1
    int getvalid() {return valid;}                                          // Get the value of valid
    int getdenominator() {return denominator;}
    int getnumerator() {return numerator;}
    Fraction() : numerator(1), denominator(1) {}                            // Default ctor
    Fraction(int num, int den) : numerator(num), denominator(den) {}        // Ctor with 2 parameters
    Fraction(int num) : numerator(num), denominator(1) {}                   // Ctor with 1 parameter
    Fraction(const Fraction& copy_frac) : numerator(copy_frac.numerator), denominator(copy_frac.denominator) {} // Copy ctor

    // Copy constructor, four arithmetic operations
    Fraction operator+(const Fraction&);
    Fraction operator-(const Fraction&);
    Fraction operator*(const Fraction&);
    Fraction operator/(const Fraction&);
    
    //simplify the fraction
    void simplify();        
    int gcd();   

    // Copy constructor, six relational operators
    bool operator<(const Fraction&);
    bool operator<=(const Fraction&);
    bool operator==(const Fraction&);
    bool operator!=(const Fraction&);
    bool operator>=(const Fraction&);
    bool operator>(const Fraction&);

    // To string
    string strings() const;

    // Typecast to double
    operator double() const {
        return double(numerator) / double(denominator);
    }

    // Inserter and extractor for streams
    friend ostream& operator<<(ostream& os, Fraction& frac) {
        if(frac.numerator == frac.denominator)
            os << "1";                      // Same numerator and denominator, the result is 1
        else if(frac.numerator == 0)
            os << "0";                      // Numerator is 0, the result is 0
        else if(frac.denominator == 1)
            os << frac.numerator;           // Denominator is 1, the result is equal to numerator
        else
            os << frac.numerator << '/' << frac.denominator;  //common result
        return os; 
    }
    friend istream& operator>>(istream& is, Fraction& frac) {
        char delimiter;
        is >> frac.numerator >> delimiter >> frac.denominator;
        if(delimiter != '/'){               // Did not enter as required
            cout << "Sorry! Your input is illegal!" << endl;
            system("PAUSE");
            exit(0);
        }
        return is;
    }

    // Conversion from a finite decimal string
    static Fraction Decimal(const string& decimal_frac) {
        unsigned int decimal_left = decimal_frac.find('.'); 
        // Number of digits to the left of the dot
        unsigned int decimal_right = decimal_frac.length() - decimal_left - 1;
        // Number of digits to the right of the dot
        int numerator = stoi(decimal_frac.substr(0, decimal_left) + decimal_frac.substr(decimal_left + 1));
        // Remove the dot to form the numerator
        int denominator = int(pow(10, decimal_right));
        return Fraction(numerator, denominator);
    }
};

#endif