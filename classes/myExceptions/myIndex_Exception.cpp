// including external libraries
#include <iostream>

/* ------------------------------------------------------------------------------ 1. myIndex_Exception ------------------------------------------------------------------------------ */

class myIndex_Exception : public myException {

    private:

        // attributes
        size_t index;

    public:

        // constructor
        myIndex_Exception(size_t idx, std::string msg) : myException(msg), index(idx) {}
        
        // methods
        void print() {

            // print the message
            std::cout << std::endl << std::endl << this->message << std::endl;
            std::cout << "The index " << this->index << " is out of range" << std::endl;

            // exit
            exit(-1);

        }

};


// Test 1 --- Test myIndex_Exception
void test_index(size_t index, size_t limit) {

    // test the exception
    if (index > limit) {

        throw myIndex_Exception(index, "!!! Index Exception !!!");

    }

    // exit
    return;

}