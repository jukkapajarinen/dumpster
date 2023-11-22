#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include <map>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameOverDialog(std::map<QString, QString> resultsData,
                            QWidget *parent = 0);
    ~GameOverDialog();

signals:
    void endSignal(QString val);

private:
    Ui::GameOverDialog *ui;

private slots:
    void onQuitGameClicked();
};

#endif // GAMEOVERDIALOG_H
