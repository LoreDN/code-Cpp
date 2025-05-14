// including external libraries
#include <iostream>

// library definition
#include "myExceptions.hpp"


/* -------------------------------------------------------------------------------- ROOT. myException ------------------------------------------------------------------------------- */

// constructor
myException::myException(std::string msg) : message(msg) {}