#ifndef DECK_H
#define DECK_H

#include "deckinterface.h"

#include <QObject>

#include <deque>

namespace Course
{

class Deck: public QObject, public Interface::DeckInterface
{
    Q_OBJECT
public:
    explicit Deck(bool visible);
    virtual ~Deck() = default;

    virtual unsigned int size() const;
    virtual std::shared_ptr<const Interface::CardInterface> cardAt(unsigned int i) const;
    virtual std::shared_ptr<Interface::CardInterface> cardAt(unsigned int i);
    virtual bool canDraw() const;
    virtual bool visible() const;

    virtual void addCard(std::shared_ptr<Interface::CardInterface> card, bool toBottom = false);
    virtual std::shared_ptr<Interface::CardInterface> draw();
    virtual std::shared_ptr<const Interface::CardInterface> peek() const;
    virtual std::shared_ptr<Interface::CardInterface> peek();
    virtual void shuffle();

signals:
    void deckChanged() const;

private:
    std::deque<std::shared_ptr<Interface::CardInterface> > cards_;
    const bool visible_;
};

} // Course

#endif // DECK_H
