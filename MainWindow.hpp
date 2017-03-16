#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <string>

#include <QMainWindow>


// Forward declarations
class ResultsWindow;

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

    // Get the selected artist
    std::string getArtist() const;

private slots:

    // Creates a new search window
    void spawnSearch(bool);

private:

    // Representation
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_HPP
