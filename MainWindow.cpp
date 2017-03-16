#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ResultsWindow.hpp"

#include <QMessageBox>

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

    // Connect the button and the spawn function
    QObject::connect( ui->pushButton, SIGNAL(clicked(bool)),
                      this, SLOT(spawnSearch(bool)) );  
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

