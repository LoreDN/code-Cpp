// including external libraries
#include <iostream>

// library definition
#include "myExceptions.hpp"


/* -------------------------------------------------------------------------------- ROOT. myException ------------------------------------------------------------------------------- */


// constructor
myException::myException(std::string msg) : message(msg) {}


/* ------------------------------------------------------------------------------ 1. myIndex_Exception ------------------------------------------------------------------------------ */


// constructor
myIndex_Exception::myIndex_Exception(size_t idx, std::string msg) : index(idx), myException(msg) {}


// Method 1 --- Print the error message
void myIndex_Exception::print() {

    // print the message
    std::cout << std::endl << std::endl << this->message << std::endl;
    std::cout << "The index " << this->index << " is out of range" << std::endl;

    // exit
    exit(-1);

}


// Test 1 --- Test myIndex_Exception
void test_index(size_t index, size_t limit) {

    // test the exception
    if (index > limit) {

        throw myIndex_Exception(index,"!!! Index Exception !!!");

    }

    // exit
    return;

}