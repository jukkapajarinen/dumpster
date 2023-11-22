#include "relationshipsaction.h"
#include "agentinterface.h"
#include <QDebug>
#include <memory>

using Interface::AgentInterface;

RelationshipsAction::RelationshipsAction(std::shared_ptr<AgentInterface> agent)
    : agent_(agent) {}

bool RelationshipsAction::canPerform() const {
    return this->agent_->connections() <= SHRT_MAX &&
            this->agent_->placement().lock() != nullptr;
}

void RelationshipsAction::perform() {
    if (this->agent_->connections() == 0) {
        this->agent_->setConnections(1);
    } else {
        this->agent_->modifyConnections(this->agent_->connections() + 1);
    }
    qDebug() << QString("RelationshipsAction");
}
