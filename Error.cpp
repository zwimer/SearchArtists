#include "Error.hpp"

// Constructor
Error::Error( const char * what ) : err(what) {}
Error::Error( std::string & what ) : err(std::move(what)) {}

// What happened
const char * Error::what() const throw() {
    return err.c_str();
}
