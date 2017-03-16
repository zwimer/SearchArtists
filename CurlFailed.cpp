#include "CurlFailed.hpp"

// Constructor
CurlFailed::CurlFailed( const std::string what ) : err(what) {}

// What happened
const char * CurlFailed::what() const throw() {
    return err.c_str();
}
