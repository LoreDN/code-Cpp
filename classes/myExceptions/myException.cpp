// including external libraries
#include <iostream>


/* -------------------------------------------------------------------------------- ROOT. myException ------------------------------------------------------------------------------- */


class myException {

    protected:

        // attributes
        std::string message;

    public:

        // constructor
        myException(std::string msg) : message(msg) {}

        // methods prototypes
        virtual void print() = 0;

};