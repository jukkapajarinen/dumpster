#include "location.h"

#include "agentinterface.h"
#include "deck.h"
#include "player.h"

using Course::Deck;
using std::make_shared;
using std::set;
using std::shared_ptr;
using std::weak_ptr;

namespace Interface
{

Location::Location(unsigned short id, const QString &name):
    id_(id),
    name_(name)
{
}

void Location::initialize()
{
    shared_ptr<Deck> deck = make_shared<Deck>(false);
    shared_ptr<Deck> discards = make_shared<Deck>(true);

    connect(deck.get(), &Deck::deckChanged, this, &Location::updateDeck);
    connect(discards.get(), &Deck::deckChanged, this, &Location::updateDiscards);

    deck_ = deck;
    discards_ = discards;
}

unsigned short Location::id() const
{
    return id_;
}

QString Location::name() const
{
    return name_;
}

shared_ptr<const DeckInterface> Location::deck() const
{
    return deck_;
}

shared_ptr<DeckInterface> Location::deck()
{
    return deck_;
}

shared_ptr<const DeckInterface> Location::discards() const
{
    return discards_;
}

shared_ptr<DeckInterface> Location::discards()
{
    return discards_;
}

set<shared_ptr<const AgentInterface> > Location::agents() const
{
    set<shared_ptr<const AgentInterface> > agents;
    for (shared_ptr<AgentInterface> agent: agents_)
    {
        agents.insert(agent);
    }
    return agents;
}

set<shared_ptr<AgentInterface> > Location::agents()
{
	return agents_;
}

bool Location::canSendAgent(shared_ptr<const Player> owner) const
{
    for (shared_ptr<AgentInterface> agent: agents_)
	{
		if (agent->owner().lock() == owner)
		{
			return false;
		}
	}

	return true;
}

void Location::sendAgent(shared_ptr<AgentInterface> agent)
{
	agents_.insert(agent);
    agent->setPlacement(shared_from_this());
    emit agentsChanged(shared_from_this());
}

void Location::removeAgent(shared_ptr<AgentInterface> agent)
{
	agents_.erase(agent);
    agent->setPlacement(weak_ptr<Location>());
    emit agentsChanged(shared_from_this());
}

shared_ptr<const Councilor> Location::councilor() const
{
    return councilor_;
}

shared_ptr<Councilor> Location::councilor()
{
    return councilor_;
}

void Location::setCouncilor(shared_ptr<Councilor> councilor)
{
    councilor_ = councilor;
}

unsigned short Location::influence(shared_ptr<const Player> player) const
{
    auto i = influence_.find(player->id());
    if (i != influence_.end())
    {
        return i->second;
    }
    else
    {
        return 0;
    }
}

void Location::setInfluence(shared_ptr<const Player> player, unsigned short influence)
{
    influence_[player->id()] = influence;
    emit influenceChanged(shared_from_this());
}

void Location::updateAgents()
{
    emit agentsChanged(shared_from_this());
}

void Location::updateDeck()
{
    emit deckChanged(shared_from_this());
}

void Location::updateDiscards()
{
    emit discardsChanged(shared_from_this());
}

} // Interface
