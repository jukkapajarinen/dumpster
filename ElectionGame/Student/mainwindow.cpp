#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mouseeventfilter.h"
#include "game.h"
#include "player.h"
#include "runner.h"
#include "controlinterface.h"
#include "manualcontrol.h"
#include "actioninterface.h"
#include "withdrawaction.h"
#include "resourcesaction.h"
#include "relationshipsaction.h"
#include "negotiationaction.h"
#include "location.h"
#include "cardinterface.h"
#include "agentinterface.h"
#include "influence.h"
#include <memory>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>

using Interface::Game;
using Interface::Player;
using Interface::Runner;
using Interface::ControlInterface;
using Interface::ManualControl;
using Interface::ActionInterface;
using Interface::WithdrawAction;
using Interface::Location;
using Interface::CardInterface;
using Interface::AgentInterface;
using Interface::Influence;

MainWindow::MainWindow(std::shared_ptr<Game> game, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->game = game;
    this->game->setActive(true);

    // Näytetään uusipeli-dialogi ennen peliä
    this->showNewGameDialog();

    // Alustetaan pelialueet ja niiden korttipakat
    this->locationsSetup();

    // Alustetaan kello peliajan mittaamiseen
    this->elapsedTimer = new QTimer(this);
    this->elapsedTimeCounter = 0;
    connect(elapsedTimer, SIGNAL(timeout()), this, SLOT(onElapsedTimerUpdate()));

    // Alustetaan käyttöliittymän tekstielementtejä
    ui->timeLabel->setText(QString("Peliaikaa kulunut: ") +
                           QString::number(this->elapsedTimeCounter) +
                           QString("s"));
    ui->historyTextEdit->setText(QString("<b>Pelihistoria:</b>"));
    ui->historyTextEdit->append(QString("<b>Peli aloitettu:</b> ") +
                                QDateTime::currentDateTime().toString());
    ui->gameHelpLabel->setText(
                QString("Valitse pelattava kortti.. Sinulla on (") +
                QString::number(MAX_ACTIONS - this->actionNumber) +
                QString(") toimintoa."));

    // Alustetaan gameGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->gameGraphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QColor(245, 245, 245)));

    // Alustetaan QGraphicsItem:it kaikille pelialueille
    this->initializeQGraphicsItemsForLocation(1);
    this->initializeQGraphicsItemsForLocation(2);
    this->initializeQGraphicsItemsForLocation(3);
    this->initializeQGraphicsItemsForLocation(4);
    this->changeQraphicsItemsOpacities(0.1, {});
    this->visibleItemIds = {87, 65, 43, 21,
                            86, 64, 42, 20}; // pelialueet ja korttipakat näkyviin
    this->changeQraphicsItemsOpacities(1.0, this->visibleItemIds);

    // Asennetaan tapahtumasuodatin QGraphicsView:in klikkauksille
    ui->gameGraphicsView->installEventFilter(new MouseEventFilter(this));
    this->eventFilterMode = DISALLOW_CLICKS;

    // Yhdistetään käsikorttien painikkeiden signaalit ja slotit
    connect(ui->cardButton1, SIGNAL(clicked()), this,
            SLOT(onAgentHandCardClicked()));
    connect(ui->cardButton2, SIGNAL(clicked()), this,
            SLOT(onInfluenceHandCardClicked()));
    connect(ui->cardButton3, SIGNAL(clicked()), this,
            SLOT(onInfluenceHandCardClicked()));
    connect(ui->cardButton4, SIGNAL(clicked()), this,
            SLOT(onInfluenceHandCardClicked()));
    connect(ui->cardButton5, SIGNAL(clicked()), this,
            SLOT(onInfluenceHandCardClicked()));

    // Yhdistetään muita signaaleja ja slotteja
    connect(ui->switchTurnsButton, SIGNAL(clicked()), this,
            SLOT(onSwitchTurnsClicked()));
    connect(ui->endGameButton, SIGNAL(clicked()), this, SLOT(onEndGameClicked()));
    connect(this, SIGNAL(endGameSignal()), this, SLOT(onEndGameClicked()));
    connect(this->game.get(),
            SIGNAL(playerChanged(std::shared_ptr<const Player>)), this,
            SLOT(setCurrentPlayer(std::shared_ptr<const Player>)));
    connect(ui->zoomInButton, SIGNAL(clicked()), this,
            SLOT(onZoomInButtonClicked()));
    connect(ui->zoomOutButton, SIGNAL(clicked()), this,
            SLOT(onZoomOutButtonClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeQGraphicsItemsForLocation(int locationId) {
    std::map<int, QPixmap> picture = {{1, PIXMAP_LOC1},{2, PIXMAP_LOC2},{3, PIXMAP_LOC3},{4, PIXMAP_LOC4}};
    std::map<int, std::pair<int, int>> spacingXY = {{1,{0,0}}, {2,{HOR_SPACE,0}}, {3,{0,VER_SPACE}}, {4,{HOR_SPACE,VER_SPACE}}};

    // Pelialueen kuva
    ui->gameGraphicsView->scene()->addPixmap(picture[locationId].scaled(LOC_WIDTH, LOC_HEIGHT))
            ->setPos(0 + spacingXY[locationId].first, 0 + spacingXY[locationId].second);
    // Pelialueen korttipakka
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_DECK.scaled(CARD_WIDTH, CARD_HEIGHT))
            ->setPos(180 + spacingXY[locationId].first, 8 + spacingXY[locationId].second);
    // Pelialueen pelaajan 1 agenttikortti
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_AGENT.scaled(CARD_WIDTH, CARD_HEIGHT))
            ->setPos(-30 + spacingXY[locationId].first, 85 + spacingXY[locationId].second);
    // Pelialueen pelaajan 2 agenttikortti
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_AGENT.scaled(CARD_WIDTH, CARD_HEIGHT))
            ->setPos(20 + spacingXY[locationId].first, 85 + spacingXY[locationId].second);
    // Pelialueen pelaajan 3 agenttikortti
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_AGENT.scaled(CARD_WIDTH, CARD_HEIGHT))
            ->setPos(70 + spacingXY[locationId].first, 85 + spacingXY[locationId].second);
    // Pelialueen pelaajan 4 agenttikortti
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_AGENT.scaled(CARD_WIDTH, CARD_HEIGHT))
            ->setPos(120 + spacingXY[locationId].first, 85 + spacingXY[locationId].second);
    // Pelialueen pelaajan 1 pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN1.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(-30 + spacingXY[locationId].first, 10 + spacingXY[locationId].second);
    // Pelialueen pelaajan 2 pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN2.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(-30 + spacingXY[locationId].first, 35 + spacingXY[locationId].second);
    // Pelialueen pelaajan 3 pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN3.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(140 + spacingXY[locationId].first, 10 + spacingXY[locationId].second);
    // Pelialueen pelaajan 4 pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN4.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(140 + spacingXY[locationId].first, 35 + spacingXY[locationId].second);
    // Pelialueen pelaajan 1 agentin pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN1.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(-35 + spacingXY[locationId].first, 120 + spacingXY[locationId].second);
    // Pelialueen pelaajan 2 agentin pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN2.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(15 + spacingXY[locationId].first, 120 + spacingXY[locationId].second);
    // Pelialueen pelaajan 3 agentin pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN3.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(65 + spacingXY[locationId].first, 120 + spacingXY[locationId].second);
    // Pelialueen pelaajan 4 agentin pelimerkki
    ui->gameGraphicsView->scene()->addPixmap(PIXMAP_COIN4.scaled(COIN_WIDTH, COIN_HEIGHT))
            ->setPos(115 + spacingXY[locationId].first, 120 + spacingXY[locationId].second);
    // Pelialueen pelaajan 1 pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(-30 + spacingXY[locationId].first + FONT_SIZE / 2, 10 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 2 pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(-30 + spacingXY[locationId].first + FONT_SIZE / 2, 35 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 3 pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(140 + spacingXY[locationId].first + FONT_SIZE / 2, 10 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 4 pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(140 + spacingXY[locationId].first + FONT_SIZE / 2, 35 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 1 agentin pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(-35 + spacingXY[locationId].first + FONT_SIZE / 2, 120 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 2 agentin pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(15 + spacingXY[locationId].first + FONT_SIZE / 2, 120 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 3 agentin pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(65 + spacingXY[locationId].first + FONT_SIZE / 2, 120 + spacingXY[locationId].second + FONT_SIZE / 2);
    // Pelialueen pelaajan 4 agentin pelimerkin arvo
    ui->gameGraphicsView->scene()->addText(QString("0"), FONT)
            ->setPos(115 + spacingXY[locationId].first + FONT_SIZE / 2, 120 + spacingXY[locationId].second + FONT_SIZE / 2);
}

