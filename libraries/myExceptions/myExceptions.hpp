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
*   Since this library is the core of all the others, it is designed in order to be used inside the various library functions, however it is avaible for general use.
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
        virtual void print_message() = 0;

};


#endif // MYEXCEPTIONS_HPP