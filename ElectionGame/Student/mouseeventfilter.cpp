#include "mouseeventfilter.h"
#include "agentoptionsdialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <memory>
#include <map>

MouseEventFilter::MouseEventFilter(QObject *parent) : QObject(parent) {}

bool MouseEventFilter::eventFilter(QObject *object, QEvent *event) {
  // Tarkista tapahtuman tyyppi (MouseButtonPress)
  if (event->type() == QEvent::MouseButtonPress) {
    // Etsitään painallusta vastaava QGraphicsItem
    QGraphicsView *gameGraphicsView = (QGraphicsView *)object;
    QMouseEvent *mEvent = (QMouseEvent *)event;
    QGraphicsItem *item = gameGraphicsView->itemAt(mEvent->x(), mEvent->y());
    this->mainWindow = (MainWindow *)object->parent()->parent();

    // Käsitellään painallus jos sellainen voidaan tehdä
    if (item != nullptr && item->opacity() == 1.0 &&
        this->mainWindow->actionNumber < MainWindow::MAX_ACTIONS &&
        this->mainWindow->eventFilterMode != MainWindow::DISALLOW_CLICKS) {
      // Selvitetään mitä QGraphicsItem id:tä painettiin
      int id;
      for (id = 0; id < gameGraphicsView->items().size() - 1; id++) {
        if (gameGraphicsView->items().at(id) == item) {
          break;
        }
      }

      qDebug() << QString("EventFilterMode: ") +
                      QString::number(this->mainWindow->eventFilterMode)
               << QString("QGraphicsItem: ") + QString::number(id)
               << gameGraphicsView->itemAt(mEvent->x(), mEvent->y());

      // Painallus tapahtui pelialueeseen
      if ((id == 87 || id == 65 || id == 43 || id == 21) &&
          this->mainWindow->eventFilterMode == MainWindow::ALLOW_LOC_CLICKS) {
        std::map<int, int> locationIds = {{87, 0}, {65, 1}, {43, 2}, {21, 3}};
        this->launchAgentOptionsDialog(locationIds[id], true);
      }
      // Painallus tapahtui ensimmäisen pelialueen agentteihin
      else if ((id == 85 || id == 84 || id == 83 || id == 82) &&
               this->mainWindow->eventFilterMode ==
                   MainWindow::ALLOW_CARD_CLICKS) {
        std::map<int, int> locationCardIds = {{0, 85}, {1, 84}, {2, 83}, {3, 82}};
        if (locationCardIds
                [this->mainWindow->getGameObject()->currentPlayer()->id()] == id) {
          this->launchAgentOptionsDialog(0, false);
        }
      }
      // Painallus tapahtui toisen pelialueen agentteihin
      else if ((id == 63 || id == 62 || id == 61 || id == 60) &&
               this->mainWindow->eventFilterMode ==
                   MainWindow::ALLOW_CARD_CLICKS) {
        std::map<int, int> locationCardIds = {{0, 63}, {1, 62}, {2, 61}, {3, 60}};
        if (locationCardIds
                [this->mainWindow->getGameObject()->currentPlayer()->id()] == id) {
          this->launchAgentOptionsDialog(1, false);
        }
      }
      // Painallus tapahtui kolmannen pelialueen agentteihin
      else if ((id == 41 || id == 40 || id == 39 || id == 38) &&
               this->mainWindow->eventFilterMode ==
                   MainWindow::ALLOW_CARD_CLICKS) {
        std::map<int, int> locationCardIds = {{0, 41}, {1, 40}, {2, 39}, {3, 38}};
        if (locationCardIds
                [this->mainWindow->getGameObject()->currentPlayer()->id()] == id) {
          this->launchAgentOptionsDialog(2, false);
        }
      }
      // Painallus tapahtui neljännen pelialueen agentteihin
      else if ((id == 19 || id == 18 || id == 17 || id == 16) &&
               this->mainWindow->eventFilterMode ==
                   MainWindow::ALLOW_CARD_CLICKS) {
        std::map<int, int> locationCardIds = {{0, 19}, {1, 18}, {2, 17}, {3, 16}};
        if (locationCardIds
                [this->mainWindow->getGameObject()->currentPlayer()->id()] == id) {
          this->launchAgentOptionsDialog(3, false);
        }
      }
      // Painallus tapahtui korttipakkoihin
      else if ((id == 86 || id == 64 || id == 42 || id == 20) &&
               this->mainWindow->eventFilterMode ==
                   MainWindow::ALLOW_DECK_CLICKS) {
        // Tulevaa kehitystä varten
      }
    }
  }

  return QObject::eventFilter(object, event);
}

void MouseEventFilter::launchAgentOptionsDialog(int locationId,
                                                bool isNewAgent) {
  AgentOptionsDialog *actionOptionDialog =
      new AgentOptionsDialog(locationId, isNewAgent, this->mainWindow);
  connect(actionOptionDialog, SIGNAL(accepted()), this->mainWindow,
          SLOT(show()));
  connect(actionOptionDialog, SIGNAL(rejected()), this->mainWindow,
          SLOT(show()));
  connect(actionOptionDialog, SIGNAL(agentOptionSelected(int, int, bool)),
          this->mainWindow, SLOT(onAgentActionPlayed(int, int, bool)));
  actionOptionDialog->show();
}
