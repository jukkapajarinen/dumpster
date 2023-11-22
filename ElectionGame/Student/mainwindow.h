#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "turnswitchdialog.h"
#include "newgamedialog.h"
#include "game.h"
#include "runner.h"
#include "manualcontrol.h"
#include "agent.h"
#include "location.h"
#include "player.h"
#include "deckinterface.h"
#include "cardinterface.h"
#include "influence.h"
#include "agentinterface.h"
#include "withdrawaction.h"
#include "resourcesaction.h"
#include "relationshipsaction.h"
#include "negotiationaction.h"
#include "manualcontrol.h"
#include "controlinterface.h"
#include "gameoverdialog.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QMainWindow>
#include <map>
#include <algorithm>
#include <memory>

using Interface::Player;
using Interface::Game;
using Interface::AgentInterface;
using Interface::Location;
using Interface::Runner;
using Interface::ManualControl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Game> game, QWidget *parent = 0);
    ~MainWindow();
    std::shared_ptr<Game> getGameObject() const;
    void initializeQGraphicsItemsForLocation(int locationId);
    void changeQraphicsItemsOpacities(float opacity, std::vector<int> itemIds);
    void updateHandCards(std::shared_ptr<Player> player);
    void updateAgentQGraphicsItems();
    void updateCoinQGraphicsItems();
    void updateDeckQGraphicsItems();
    void locationsSetup();
    int turnNumber = 1;
    int actionNumber = 0;
    int eventFilterMode;
    static int const DISALLOW_CLICKS = 0;
    static int const ALLOW_LOC_CLICKS = 1;
    static int const ALLOW_CARD_CLICKS = 2;
    static int const ALLOW_DECK_CLICKS = 3;
    static int const MAX_TURNS = 10;
    static int const MAX_ACTIONS = 2;

public slots:
    void onSwitchTurnsClicked();
    void onEndTurnConfirmed();
    void onEndGameClicked();
    void toggleTimer();
    void onElapsedTimerUpdate();
    void onAgentHandCardClicked();
    void onInfluenceHandCardClicked();
    void showNewGameDialog();
    void playerSetup();
    void setCurrentPlayer(std::shared_ptr<const Player> prevPlayer);
    void onAgentActionPlayed(int agentOption, int locationId, bool isNewAgent);
    void onZoomInButtonClicked();
    void onZoomOutButtonClicked();

signals:
    void endGameSignal();

private:
    Ui::MainWindow *ui;
    TurnSwitchDialog *turnDialog;
    QTimer *elapsedTimer;
    int elapsedTimeCounter;
    std::vector<int> visibleItemIds;
    std::shared_ptr<Game> game;
    NewGameDialog *newGame;
    std::shared_ptr<Runner> newRunner;
    std::map<QString, QString> calculateFinalResultsData();
    int const LOC_WIDTH = 140;
    int const LOC_HEIGHT = 75;
    int const CARD_WIDTH = 44;
    int const CARD_HEIGHT = 60;
    int const COIN_WIDTH = 30;
    int const COIN_HEIGHT = 30;
    int const HOR_SPACE = 300;
    int const VER_SPACE = 200;
    int const FONT_SIZE = 10;
    QFont const FONT = QFont(QString("Thonburi"), FONT_SIZE, -1, false);
    QPixmap const PIXMAP_LOC1 = QPixmap(":/Assets/location1.png");
    QPixmap const PIXMAP_LOC2 = QPixmap(":/Assets/location2.png");
    QPixmap const PIXMAP_LOC3 = QPixmap(":/Assets/location3.png");
    QPixmap const PIXMAP_LOC4 = QPixmap(":/Assets/location4.png");
    QPixmap const PIXMAP_DECK = QPixmap(":/Assets/carddeck.png");
    QPixmap const PIXMAP_AGENT = QPixmap(":/Assets/card_agent.png");
    QPixmap const PIXMAP_COIN1 = QPixmap(":/Assets/coin1.png");
    QPixmap const PIXMAP_COIN2 = QPixmap(":/Assets/coin2.png");
    QPixmap const PIXMAP_COIN3 = QPixmap(":/Assets/coin3.png");
    QPixmap const PIXMAP_COIN4 = QPixmap(":/Assets/coin4.png");

    std::map<int, std::map<int,int>> const LOC_CARD_IDS = {
        {0, {{0,85},{1,84},{2,83},{3,82}}},
        {1, {{0,63},{1,62},{2,61},{3,60}}},
        {2, {{0,41},{1,40},{2,39},{3,38}}},
        {3, {{0,19},{1,18},{2,17},{3,16}}}
    };
    std::map<int, std::map<int,int>> const LOC_CARD_COIN_IDS = {
        {0, {{0,77},{1,76},{2,75},{3,74}}},
        {1, {{0,55},{1,54},{2,53},{3,52}}},
        {2, {{0,33},{1,32},{2,31},{3,30}}},
        {3, {{0,11},{1,10},{2,9},{3,8}}}
    };
    std::map<int, std::map<int,int>> const LOC_CARD_COIN_VAL_IDS = {
        {0, {{0,69},{1,68},{2,67},{3,66}}},
        {1, {{0,47},{1,46},{2,45},{3,44}}},
        {2, {{0,25},{1,24},{2,23},{3,22}}},
        {3, {{0,3},{1,2},{2,1},{3,0}}}
    };
    std::map<int, std::map<int,int>> const LOC_COIN_IDS = {
        {0, {{0,81},{1,80},{2,79},{3,78}}},
        {1, {{0,59},{1,58},{2,57},{3,56}}},
        {2, {{0,37},{1,36},{2,35},{3,34}}},
        {3, {{0,15},{1,14},{2,13},{3,12}}}
    };
    std::map<int, std::map<int,int>> const LOC_COIN_VAL_IDS = {
        {0, {{0,73},{1,72},{2,71},{3,70}}},
        {1, {{0,51},{1,50},{2,49},{3,48}}},
        {2, {{0,29},{1,28},{2,27},{3,26}}},
        {3, {{0,7},{1,6},{2,5},{3,4}}}
    };
    std::map<int, int> const LOC_DECK_IDS = {
        {0, 86}, {1, 64}, {2, 42}, {3, 20}
    };
    std::map<int, int> const LOC_IDS = {
        {0, 87}, {1, 65}, {2, 44}, {3, 21}
    };
};

#endif // MAINWINDOW_H
