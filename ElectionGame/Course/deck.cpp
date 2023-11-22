#include "deck.h"

#include "random.h"

using Interface::CardInterface;
using Interface::Random;
using std::shared_ptr;

namespace Course
{

Deck::Deck(bool visible):
    visible_(visible)
{
}

unsigned int Deck::size() const
{
    return cards_.size();
}

shared_ptr<const CardInterface> Deck::cardAt(unsigned int i) const
{
    return cards_.at(i);
}

shared_ptr<CardInterface> Deck::cardAt(unsigned int i)
{
    return cards_.at(i);
}

bool Deck::canDraw() const
{
    return size() > 0;
}

bool Deck::visible() const
{
    return visible_;
}

void Deck::addCard(shared_ptr<CardInterface> card, bool toBottom)
{
    if (toBottom)
    {
        cards_.push_front(card);
    }
    else
    {
        cards_.push_back(card);
    }

    emit deckChanged();
}

shared_ptr<CardInterface> Deck::draw()
{
    Q_ASSERT(size() > 0);

    shared_ptr<CardInterface> card = cards_.back();
    cards_.pop_back();

    emit deckChanged();

    return card;
}

shared_ptr<const CardInterface> Deck::peek() const
{
    return cards_.back();
}

shared_ptr<CardInterface> Deck::peek()
{
    return cards_.back();
}

void Deck::shuffle()
{
    for (unsigned int i = 1; i < cards_.size(); ++i)
    {
        unsigned int j = Random::RANDOM.uint(i);
        if (i != j)
        {
            cards_.at(i).swap(cards_.at(j));
        }
    }

    emit deckChanged();
}

} // Course
