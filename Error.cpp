#include "Error.hpp"

// Constructor
Error::Error( const std::string what ) : err(what) {}

// What happened
const char * Error::what() const throw() {
    return err.c_str();
}
