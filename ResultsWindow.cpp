#include "ResultsWindow.hpp"
#include "ui_ResultsWindow.h"
#include "MainWindow.hpp"
#include "Search.hpp"
#include "main.hpp"

// QT
#include <QTreeWidgetItemIterator>
#include <QTreeWidgetItem>

// STL
#include <set>


/*****************************************************************/
/*                                                               */
/*                      Forward declarations                     */
/*                                                               */
/*****************************************************************/


// Given a track, format the name and when it was made
inline const QString format(const json & j);

// Convert a json's 'string' to a QString
inline const QString toQ(const json & j);


/*****************************************************************/
/*                                                               */
/*                ResultsWindow class definition                 */
/*                                                               */
/*****************************************************************/


// Constructor
ResultsWindow::ResultsWindow( const MainWindow * p ) :
    QDialog( nullptr ), ui(new Ui::ResultsWindow) {

    // Setup the ui
    ui->setupUi(this);

    // Setup the tableWidget
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(
                QString("Category;Information").split(";") );

    // Get selected artist, set window title to him
    std::string artist = p->getArtist();
    setWindowTitle( QObject::tr("Media by: ") + QObject::tr(artist.c_str()) );

    // Search for the selected artist
    json js = search( artist );
    int n = js["resultCount"];
    media = js["results"];

    // Populate the list widget
    for(int i = 0; i < n; i++) {
        ui->listWidget->addItem( format(media[i]) );
    }

    // Connect selecting an item to display it's information
    QObject::connect( ui->listWidget, SIGNAL(currentRowChanged( int )),
                      this, SLOT( updateDisplay( int ) ) );
}

// Destructor, prevent leaks
ResultsWindow::~ResultsWindow() {
    delete this;
}


// Update the display with info from the selected song
void ResultsWindow::updateDisplay( int row ) {

    // Error checking
    if (row < 0) return;

    // For clarity
    const json & track = media[ row ];

    // Clear the tableWidget
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(
                QString("Category;Information").split(";") );

    // For each element in media[i], add it to the tableWidget
    for (json::const_iterator i = track.begin(); i != track.end(); ++i) {

        // Create category and information containing i
        auto * newLeft = new QTableWidgetItem( toQ(i.key()) );
        auto * newRight = new QTableWidgetItem( toQ(i.value()));

        // Add new items to the tableWidget
        const int n = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow( n );
        ui->tableWidget->setItem( n, 0, newLeft );
        ui->tableWidget->setItem( n, 1, newRight );
    }

    // Resize the table as needed
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}


/*****************************************************************/
/*                                                               */
/*             Define functions used in ResultsWindow            */
/*                                                               */
/*****************************************************************/


// Format a given date
inline const std::string formatDate( const std::string& d ) {

    // Error checking
    if (d.size() < 6) return "NA";
    if (d.find("T") == std::string::npos) return "NA";

    // Return the formatted date
    return std::move(
                std::string(d.substr(5, d.find("T") - 5))
                + std::string("-")
                + d.substr(0,4)
            );
}

// Given a track, format the name and when it was made
inline const QString format(const json & j) {

    // Format the return string
    std::stringstream s;
    s << formatDate(j["releaseDate"]) << " : " << j["trackName"];

    // Return it
    return std::move( QObject::tr( s.str().c_str() ) );
}

// Convert a json's 'string' to a QString
inline const QString toQ(const json & j) {

    // Convert j to a string
    std::stringstream s; s << j;
    std::string ret = s.str();

    // Remove unneeded "s if needed
    if (ret.size()) if (ret[0] == '\"') ret.erase(0, 1);
    if (ret.size()) if (ret[ret.size()-1] == '\"') ret.pop_back();

    // Return the string as a QString
    return std::move( QObject::tr(ret.c_str()) );
}
