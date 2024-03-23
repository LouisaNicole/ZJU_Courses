#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

template <class T>
class Vector {
public:
    Vector();                      // creates an empty vector
    Vector(int size);              // creates a vector for holding 'size' elements
    Vector(const Vector& r);       // the copy ctor
    ~Vector();                     // destructs the vector 
    T& operator[](int index);      // accesses the specified element without bounds checking
    T& at(int index);              // accesses the specified element, throws an exception of
                                   // type 'out_of_range' when index <0 or >=m_nSize
    int size() const;              // return the size of the container
    int capacity() const;
    void push_back(const T& x);    // adds an element to the end 
    void clear();                  // clears the contents
    bool empty() const;            // checks whether the container is empty 
private:
    void inflate();                // expand the storage of the container to a new capacity,
                                   // e.g. 2*m_nCapacity
    T *m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the total number of elements that can be held in the
                                   // allocated storage
};

template <class T>
Vector<T>::Vector() {              // Implementation of the default constructor
    m_nSize = 0;
    m_nCapacity = 0;
    m_pElements = nullptr;
}

template <class T>
Vector<T>::Vector(int size) {      // Implementation of the constructor that creates a vector with a specified size
    m_nSize = size;
    m_nCapacity = size;
    m_pElements = new T[m_nCapacity];
    for (int i = 0; i < m_nSize; i++) {
        m_pElements[i] = T();      // Initialize array elements with default values (0 for primitive types)
    }
}

template <class T>
Vector<T>::Vector(const Vector& r) {  // Implementation of the copy constructor
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    m_pElements = new T[r.m_nCapacity];

    for (int i = 0; i < m_nSize; i++) {
        m_pElements[i] = r.m_pElements[i];
    }
}

template <class T>
Vector<T>::~Vector() {             // Implementation of the destructor
    delete[] m_pElements;
}

template <class T>
T& Vector<T>::operator[](int index) { // Implementation of the overloaded operator for accessing elements without bounds checking
    return m_pElements[index];
}

template <class T>
T& Vector<T>::at(int index) {      // Implementation of the function for accessing elements with bounds checking
    if (index < 0 || index >= m_nSize) {
        throw "std::out of range"; // Throw an exception if the index is out of range
    }
    return m_pElements[index];
}

template <class T>
int Vector<T>::size() const {      // Implementation of the function to return the size of the container
    return m_nSize;
}

template <class T>
int Vector<T>::capacity() const {  // Implementation of the function to return the capacity of the container
    return m_nCapacity;
}

template <class T>
void Vector<T>::push_back(const T& x) {  // Implementation of the function to add an element to the end of the container
    if (m_nSize == m_nCapacity) {
        inflate();                 // Expand the storage if the container is full
    }
    m_pElements[m_nSize] = x;
    m_nSize++;
}

template <class T>
void Vector<T>::clear() {          // Implementation of the function to clear the contents of the container
    m_nSize = 0;
}

template <class T>
bool Vector<T>::empty() const {    // Implementation of the function to check whether the container is empty
    if (m_nSize == 0) {
        return true;
    }
    return false;
}

template <class T>
void Vector<T>::inflate() {        // Implementation of the private function to expand the storage of the container
    int new_capacity;
    if (m_nCapacity == 0) {
        new_capacity = 1;
    }
    else {
       new_capacity = m_nCapacity * 2;
    }
    T* new_Elements = new T[new_capacity];
    for (int i = 0; i < m_nSize; i++) {
        new_Elements[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = new_Elements;
    m_nCapacity = new_capacity;
}

#endif