#include "negotiationaction.h"
#include "agentinterface.h"
#include <QDebug>
#include <memory>

using Interface::AgentInterface;

NegotiationAction::NegotiationAction(std::shared_ptr<AgentInterface> agent) {
    this->agent_ = agent;
}

bool NegotiationAction::canPerform() const {
    return this->agent_->placement().lock() != nullptr &&
            this->agent_->placement().lock()->influence(this->agent_->owner().lock())
            <= SHRT_MAX;
}

void NegotiationAction::perform() {
    unsigned short currentInfluence =
            this->agent_->placement().lock()->influence(this->agent_->owner().lock());
    ++currentInfluence;
    this->agent_->placement().lock()->setInfluence(this->agent_->owner().lock(),
                                             currentInfluence);
    qDebug() << QString("NegotiationAction");
}
