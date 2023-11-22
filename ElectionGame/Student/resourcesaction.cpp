#include "resourcesaction.h"
#include "cardinterface.h"
#include "deckinterface.h"
#include "location.h"
#include "player.h"
#include <QDebug>
#include <memory>
#include <map>

using Interface::AgentInterface;
using Interface::Location;
using Interface::Player;
using Interface::CardInterface;

ResourcesAction::ResourcesAction(std::shared_ptr<AgentInterface> agent,
                                 std::shared_ptr<Location> location,
                                 std::shared_ptr<Player> currentPlayer)
    : agent_(agent), location_(location), player_(currentPlayer) {}

bool ResourcesAction::canPerform() const {
    return this->location_->deck()->canDraw() &&
            this->agent_->placement().lock() != nullptr;
}

void ResourcesAction::perform() {
    std::shared_ptr<CardInterface> drawedCard = this->location_->deck()->draw();
    this->player_->addCard(drawedCard);
    qDebug() << QString("ResourcesAction");
}
