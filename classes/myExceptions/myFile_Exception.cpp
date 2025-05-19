// including external libraries
#include <iostream>
#include <fstream>


/* ------------------------------------------------------------------------------- 2. myFile_Exception ------------------------------------------------------------------------------ */


class myFile_Exception : public myException {

    private:

        // attributes
        std::string path;

    public:

        // constructor
        myFile_Exception(std::string name, std::string msg) : myException(msg), path(name) {}

        // methods
        void print() {

            // print the message
            std::cout << std::endl << std::endl << this->message << std::endl;
            std::cout << "The file " << this->path << " cannot be opened correctly" << std::endl;

            // exit
            exit(-1);

        }

};


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