#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ResultsWindow.hpp"


// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    //Setup the ui
    ui->setupUi(this);

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
    return std::move(ui->lineEdit->text()).toLatin1().constData();
}

// Spawn a search window
void MainWindow::spawnSearch(bool) const {

    // Create a new window, and show it
    // Don't worry about leaks, destructor handles them
    (new ResultsWindow( this ))->show();
}

