#include "fraction.h"
#include <iostream>
using namespace std;

int main() {
    Fraction f0;        // The default constructor makes both the numerator and denominator 1
    cout << "Default ctor f0 = " << f0 << endl;

    Fraction f1(1, 2);  // Pass a constructor with two arguments
    cout << "Ctor f1(1, 2) with 2 parameters f1 = " << f1 << endl;

    Fraction f2(2, 3);  // Fractions are converted to double-precision numbers
    double f2_double = f2;
    cout << "Fraction f2(2, 3) as double: " << f2_double << endl;

    string f2_string = f2.strings();
    cout << "Fraction f2(2, 3) as string: " << f2_string << endl;
    
    Fraction f3(f2);    // Copy construcor function
    cout << "Copy ctor f3(f2) = " << f3 << endl;

    // Convert finite decimal string to fraction
    string str = "1.414";
    Fraction f4 = Fraction::Decimal(str);
    f4.simplify();
    cout << "Fraction from decimal string " << str << ": " << f4 << endl;

    // Read fraction from input stream
    cout << "Enter two fractions in the form 'numerator/denominator': ";
    cin >> f1 >> f2;
    if(f1.getdenominator() == 0 || f2.getdenominator() == 0){
        // Determine whether the two fractions read are valid
        cout << "ERROR! The denominator can't be 0!" << endl;
		system("PAUSE");
		exit(0);
    }
    else{
        f1.initvalid();
        f2.initvalid();
    }

    Fraction sum = f1 + f2;
    Fraction difference = f1 - f2;
    Fraction product = f1 * f2;
    Fraction quotient = f1 / f2;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << difference << endl;
    cout << "Product: " << product << endl;
    if(quotient.getdenominator() != 0) cout << "Quotient: " << quotient << endl; 
    // Output only if the result is legitimate
    else cout << "ERROR! The divisor cannot be 0!" << endl;

    cout << "f1 < f2?" << "\t" << boolalpha << (f1 < f2) << endl;
    cout << "f1 <= f2?" << "\t" << boolalpha << (f1 <= f2) << endl;
    cout << "f1 == f2?" << "\t" << boolalpha << (f1 == f2) << endl;
    cout << "f1 != f2?" << "\t" << boolalpha << (f1 != f2) << endl;
    cout << "f1 >= f2?" << "\t" << boolalpha << (f1 >= f2) << endl;
    cout << "f1 > f2?" << "\t" << boolalpha << (f1 > f2) << endl;

    system("pause");
}