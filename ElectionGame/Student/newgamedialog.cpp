#include "newgamedialog.h"
#include "ui_newgamedialog.h"
#include <map>

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog) {
    ui->setupUi(this);
    connect(ui->startGameButton, SIGNAL(clicked()),
            this, SLOT(onStartGameClicked()));
    connect(ui->player3check, SIGNAL(toggled(bool)),
            this, SLOT(onPlayer3checkToggled(bool)));
    connect(ui->player4Check, SIGNAL(toggled(bool)),
            this, SLOT(onPlayer4checkToggled(bool)));
}

NewGameDialog::~NewGameDialog() {
    delete ui;
}

void NewGameDialog::onStartGameClicked() {
    std::map<int, QString> playerMap;

    playerMap[0] = ui->player1NameEdit->text() !=
            "" ? ui->player1NameEdit->text() : "Pelaaja 1";
    playerMap[1] = ui->player2NameEdit->text() !=
            "" ? ui->player2NameEdit->text() : "Pelaaja 2";

    if(ui->player3check->isChecked()) {
        playerMap[2] = ui->player3NameEdit->text() !=
                "" ? ui->player3NameEdit->text() : "Pelaaja 3";
    }

    if(ui->player4Check->isChecked()) {
        playerMap[3] = ui->player4NameEdit->text() !=
                "" ? ui->player4NameEdit->text() : "Pelaaja 4";
    }
    this->playerMap = playerMap;

    emit startSignal();
}

std::map<int,QString> NewGameDialog::getPlayerNames() {
    return this->playerMap;
}

void NewGameDialog::onPlayer3checkToggled(bool checked) {
    ui->player3NameEdit->setEnabled(checked);
}

void NewGameDialog::onPlayer4checkToggled(bool checked) {
    ui->player4NameEdit->setEnabled(checked);
}
