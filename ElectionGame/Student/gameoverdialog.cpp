#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QDebug>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

GameOverDialog::GameOverDialog(std::map<QString, QString> resultsData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog) {

    ui->setupUi(this);
    connect(ui->quitGameButton,SIGNAL(clicked()),this,SLOT(onQuitGameClicked()));
    ui->gameResultsTextEdit->setText(QString("Peli loppui vuorolla: ") +
                                     resultsData["playedTurns"] + QString("/") +
                                     resultsData["maxTurns"] + QString("<br>"));
    ui->gameResultsTextEdit->append(QString("Pisteiden jako: "));
    std::vector<std::pair<int, QString>> sortableResults = {};

    for(int i = 0 ; i < resultsData["playerCount"].toInt() ; i++) {
        QString playerPoints = QString("player")+QString::number(i+1)+QString("Points");
        QString playerName = QString("player")+QString::number(i+1)+QString("Name");
        sortableResults.push_back(std::make_pair(resultsData[playerPoints].toInt(), resultsData[playerName]));
    }
    std::sort(sortableResults.begin(), sortableResults.end());
    std::reverse(sortableResults.begin(), sortableResults.end());

    for(unsigned long i = 0 ; i < sortableResults.size() ; i++) {
        ui->gameResultsTextEdit->append(QString::number(i+1)+QString(". ")+
                                        QString::number(sortableResults.at(i).first)+
                                        QString(" pst (")+sortableResults.at(i).second+QString(")"));
    }
}

GameOverDialog::~GameOverDialog() {
    delete ui;
}
void GameOverDialog::onQuitGameClicked(){
    emit endSignal(ui->quitGameButton->text());
}
