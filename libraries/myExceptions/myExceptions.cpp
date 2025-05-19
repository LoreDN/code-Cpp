// including external libraries
#include <iostream>
#include <fstream>

// library definition
#include "myExceptions.hpp"


/* -------------------------------------------------------------------------------- ROOT. myException ------------------------------------------------------------------------------- */


myException::myException(std::string msg) : message(msg) {}


/* ------------------------------------------------------------------------------ 1. myIndex_Exception ------------------------------------------------------------------------------ */


// constructor
myIndex_Exception::myIndex_Exception(size_t idx, std::string msg) : myException(msg), index(idx) {}


// Method --- Print the error message
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

        throw myIndex_Exception(index, "!!! Index Exception !!!");

    }

    // exit
    return;

}


/* ------------------------------------------------------------------------------- 2. myFile_Exception ------------------------------------------------------------------------------ */


// constructor
myFile_Exception::myFile_Exception(std::string name, std::string msg) : myException(msg), path(name) {}


// Method --- Print the error message
void myFile_Exception::print() {

    // print the message
    std::cout << std::endl << std::endl << this->message << std::endl;
    std::cout << "The file " << this->path << " cannot be opened correctly" << std::endl;

    // exit
    exit(-1);

}


// Test 2 --- 1 --- Test myFile_Exception with ifstream
void test_infile(std::string path, std::ifstream *file) {

    // test the exception
    if (!(*file).is_open()) {

        throw myFile_Exception(path, "!!! Reading File Exception !!!");

    }

    // exit
    return;

}


// Test 2 --- 2 --- Test myFile_Exception with fstream
void test_outfile(std::string path, std::ofstream *file) {

    // test the exception
    if (!(*file).is_open()) {

        throw myFile_Exception(path, "!!! Writing File Exception !!!");

    }

    // exit
    return;

}


// Test 2 --- 3 --- Test myFile_Exception with fstream
void test_iofile(std::string path, std::fstream *file) {

    // test the exception
    if (!(*file).is_open()) {

        throw myFile_Exception(path, "!!! Reading / Writing File Exception !!!");

    }

    // exit
    return;

}