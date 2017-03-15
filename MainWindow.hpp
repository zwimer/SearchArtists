#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

// Protect the global namespace
namespace Ui {
    class MainWindow;
}

// The main window class
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    // Explicit constructor, prevent implicit parent
    explicit MainWindow(QWidget *parent = 0);

    // Destructor
    ~MainWindow();

private:

    // Representation
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
