#ifndef RESULTSWINDOW_HPP
#define RESULTSWINDOW_HPP

#include "main.hpp"

#include <QListWidgetItem>
#include <QDialog>


// Forward declarations
class MainWindow;

/*****************************************************************/
/*                                                               */
/*  Note: The following class MUST be dynamically allocated !!!  */
/*                                                               */
/*****************************************************************/


// Protect the global namespace
namespace Ui {
    class ResultsWindow;
}


// The class that will be the window for the results of a search
class ResultsWindow : public QDialog {
    Q_OBJECT
public:

    // Explicit Constructor, prevent implicit conversion
    explicit ResultsWindow( const MainWindow * p );

    // Constructor: take in string as data
    explicit ResultsWindow( const std::string& who,
                            const std::string& data );

    // Destructor
    ~ResultsWindow();

private slots:

    // Update the display with info from the selected song
    void updateDisplay( int row );

private:

    // Setup the ui
    void setup();

    // Construct listWidget and media
    // Also connect signals and slots
    void finishSetup( const json& artist );

    // Representation
    Ui::ResultsWindow *ui;
    json media;
};

#endif // RESULTSWINDOW_HPP
