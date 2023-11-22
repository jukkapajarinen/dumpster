#ifndef SAFEQAPPLICATION_H
#define SAFEQAPPLICATION_H

#include <QApplication>

class SafeQApplication : public QApplication
{

public:
    SafeQApplication(int &argc, char ** argv);

private:
    bool notify(QObject *receiver, QEvent *event);
};

#endif // SAFEQAPPLICATION_H
