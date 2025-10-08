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

    if (index > limit) { throw myIndex_Exception(index, "!!! Index Exception !!!"); }
    return;

}


/* ----------------------------------------------------------------------------- 2. myDataSize_Exception ---------------------------------------------------------------------------- */


// constructor
myDataSize_Exception::myDataSize_Exception(size_t sz, std::string msg) : myException(msg), size(sz) {}


// Method --- Print the error message
void myDataSize_Exception::print() {

    // print the message
    std::cout << std::endl << std::endl << this->message << std::endl;
    std::cout << "The Data-Structure of size " << this->size << " will be resized!" << std::endl;

    // exit
    return;

}


// Test 1 --- Test myDataSize_Exception
void test_data_size(size_t size, size_t limit) {

    if (size >= limit) { throw myDataSize_Exception(size, "!!! Data Size Exception !!!"); }
    return;

}


/* ------------------------------------------------------------------------------- 3. myFile_Exception ------------------------------------------------------------------------------ */


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

    if (!(*file).is_open()) { throw myFile_Exception(path, "!!! Reading File Exception !!!"); }
    return;

}


// Test 2 --- 2 --- Test myFile_Exception with fstream
void test_outfile(std::string path, std::ofstream *file) {

    if (!(*file).is_open()) { throw myFile_Exception(path, "!!! Writing File Exception !!!"); }
    return;

}


// Test 2 --- 3 --- Test myFile_Exception with fstream
void test_iofile(std::string path, std::fstream *file) {

    if (!(*file).is_open()) { throw myFile_Exception(path, "!!! Reading / Writing File Exception !!!"); }
    return;

}