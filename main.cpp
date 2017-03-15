#include <algorithm>
#include <iostream>
#include <sstream>

// QT
#include <QApplication>

// My files
#include "main.hpp"
#include "MainWindow.hpp"


// Main function
int main(int argc, char * argv[] ) {
    
    // Display the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    // Execute the program
    return a.exec();
}
