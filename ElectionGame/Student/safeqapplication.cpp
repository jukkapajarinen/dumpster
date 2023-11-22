#include "safeqapplication.h"
#include "gameexception.h"
#include <QMessageBox>

using Interface::GameException;

SafeQApplication::SafeQApplication(int &argc, char **argv)
    : QApplication(argc, argv) {}

bool SafeQApplication::notify(QObject *receiver, QEvent *event) {
    try {
        return QApplication::notify(receiver, event);
    } catch (GameException &e) {
        QMessageBox *exceptionDialog = new QMessageBox();
        exceptionDialog->setText(
                    QString("Voi rähmä, peli suljetaan sisäisen virheen takia: ") + e.msg());
        connect(exceptionDialog, SIGNAL(finished(int)), this, SLOT(quit()));
        exceptionDialog->show();
        return false;
    }
}
