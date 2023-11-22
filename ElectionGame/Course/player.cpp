#include "player.h"

#include "cardinterface.h"
#include "game.h"

using Interface::CardInterface;
using Interface::Councilor;
using Interface::Game;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

namespace Interface
{

Player::Player(weak_ptr<Game> game, unsigned short id, const QString &name):
    game_(game),
    id_(id),
    name_(name),
    councilor_()
{
}

unsigned short Player::id() const
{
    return id_;
}

QString Player::name() const
{
    return name_;
}

shared_ptr<const Councilor> Player::councilor() const
{
    return councilor_;
}

shared_ptr<Councilor> Player::councilor()
{
    return councilor_;
}

void Player::setCouncilor(shared_ptr<Councilor> councilor)
{
    councilor_ = councilor;
}

vector<shared_ptr<const CardInterface> > Player::cards() const
{
    vector<shared_ptr<const CardInterface> > cards;
    for (shared_ptr<CardInterface> card: cards_)
    {
        cards.push_back(card);
    }
    return cards;
}

vector<shared_ptr<CardInterface> > Player::cards()
{
    return cards_;
}

void Player::addCard(shared_ptr<CardInterface> card)
{
    cards_.push_back(card);
    card->setOwner(shared_from_this());
    game_.lock()->notify(nullptr);
}

void Player::playCard(shared_ptr<const CardInterface> card)
{
    for (vector<shared_ptr<CardInterface> >::iterator i = cards_.begin(); i != cards_.end(); ++i)
    {
        if (*i == card)
        {
            cards_.erase(i);
            game_.lock()->notify(nullptr);
            return;
        }
    }

    Q_ASSERT(false);
}

} // Interface