std::shared_ptr<Interface::Game> MainWindow::getGameObject() const {
    return this->game;
}

void MainWindow::updateHandCards(std::shared_ptr<Player> player) {
    // Päivitetään käsikorttipainkkeiden lukumäärät nollaksi
    ui->cardButton1->setText(QString::number(0));
    ui->cardButton2->setText(QString::number(0));
    ui->cardButton3->setText(QString::number(0));
    ui->cardButton4->setText(QString::number(0));
    ui->cardButton5->setText(QString::number(0));

    // Asetetaan käsikorttipainikkeiden lukumäärät oikeiksi
    for (int i = 0; i < (int)player->cards().size(); i++) {
        std::shared_ptr<CardInterface> card = player->cards().at(i);
        if (QString::compare(card->name(), QString("Agentti")) == 0) {
            ui->cardButton1->setText(
                        QString::number(ui->cardButton1->text().toInt() + 1));
        } else if (QString::compare(card->name(), QString("Kuninkaanlinna")) == 0) {
            ui->cardButton2->setText(
                        QString::number(ui->cardButton2->text().toInt() + 1));
        } else if (QString::compare(card->name(), QString("Kaupunginvartiosto")) ==
                   0) {
            ui->cardButton3->setText(
                        QString::number(ui->cardButton3->text().toInt() + 1));
        } else if (QString::compare(card->name(), QString("Kauppiaiden kilta")) ==
                   0) {
            ui->cardButton4->setText(
                        QString::number(ui->cardButton4->text().toInt() + 1));
        } else if (QString::compare(card->name(), QString("Hevostalli")) == 0) {
            ui->cardButton5->setText(
                        QString::number(ui->cardButton5->text().toInt() + 1));
        }
    }

    // Asetetaan tyhjät käsikorttipainikkeet ei-painettaviksi
    ui->cardButton1->setEnabled(ui->cardButton1->text().toInt() == 0 ? false
                                                                     : true);
    ui->cardButton2->setEnabled(ui->cardButton2->text().toInt() == 0 ? false
                                                                     : true);
    ui->cardButton3->setEnabled(ui->cardButton3->text().toInt() == 0 ? false
                                                                     : true);
    ui->cardButton4->setEnabled(ui->cardButton4->text().toInt() == 0 ? false
                                                                     : true);
    ui->cardButton5->setEnabled(ui->cardButton5->text().toInt() == 0 ? false
                                                                     : true);
}

