// library definition
#ifndef MYEXCEPTIONS_HPP
#define MYEXCEPTIONS_HPP

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*
*  This library is used as the core for other libraries, here are defined all custom exceptions taht can be found in the other libarries of the repository.ADJ_OFFSET_SINGLESHOT
*  In particular is defined the class "myException", which is an abstract class used as the root from where all the other exceptions descend.
*  Are also defined some functions, used in order to catch the various exceptions.
*
*
*  |-----** IMPORTANT!!! **-----|
*  Since this library is the core of all the others, it is designed in order to be used inside the various library functions, however it is avaible for general use.
*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */





// including external libraries
#include <iostream>


/* -------------------------------------------------------------------------------- ROOT. myException ------------------------------------------------------------------------------- */

class myException {

    protected:

        // attributes
        std::string message;

    public:

        // constructor
        myException(std::string msg);

        // methods prototypes
        virtual void print() = 0;

};

/* ------------------------------------------------------------------------------ 1. myIndex_Exception ------------------------------------------------------------------------------ */

class myIndex_Exception : public myException {

    private:

        // attributes
        size_t index;

    public:

        // constructor
        myIndex_Exception(size_t idx, std::string msg);

        // methods prototypes
        void print() override;

};

void test_index(size_t index, size_t limit);

/* ----------------------------------------------------------------------------- 2. myDataSize_Exception ---------------------------------------------------------------------------- */

class myDataSize_Exception : public myException {

    private:

        // attributes
        size_t size;

    public:

        // constructor
        myDataSize_Exception(size_t dim, std::string msg);

        // methods prototypes
        void print() override;

};

void test_data_size(size_t size, size_t limit);

/* ------------------------------------------------------------------------------- 3. myFile_Exception ------------------------------------------------------------------------------ */

class myFile_Exception : public myException {

    private:

        // attributes
        std::string path;

    public:

        // constructor
        myFile_Exception(std::string name, std::string message);

        // methods prototypes
        void print() override;

};

void test_infile(std::string path, std::ifstream *file);
void test_outfile(std::string path, std::ofstream *file);
void test_iofile(std::string path, std::fstream *file);


#endif // MYEXCEPTIONS_HPP