#include "agentoptionsdialog.h"
#include "mainwindow.h"
#include "ui_agentoptionsdialog.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

AgentOptionsDialog::AgentOptionsDialog(int locationId, bool isNewAgent,
                                       QWidget *parent):
    QDialog(parent),
    ui(new Ui::AgentOptionsDialog) {

    ui->setupUi(this);
    connect(ui->agentButtonBox, SIGNAL(accepted()), this,
            SLOT(onAgentOptionSelected()));
    this->locationId = locationId;
    this->isNewAgent = isNewAgent;
}

AgentOptionsDialog::~AgentOptionsDialog() {
    delete ui;
}

void AgentOptionsDialog::onAgentOptionSelected() {

    QVBoxLayout *radioButtons = ui->agentActionVerticalLayout;

    for (int i = 0; i < radioButtons->count(); i++) {
        QRadioButton *tempBtn = (QRadioButton *)radioButtons->itemAt(i)->widget();

        if (tempBtn->isChecked()) {
            emit agentOptionSelected(i, this->locationId, this->isNewAgent);
        }
    }
}
