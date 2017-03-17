#include <algorithm>
#include <iostream>
#include <sstream>

// QT
#include <QApplication>

// My files
#include "main.hpp"
#include "MainWindow.hpp"


// Returns true if s is all whitespace
bool isAllSpace(const std::string & s) {
    for(size_t i = 0; i < s.size(); ++i)
        if (!isspace(s[i]))
            return false;
    return true;
}


// Main function
int main(int argc, char * argv[] ) {
    
    // Display the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    // Execute the program
    return a.exec();
}
