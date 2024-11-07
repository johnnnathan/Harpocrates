#include <iostream>

class Number {
private:
    int value;

public:
    // Constructor
    Number(unsigned long int v) : value(v) {}

    // Overloading the dereference operator to allow direct access to the value
    int& operator*() {
        return value;  // Return reference to the value
    }

    // Overloading the assignment operator if needed (optional but good practice)
    Number& operator=(const int& v) {
        value = v;
        return *this;
    }

    // You can also overload other operators as needed, for example, the increment operator
    Number& operator++() {
        ++value;
        return *this;
    }

    // Optional: To print the value easily
    void print() const {
        std::cout << value << std::endl;
    }
};
