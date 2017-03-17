#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ResultsWindow.hpp"
#include "Error.hpp"

// QT
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

// STL
#include <fstream>

// C
#include <libgen.h>


// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    //Setup the ui
    ui->setupUi(this);

    // Display startup warning
    QString txt = tr(
                "After clicking search, this program may not "
                "respond instantly. This is due to the fact that is is "
                "requesting information from Apple's API. In a few seconds "
                "your results should pop up."
    );

    //Warn the user
    QMessageBox::warning(NULL, QObject::tr("Warning"),
                txt, QMessageBox::Ok, QMessageBox::Ok);

    // Connect the search button and the spawn function
    QObject::connect( ui->pushButton, SIGNAL( clicked(bool) ),
                      this, SLOT( spawnSearch(bool) ) );

    // Connect the load button to selecting a file
    QObject::connect( ui->loadButton, SIGNAL( clicked(bool) ),
                      this, SLOT( chooseFile(bool) ) );
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

// Get the name or the selected artist
std::string MainWindow::getArtist() const {
    return std::move( ui->lineEdit->text().toLatin1().constData() );
}

// Spawn a search window then clear line edit
void MainWindow::spawnSearch(bool) {

    // Create a new window, and show it
    // Don't worry about leaks, destructor handles them
    (new ResultsWindow( this ))->show();

    // Clear the lineEdit
    ui->lineEdit->clear();
}

// Choose a file to read the json in from
void MainWindow::chooseFile(bool) const {

    // Get the in file
    const std::string inFileName = QFileDialog::getOpenFileName(
        NULL,
        tr("Choose the file to read from:"),
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        tr("JSON (*.json)")
    ).toLatin1().constData();

    // Read from the in file
    std::ifstream inFile(inFileName);

    // Error checking
    if(!inFile.is_open())
        throw new Error("Selected file could not be opened.");

    // Read file into string
    std::stringstream buf;
    buf << inFile.rdbuf();
    const std::string info = buf.str();

    // Check the contents of the file
    bool isBad = true;
    for(size_t i = 0; i < info.size(); ++i) {
        if (!isspace(info[i])) {
            isBad = false;
            break;
        }
    }

    // If file is empty, throw an exception
    if (isBad) throw new Error("Bad file");

    // Get and format the artist's name, error check while doing so
    std::string artist = basename( (char *) inFileName.c_str() );
    if (artist.size() < 5 || artist.find(".json") == std::string::npos)
        throw new Error("File not valid");
    else if (artist.size() == 5) artist = "";
    else artist = artist.substr(0, artist.size()-5);

    // Create a new window, and show it
    // Don't worry about leaks, destructor handles them
    (new ResultsWindow( artist, info ))->show();

    // Clear the lineEdit
    ui->lineEdit->clear();
}