void MainWindow::changeQraphicsItemsOpacities(float opacity,
                                              std::vector<int> itemIds) {
    // Asetetaan pienin mahdollinen läpinäkyvyys arvoon 0.1
    opacity = opacity < 0.1 ? 0.1 : opacity;
    for (int i = 0; i < ui->gameGraphicsView->items().size(); i++) {
        // Vaihdetaan läpinäkyvyys itemIDs:eille (tai kaikille jos itemIds on tyhjä)
        if (itemIds.size() == 0 ||
                (itemIds.size() > 0 &&
                 std::find(itemIds.begin(), itemIds.end(), i) != itemIds.end())) {
            ui->gameGraphicsView->items().at(i)->setOpacity(opacity);
        }
    }
}

void MainWindow::updateAgentQGraphicsItems() {
    for (unsigned long i = 0; i < this->game->players().size(); i++) {
        for (unsigned long j = 0; j < this->game->locations().size(); j++) {
            this->visibleItemIds.erase(std::remove(this->visibleItemIds.begin(),
                                              this->visibleItemIds.end(),
                                              LOC_CARD_IDS.at(j).at(i)),
                                       this->visibleItemIds.end());

            std::shared_ptr<Location> loc = this->game->locations().at(j);
            for (auto item : loc->agents()) {
                std::shared_ptr<AgentInterface> agent = item;
                if (agent->owner().lock()->id() == i) {
                    this->visibleItemIds.push_back((LOC_CARD_IDS.at(j)).at(i));
                }
            }
        }
    }
}

