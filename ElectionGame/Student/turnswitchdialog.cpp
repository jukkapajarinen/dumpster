#include "turnswitchdialog.h"
#include "mainwindow.h"
#include "ui_turnswitchdialog.h"
#include <memory>

TurnSwitchDialog::TurnSwitchDialog(std::shared_ptr<Player> currentPlayer,
                                   QWidget *parent):
    QDialog(parent), ui(new Ui::TurnSwitchDialog) {
    ui->setupUi(this);
    ui->nextPlayerNameLabel->setText(currentPlayer->name());
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onTurnFinished()));
}

TurnSwitchDialog::~TurnSwitchDialog() {
    delete ui;
}

void TurnSwitchDialog::onTurnFinished() {
    emit switchSignal(ui->okButton->text());
}
