#ifndef AGENTOPTIONSDIALOG_H
#define AGENTOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class AgentOptionsDialog;
}

class AgentOptionsDialog : public QDialog {
    Q_OBJECT

public:
    explicit AgentOptionsDialog(int locationId, bool isNewAgent,
                                QWidget *parent = 0);
    ~AgentOptionsDialog();

signals:
    void agentOptionSelected(int agentOption, int locationId, bool isNewAgent);

public slots:
    void onAgentOptionSelected();

private:
    Ui::AgentOptionsDialog *ui;
    int locationId;
    bool isNewAgent;
};

#endif // AGENTOPTIONSDIALOG_H
