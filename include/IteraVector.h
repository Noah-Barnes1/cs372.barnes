#pragma once
#pragma once
#include <iostream>
#include <cstdlib>

template <typename T>
class Vector {
private:
    T* arr;          // pointer to dynamic array
    int vCapacity;   // current allocated capacity
    int length;      // number of elements actually stored

    void expand(int newCapacity) {
        if (newCapacity > vCapacity) {
            T* temp = new T[newCapacity];
            for (int i = 0; i < length; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            vCapacity = newCapacity;
        }
        else {
            std::cerr << "Vector::expand: new capacity must be greater than current\n";
        }
    }

public:
    // ========== Iterator Class ==========
    class Iterator {
    private:
        Vector<T>* vec;  // pointer to owning vector
        int index;       // current index
    public:
        Iterator(Vector<T>* v, int i) : vec(v), index(i) {}

        // Dereference
        T& operator*() { return vec->arr[index]; }

        // Prefix increment
        Iterator& operator++() {
            ++index;
            return *this;
        }

        // Postfix increment
        Iterator operator++(int) {
            Iterator temp = *this;
            ++index;
            return temp;
        }

        // Equality / inequality
        bool operator==(const Iterator& other) const {
            return vec == other.vec && index == other.index;
        }
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    // begin() and end()
    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, length); }

    // ====================================

    // Constructors and destructor
    Vector() {
        arr = new T[1];
        vCapacity = 1;
        length = 0;
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    // Copy constructor
    Vector(const Vector& other) {
        vCapacity = other.vCapacity;
        length = other.length;
        arr = new T[vCapacity];
        for (int i = 0; i < length; i++) {
            arr[i] = other.arr[i];
        }
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr;
            vCapacity = other.vCapacity;
            length = other.length;
            arr = new T[vCapacity];
            for (int i = 0; i < length; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    // Insert or replace element
    void put(T data, int index) {
        if (index < 0) {
            std::cerr << "Vector::put: negative index\n";
            return;
        }
        if (index >= vCapacity) {
            expand(2 * vCapacity);
        }
        if (index == length) {
            push_back(data);
        }
        else {
            arr[index] = data;
        }
    }

    // Add at end
    void push_back(T data) {
        if (length == vCapacity) {
            expand(2 * vCapacity);
        }
        arr[length] = data;
        length++;
    }

    // Access with bounds checking
    T& at(int index) {
        if (index < 0 || index >= length) {
            std::cerr << "Vector::at: index out of bounds\n";
            std::exit(1);
        }
        return arr[index];
    }

    // Size and capacity
    int size() const { return length; }
    int capacity() const { return vCapacity; }

    // Traverse and print
    void traverse() const {
        for (int i = 0; i < length; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Operator overloads
    bool operator==(const Vector& other) const {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++) {
            if (arr[i] != other.arr[i]) return false;
        }
        return true;
    }

    T& operator[](int i) {
        if (i < 0 || i >= length) {
            std::cerr << "Vector::operator[]: index out of bounds\n";
            std::exit(1);
        }
        return arr[i];
    }
};
