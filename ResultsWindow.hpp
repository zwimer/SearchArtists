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

    // Destructor
    ~ResultsWindow();

private slots:

    // Update the display with info from the selected song
    void updateDisplay( int row );

private:

    //Representation
    Ui::ResultsWindow *ui;
    json media;
};

#endif // RESULTSWINDOW_HPP
