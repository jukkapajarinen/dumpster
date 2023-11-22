#include "game.h"
#include "mainwindow.h"
#include "safeqapplication.h"
#include <memory>

using Interface::Game;

/*
 * The main program should initialize the game and open the main window, or
 * delegate these tasks elsewhere.
 */
int main(int argc, char* argv[]) {
    SafeQApplication a(argc, argv);
    std::shared_ptr<Game> game = std::make_shared<Game>();
    MainWindow mainWindow(game);
    a.exec();
}
