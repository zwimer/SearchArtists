#include "MainWindow.hpp"
#include "ui_MainWindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    //Setup the ui
    ui->setupUi(this);



}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}
