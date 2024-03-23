#include "my_vector.h"  // Include the custom Vector header file
#include <stdio.h>
using namespace std;

int main() {
    int i;
    // Create an instance of Vector<int> using the default constructor
    Vector<int> vector1;
    // Print whether vector1 is empty or not
    cout << "Default ctor: If vector1 is empty, print 1; otherwise print 0: " << vector1.empty() << endl;
    // Print the size and capacity of vector1
    cout << "Vector1's size is " << vector1.size() << " , capacity is " << vector1.capacity() << endl;
    // Add elements to vector1 using the push_back() function
    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(3);
    // Print whether vector1 is empty or not after adding elements
    cout << "After push_back 3 elements, if vector1 is empty, print 1; otherwise print 0: " << vector1.empty() << endl;
    // Print the size and capacity of vector1 after adding elements
    cout << "Vector1's size is " << vector1.size() << " , capacity is " << vector1.capacity() << endl;
    // Print the elements of vector1 using the overloaded [] operator
    cout << "Vector1's elements are as follow: ";
    for (i = 0; i < vector1.size(); i++) {
        cout << vector1[i] << " ";
    }
    cout << endl << endl;
    
    // Create an instance of Vector<float> with an initial capacity of 2
    Vector<float> vector_f(2);
    // Add an element to vector_f using the push_back() function
    vector_f.push_back(3.14);
    // Print the elements of vector_f
    cout << "float_vector: ";
    for (i = 0; i < vector_f.size(); i++) {
        cout << vector_f[i] << " ";
    }
    cout << endl;

    // Create an instance of Vector<double> with an initial capacity of 2
    Vector<double> vector_d(2);
    // Add an element to vector_d using the push_back() function
    vector_d.push_back(3.14159265358979);
    // Print the elements of vector_d with precision set to 15 decimal places
    cout << "double_vector: ";
    for (i = 0; i < vector_d.size(); i++) {
        cout << setprecision(15) << vector_d[i] << " ";
    }
    cout << endl;
    
    // Create an instance of Vector<char> with an initial capacity of 2
    Vector<char> vector_c(2);
    // Add an element to vector_c using the push_back() function
    vector_c.push_back('c');
    // Print the elements of vector_c
    cout << "char_vector: ";
    for (i = 0; i < vector_c.size(); i++) {
        cout << vector_c[i] << " ";
    }
    cout << endl;
    
    // Create an instance of Vector<string> with an initial capacity of 2
    Vector<string> vector_s(2);
    // Add an element to vector_s using the push_back() function
    vector_s.push_back("hello world");
    // Print the elements of vector_s
    cout << "string_vector: ";
    for (i = 0; i < vector_s.size(); i++) {
        cout << vector_s[i] << " ";
    }
    cout << endl << endl;
    
    // Create an instance of Vector<int> with an initial capacity of 5
    Vector<int> vector2(5);
    // Print whether vector2 is empty or not
    cout << "Ctor with parameter: If vector2 is empty, print 1; otherwise print 0: " << vector2.empty() << endl;
    // Print the size and capacity of vector2
    cout << "Vector2's size is " << vector2.size() << " , capacity is " << vector2.capacity() << endl;
    // Add an element to vector2 using the push_back() function (triggers capacity expansion)
    vector2.push_back(6);
    // Print the size and capacity of vector2 after adding an element
    cout << "After push_back one element (inflate), the vector2's size is " << vector2.size() << " , capacity is " << vector2.capacity() << endl;
    // Print the elements of vector2
    cout << "Vector2's elements are as follow: ";
    for (i = 0; i < vector2.size(); i++) {
        cout << vector2[i] << ' ';
    }
    cout << endl;
    // Clear vector2
    vector2.clear();
    // Print the size and capacity of vector2 after clearing
    cout << "After clear vector2, the vector2's size is " << vector2.size() << " , capacity is " << vector2.capacity() << endl;
    cout << endl;
    
    // Create a new vector vector3 by copying vector1
    Vector<int> vector3(vector1);
    // Print whether vector3 is empty or not
    cout << "Copy_ctor: If vector3 is empty, print 1; otherwise print 0: " << vector3.empty() << endl;
    // Print the size and capacity of vector3
    cout << "Vector3's size is " << vector3.size() << " , capacity is " << vector3.capacity() << endl;
    // Print the elements of vector3
    cout << "Vector3's elements are as follow: ";
    for (i = 0; i < vector3.size(); i++) {
        cout << vector3[i] << " ";
    }
    cout << endl;
    // Access a legal position in vector3 using the [] operator
    cout << "Use vector3[i] to visit a legal position, for example vector3[2]: " << vector3[2] << endl;
    // Access a legal position in vector3 using the at() function
    cout << "Use vector3.at(i) to visit a legal position, for example vector3.at(2): " << vector3.at(2) << endl;
    // Access an illegal position in vector3 using the [] operator
    cout << "Use vector3[i] to visit an illegal position, for example vector3[5]: " << vector3[5] << endl;
    // Access an illegal position in vector3 using the at() function
    cout << "Use vector3.at(i) to visit an illegal position, for example vector3.at(5): " << vector3.at(5) << endl << endl;
    
    system("pause");
    return 0;
}