void MainWindow::updateCoinQGraphicsItems() {
    for (unsigned long i = 0; i < this->game->players().size(); i++) {
        for (unsigned long j = 0; j < this->game->locations().size(); j++) {
            this->visibleItemIds.erase(std::remove(this->visibleItemIds.begin(),
                                                   this->visibleItemIds.end(),
                                                   LOC_COIN_IDS.at(j).at(i)),
                                                   this->visibleItemIds.end());
            this->visibleItemIds.erase(std::remove(this->visibleItemIds.begin(),
                                                   this->visibleItemIds.end(),
                                                   LOC_COIN_VAL_IDS.at(j).at(i)),
                                                   this->visibleItemIds.end());
            this->visibleItemIds.erase(std::remove(this->visibleItemIds.begin(),
                                                   this->visibleItemIds.end(),
                                                   LOC_CARD_COIN_IDS.at(j).at(i)),
                                                   this->visibleItemIds.end());
            this->visibleItemIds.erase(std::remove(this->visibleItemIds.begin(),
                                                   this->visibleItemIds.end(),
                                                   LOC_CARD_COIN_VAL_IDS.at(j).at(i)),
                                                   this->visibleItemIds.end());

            std::shared_ptr<Location> loc = this->game->locations().at(j);
            // Pelialueiden pelimerkit
            if (loc->influence(this->game->players().at(i)) > 0) {
                this->visibleItemIds.push_back((LOC_COIN_IDS.at(j)).at(i));
                this->visibleItemIds.push_back((LOC_COIN_VAL_IDS.at(j)).at(i));
                QGraphicsTextItem *item =
                        (QGraphicsTextItem *)ui->gameGraphicsView->scene()->items().at(
                            LOC_COIN_VAL_IDS.at(j).at(i));
                item->setPlainText(
                            QString::number(loc->influence(this->game->players().at(i))));
            }

            for (auto item : loc->agents()) {
                std::shared_ptr<AgentInterface> agent = item;
                // Agenttikorttien pelimerkit
                if (agent->owner().lock()->id() == i) {
                    this->visibleItemIds.push_back((LOC_CARD_COIN_IDS.at(j)).at(i));
                    this->visibleItemIds.push_back((LOC_CARD_COIN_VAL_IDS.at(j)).at(i));
                    QGraphicsTextItem *item =
                            (QGraphicsTextItem *)ui->gameGraphicsView->scene()->items().at(
                                LOC_CARD_COIN_VAL_IDS.at(j).at(i));
                    item->setPlainText(QString::number(agent->connections()));
                }
            }
        }
    }
}

void MainWindow::updateDeckQGraphicsItems() {
    for (unsigned long i = 0; i < this->game->locations().size(); i++) {
        if (this->game->locations().at(i)->deck()->size() == 0) {
          this->visibleItemIds.erase(
              std::remove(this->visibleItemIds.begin(),
                          this->visibleItemIds.end(), LOC_DECK_IDS.at(i)),
              this->visibleItemIds.end());
        }
    }
}

std::map<QString, QString> MainWindow::calculateFinalResultsData() {
    std::map<QString, QString> resultsData = {};
    resultsData[QString("playedTurns")] = QString::number(this->turnNumber);
    resultsData[QString("maxTurns")] =
            QString::number(this->game->players().size() * MAX_TURNS);
    resultsData[QString("playerCount")] =
            QString::number(this->game->players().size());
    std::shared_ptr<Agent> currentAgent;
    for (unsigned long i = 0; i < this->game->players().size(); i++) {
        qreal temp = 0;
        for (unsigned long j = 0; j < this->game->players().at(i)->cards().size();
             j++) {
            if (QString::compare(this->game->players().at(i)->cards().at(j)->name(),
                                 QString("Agentti")) == 1) {
                ++temp;
            } else if (QString::compare(
                           this->game->players().at(i)->cards().at(j)->name(),
                           QString("Agentti")) == 0) {
                currentAgent = std::static_pointer_cast<Agent>(
                            this->game->players().at(i)->cards().at(j));
                temp += currentAgent->connections();
            }
        }

        for (unsigned long j = 0; j < this->game->locations().size(); j++) {
            for (auto x : this->game->locations().at(j)->agents()) {
                if (x->owner().lock() == this->game->players().at(i)) {
                    currentAgent = std::static_pointer_cast<Agent>(x);
                    temp += currentAgent->connections();
                }
            }
            temp +=
                    this->game->locations().at(j)->influence(this->game->players().at(i));
        }
        resultsData[QString("player") + QString::number(i + 1) + QString("Name")] =
                this->game->players().at(i)->name();
        resultsData[QString("player") + QString::number(i + 1) +
                QString("Points")] = QString::number(temp);
    }
    return resultsData;
}

