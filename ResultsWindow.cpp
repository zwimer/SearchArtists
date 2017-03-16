#include "ResultsWindow.hpp"
#include "ui_ResultsWindow.h"
#include "MainWindow.hpp"
#include "Search.hpp"
#include "main.hpp"


/*****************************************************************/
/*                                                               */
/*                    Forwdward declearations                    */
/*                                                               */
/*****************************************************************/


// Given a track, format the name and when it was made
inline const QString format(const json & j);


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

    // TODO: check if getArtist is a valid artist !!!

    // Search for the selected artist
    json js = search( p->getArtist() );
    json media = js["results"];
    int n = js["resultCount"];

    // Populate the list widget
    for(int i = 0; i < n; i++) {
        ui->listWidget->addItem(format(media[i]));
    }

#if 0
    // Collect data
    auto js = search( "jack johnson" );

    // Separate number of tracks from media
    auto media = js["results"];
    int n = js["resultCount"];

    // Print out name of tracks
    for(int i = 0; i < n; i++)
        std::cout << media[i]["trackName"] << '\n';

    std::cout << " n = " << n << std::endl;
#endif

}

// Destructor, prevent leaks
ResultsWindow::~ResultsWindow() {
    delete this;
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

    // Return iR
    return std::move( QObject::tr( s.str().c_str() ) );
}
