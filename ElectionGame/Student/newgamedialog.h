#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include "player.h"
#include <QDialog>
#include <map>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();
    std::map<int,QString> getPlayerNames();

signals:
    void startSignal();

private:
    Ui::NewGameDialog *ui;
    std::map<int, QString> playerMap;

private slots:
    void onStartGameClicked();
    void onPlayer3checkToggled(bool checked);
    void onPlayer4checkToggled(bool checked);
};

#endif // NEWGAMEDIALOG_H