void MainWindow::onSwitchTurnsClicked() {
    if ((unsigned long)this->turnNumber <
            this->game->players().size() * MAX_TURNS) {
        game->nextPlayer();
        this->actionNumber = 0;
        this->hide();
        TurnSwitchDialog *turnDialog =
                new TurnSwitchDialog(this->game->currentPlayer(), this);
        connect(turnDialog, SIGNAL(switchSignal(QString)), this,
                SLOT(onEndTurnConfirmed()));
        this->toggleTimer();
        turnDialog->show();
    } else {
        emit endGameSignal();
    }
}

void MainWindow::onEndTurnConfirmed() {
    this->turnNumber++;
    this->toggleTimer();
    this->eventFilterMode = ALLOW_CARD_CLICKS;
    ui->roundLabel->setText(
                QString("Vuoro: ") + QString::number(this->turnNumber) + QString(" / ") +
                QString::number(this->game->players().size() * MAX_TURNS));
    ui->gameHelpLabel->setText(
                QString("Valitse pelattava kortti.. Sinulla on (") +
                QString::number(MAX_ACTIONS - this->actionNumber) +
                QString(") toimintoa."));
    this->updateHandCards(this->game->currentPlayer());
    this->changeQraphicsItemsOpacities(1.0, this->visibleItemIds);
    this->show();
}

void MainWindow::onEndGameClicked() {
    this->hide();
    this->elapsedTimer->stop();
    this->game->setActive(false);
    this->eventFilterMode = DISALLOW_CLICKS;
    GameOverDialog *gameOver =
            new GameOverDialog(this->calculateFinalResultsData(), this);
    connect(gameOver, SIGNAL(endSignal(QString)), this, SLOT(close()));
    gameOver->show();
}

void MainWindow::onAgentHandCardClicked() {
    if (this->actionNumber < MAX_ACTIONS) {
        this->changeQraphicsItemsOpacities(
                    0.6, this->visibleItemIds); // Himmennetään QGraphicsItem:it
        this->changeQraphicsItemsOpacities(
                    1.0, {87, 65, 43, 21}); // Korostetaan vain pelialueet
        this->updateHandCards(this->game->currentPlayer());
        this->eventFilterMode = ALLOW_LOC_CLICKS;
        ui->gameHelpLabel->setText(
                    QString("Valitse pelialue, jonne haluat sijoittaa agentin.."));
    } else {
        ui->gameHelpLabel->setText(
                    QString("Sinulla ei ole enempää toimintoja.. Lopeta vuorosi \"Vaihda "
                            "vuoroa\"-painikkeesta."));
    }
}

void MainWindow::onInfluenceHandCardClicked() {
    this->eventFilterMode = ALLOW_CARD_CLICKS;
    ui->gameHelpLabel->setText(
                QString("Valitsemasi kortti ei ole toimintakortti.."));
}

void MainWindow::onElapsedTimerUpdate() {
    ui->timeLabel->setText(QString("Peliaikaa kulunut: ") +
                           QString::number(++this->elapsedTimeCounter) +
                           QString(" s"));
}

void MainWindow::onZoomInButtonClicked() {
    ui->gameGraphicsView->scale(2.0, 2.0);
}

void MainWindow::onZoomOutButtonClicked() {
    ui->gameGraphicsView->scale(0.5, 0.5);
}

void MainWindow::showNewGameDialog() {
    NewGameDialog *newGame = new NewGameDialog(this);
    this->newGame = newGame;
    connect(this->newGame, SIGNAL(startSignal()), this, SLOT(show()));
    connect(this->newGame, SIGNAL(startSignal()), this, SLOT(toggleTimer()));
    connect(this->newGame, SIGNAL(startSignal()), this, SLOT(playerSetup()));
    this->eventFilterMode = DISALLOW_CLICKS;
    this->newGame->show();
}

