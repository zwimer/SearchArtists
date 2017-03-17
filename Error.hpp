#ifndef CURLFAILED_H
#define CURLFAILED_H

#include <exception>
#include <string>

// Thrown when curl fails
class Error : public std::exception {
public:

    // Constructors
    explicit Error( const char * what );
    explicit Error( std::string & what );

    // What happened
    const char * what() const throw();

private:

    // Representation
    const std::string err;
};

#endif // CURLFAILED_H
