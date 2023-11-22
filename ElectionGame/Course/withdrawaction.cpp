#include "withdrawaction.h"

#include "agentinterface.h"
#include "location.h"
#include "player.h"

using std::shared_ptr;

namespace Interface
{

WithdrawAction::WithdrawAction(shared_ptr<AgentInterface> agent):
    agent_(agent)
{
}

bool WithdrawAction::canPerform() const
{
    return agent_->placement().lock() != nullptr;
}

void WithdrawAction::perform()
{
    agent_->placement().lock()->removeAgent(agent_);
    agent_->owner().lock()->addCard(agent_);
}

} // Interface