void MainWindow::toggleTimer() {
    if (this->elapsedTimer->isActive() == true) {
        this->elapsedTimer->stop();
    } else {
        this->elapsedTimer->start(1000);
    }
}

void MainWindow::locationsSetup() {
    std::shared_ptr<Location> location1 = std::make_shared<Location>(0, "Kuninkaanlinna");
    location1->initialize();
    this->game->addLocation(location1);

    std::shared_ptr<Location> location2 =
            std::make_shared<Location>(1, "Kaupunginvartiosto");
    location2->initialize();
    this->game->addLocation(location2);

    std::shared_ptr<Location> location3 =
            std::make_shared<Location>(2, "Kauppiaiden kilta");
    location3->initialize();
    this->game->addLocation(location3);

    std::shared_ptr<Location> location4 = std::make_shared<Location>(3, "Hevostalli");
    location4->initialize();
    this->game->addLocation(location4);

    for (int i = 0; i < (int)this->game->locations().size(); i++) {
        // Luodaan 7 vaikutusvaltakorttia
        for (int j = 0; j < 7; j++) {
            std::shared_ptr<Influence> influenceCard =
                    std::make_shared<Influence>(this->game->locations().at(i)->name(),
                                           this->game->locations().at(i), 1);
            this->game->locations().at(i)->deck()->addCard(influenceCard);
        }
        // Luodaan 3 agenttikorttia
        for (int j = 0; j < 3; j++) {
            std::shared_ptr<Agent> agentCard =
                    std::make_shared<Agent>("Agentti", this->game->locations().at(i), 1);
            this->game->locations().at(i)->deck()->addCard(agentCard);
        }
        // Sekoitetaan korttipakka
        this->game->locations().at(i)->deck()->shuffle();
    }
}

void MainWindow::playerSetup() {
    std::map<int, QString> playerNames = this->newGame->getPlayerNames();
    std::shared_ptr<Player> player1 = this->game->addPlayer(playerNames[0]);
    std::shared_ptr<Player> player2 = this->game->addPlayer(playerNames[1]);

    this->newRunner = std::make_shared<Runner>(this->game);
    std::shared_ptr<ManualControl> control1 = std::make_shared<ManualControl>();
    std::shared_ptr<ManualControl> control2 = std::make_shared<ManualControl>();
    this->newRunner->setPlayerControl(player1, control1);
    this->newRunner->setPlayerControl(player2, control2);
    player1->addCard(std::make_shared<Agent>("Agentti", std::weak_ptr<Location>(), 0));
    player2->addCard(std::make_shared<Agent>("Agentti", std::weak_ptr<Location>(), 0));

    if (playerNames.size() == 3 || playerNames.size() == 4) {
        std::shared_ptr<Player> player3 = this->game->addPlayer(playerNames[2]);
        std::shared_ptr<ManualControl> control3 = std::make_shared<ManualControl>();
        this->newRunner->setPlayerControl(player3, control3);
        player3->addCard(std::make_shared<Agent>("Agentti", std::weak_ptr<Location>(), 0));
    }

    if (playerNames.size() == 4) {
        std::shared_ptr<Player> player4 = this->game->addPlayer(playerNames[3]);
        std::shared_ptr<ManualControl> control4 = std::make_shared<ManualControl>();
        this->newRunner->setPlayerControl(player4, control4);
        player4->addCard(std::make_shared<Agent>("Agentti", std::weak_ptr<Location>(), 0));
    }

    this->updateHandCards(this->game->currentPlayer());
    ui->playerLabel->setText(QString("Pelaaja: ") + playerNames[0]);
    ui->roundLabel->setText(
                QString("Vuoro: ") + QString::number(this->turnNumber) + QString(" / ") +
                QString::number(this->game->players().size() * MAX_TURNS));
}

void MainWindow::setCurrentPlayer(std::shared_ptr<const Player> prevPlayer) {
    ui->playerLabel->setText(QString("Pelaaja: ") +
                             this->game->currentPlayer()->name());
}

