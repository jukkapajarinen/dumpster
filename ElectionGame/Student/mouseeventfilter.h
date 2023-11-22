#ifndef MOUSEEVENTFILTER_H
#define MOUSEEVENTFILTER_H

#include <QObject>
#include <QMouseEvent>
#include "mainwindow.h"

class MouseEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit MouseEventFilter(QObject *parent = 0);
    bool eventFilter(QObject* object, QEvent* event);

private:
    MainWindow *mainWindow;
    void launchAgentOptionsDialog(int locationId, bool isNewAgent);
};

#endif // MOUSEEVENTFILTER_H

