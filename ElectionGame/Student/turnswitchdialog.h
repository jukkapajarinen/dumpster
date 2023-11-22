#ifndef TURNSWITCHDIALOG_H
#define TURNSWITCHDIALOG_H

#include "player.h"
#include <QDialog>
#include <memory>

using Interface::Player;

namespace Ui {
class TurnSwitchDialog;
}

class TurnSwitchDialog : public QDialog {
    Q_OBJECT

public:
    explicit TurnSwitchDialog(std::shared_ptr<Player> currentPlayer,
                              QWidget *parent = 0);
    ~TurnSwitchDialog();

signals:
    void switchSignal(QString val);

private:
    Ui::TurnSwitchDialog *ui;

private slots:
    void onTurnFinished();
};

#endif // SWITCHTURNS_H
