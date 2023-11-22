#include "runner.h"

#include "actioninterface.h"
#include "controlexception.h"
#include "controlinterface.h"
#include "game.h"
#include "player.h"

using std::shared_ptr;

namespace Interface
{

Runner::Runner(shared_ptr<Game> game):
    game_(game)
{
}

shared_ptr<ControlInterface> Runner::playerControl(shared_ptr<const Player> player) const
{
    auto iter = playerControls_.find(player);
    if (iter != playerControls_.end())
    {
        return iter->second;
    }

    return shared_ptr<ControlInterface>();
}

void Runner::setPlayerControl(shared_ptr<const Player> player, shared_ptr<ControlInterface> control)
{
    playerControls_[player] = control;
}

std::shared_ptr<ControlInterface> Runner::run()
{
    while (game_->active())
    {
        shared_ptr<Player> player = game_->currentPlayer();
        shared_ptr<ControlInterface> control = playerControls_.at(player);
        shared_ptr<ActionInterface> action = control->nextAction();
        if (action == nullptr)
        {
            return control;
        }

        if (action->canPerform())
        {
            action->perform();
            emit actionPerformed(player, action);
        }
        else
        {
            throw ControlException("control produced unperformable action");
        }
    }

    return nullptr;
}

} // Interface
