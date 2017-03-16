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
/*                    Forwdward declearations                    */
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

    // Setup the treeWidget
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(
                QStringList() << QObject::tr("Track Information")
    );

    // TODO: check if getArtist is a valid artist !!!

    // Search for the selected artist
    json js = search( p->getArtist() );
    int n = js["resultCount"];
    media = js["results"];

    // Populate the list widget and itmToSong
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

    // For clarity
    const json & track = media[ row ];

    // Record expanded items
    std::set< QString > expanded;
    for(QTreeWidgetItemIterator i(ui->treeWidget); *i; ++i) {
        if ((*i)->isExpanded()) expanded.insert((*i)->text(0));
    }

    // Clear the treeWidget
    ui->treeWidget->clear();

    // For recording the track name
    QString trackName = tr("trackName");
    QString name;

    // For each element in media[i], add it to the treeWidget
    for (json::const_iterator i = track.begin(); i != track.end(); ++i) {

        // Create a new item titled i.key()
        auto * newItem = new QTreeWidgetItem( ui->treeWidget );
        const QString iKey = toQ(i.key());
        newItem->setText(0, iKey);

        // Create a new item titled i.value()
        auto * newItemChild = new QTreeWidgetItem();
        const QString iValue = toQ(i.value());
        newItemChild->setText( 0, iValue );

        // Name the child in the relationship, then add it to the treeWidget
        newItem->addChild( newItemChild );
        ui->treeWidget->addTopLevelItem( newItem );

        // Record track name if applicable
        if (iKey == trackName) name = iKey;
    }

    // Rename header to include song title
    ui->treeWidget->setHeaderLabels(
        QStringList() << QObject::tr("\"") + name + QObject::tr("\" information")
    );

    // Expand items as needed
    for(QTreeWidgetItemIterator i(ui->treeWidget); *i; ++i) {
        if (expanded.find((*i)->text(0)) != expanded.end())
            (*i)->setExpanded(true);
    }
}


/*****************************************************************/
/*                                                               */
/*             Define functions used in ResultsWindow            */
/*                                                               */
/*****************************************************************/


// Format a given date
inline const std::string formatDate( const std::string& d ) {
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

    // Remove undeeded "s if needed
    if (ret.size()) if (ret[0] == '\"') ret.erase(0, 1);
    if (ret.size()) if (ret[ret.size()-1] == '\"') ret.pop_back();

    // Return the string as a QString
    return std::move( QObject::tr(ret.c_str()) );
}