void MainWindow::onAgentActionPlayed(int agentOption, int locationId,
                                     bool isNewAgent) {
    qDebug() << QString("AgentCard: option ") + QString::number(agentOption) +
                QString(", location ") + QString::number(locationId);

    std::shared_ptr<ManualControl> currentPlayerControl =
            std::static_pointer_cast<ManualControl>(
                this->newRunner->playerControl(this->game->currentPlayer()));
    std::shared_ptr<Location> location = this->game->locations().at(locationId);
    std::shared_ptr<Agent> currentAgent;

    // Laitetaan agentti pelialueelle, jos se pelattiin juuri
    if (isNewAgent) {
        for (unsigned long int i = 0;
             i < this->game->currentPlayer()->cards().size(); i++) {
            std::shared_ptr<CardInterface> card =
                    this->game->currentPlayer()->cards().at(i);
            if (QString::compare(card->name(), QString("Agentti")) == 0) {
                currentAgent = std::static_pointer_cast<Agent>(card);
                break;
            }
        }
        this->game->currentPlayer()->playCard(currentAgent);
        location->sendAgent(currentAgent);
    }

    // Etsitään pelattu agenttikortti pelialueesta
    for (auto x : location->agents()) {
        if (x->owner().lock() == this->game->currentPlayer()) {
            currentAgent = std::static_pointer_cast<Agent>(x);
        }
    }

    // Suoritetaan pelatun agenttikortin toiminto
    switch (agentOption) {
    case 0: // Suhteiden vaaliminen
        currentPlayerControl->setNextAction(
                    std::make_shared<RelationshipsAction>(currentAgent));
        ui->historyTextEdit->append(
                    QString("<b>Vuoro ") + QString::number(this->turnNumber) +
                    QString(":</b> <i>") + this->game->currentPlayer()->name() +
                    QString("</i> loi suhteita alueeseen: ") + location->name());
        break;
    case 1: // Resurssien kerääminen
        currentPlayerControl->setNextAction(std::make_shared<ResourcesAction>(
                                                currentAgent, location, this->game->currentPlayer()));
        ui->historyTextEdit->append(
                    QString("<b>Vuoro ") + QString::number(this->turnNumber) +
                    QString(":</b> <i>") + this->game->currentPlayer()->name() +
                    ("</i> keräsi resurssin alueelta: ") + location->name());
        break;
    case 2: // Neuvottelut
        currentPlayerControl->setNextAction(
                    std::make_shared<NegotiationAction>(currentAgent));
        ui->historyTextEdit->append(
                    QString("<b>Vuoro ") + QString::number(this->turnNumber) +
                    QString(":</b> <i>") + this->game->currentPlayer()->name() +
                    ("</i> neuvotteli alueella: ") + location->name());
        break;
    case 3: // Vetäytyminen
        currentPlayerControl->setNextAction(
                    std::make_shared<WithdrawAction>(currentAgent));
        ui->historyTextEdit->append(
                    QString("<b>Vuoro ") + QString::number(this->turnNumber) +
                    QString(":</b> <i>") + this->game->currentPlayer()->name() +
                    ("</i> vetäytyi alueelta: ") + location->name());
        break;
    }
    this->newRunner->run();

    // Päivitetään käyttöliittymä pelin tilan mukaiseksi
    this->updateAgentQGraphicsItems();
    this->updateCoinQGraphicsItems();
    this->updateDeckQGraphicsItems();
    this->updateHandCards(this->game->currentPlayer());
    this->changeQraphicsItemsOpacities(0.1, {});
    this->changeQraphicsItemsOpacities(1.0, this->visibleItemIds);

    this->eventFilterMode = ALLOW_CARD_CLICKS;
    this->actionNumber++; // Kasvatetaan pelattujen toimintojen määrää

    // Infotaan pelaajaa jäljellä olevista toiminnoista
    if (this->actionNumber < MAX_ACTIONS) {
        ui->gameHelpLabel->setText(
                    QString("Valitse pelattava kortti.. Sinulla on (") +
                    QString::number(MAX_ACTIONS - this->actionNumber) +
                    QString(") toimintoa."));
    } else {
        ui->gameHelpLabel->setText(
                    QString("Sinulla ei ole enempää toimintoja.. Lopeta vuorosi \"Vaihda "
                            "vuoroa\"-painikkeesta."));
    }
}
