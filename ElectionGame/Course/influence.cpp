#include "influence.h"

using std::weak_ptr;

namespace Interface
{

Influence::Influence(const QString& name, weak_ptr<Location> location, unsigned short amount):
    name_(name),
    location_(location),
    owner_(),
	amount_(amount)
{
}

QString Influence::typeName() const
{
    return "Influence";
}

QString Influence::name() const
{
    return name_;
}

QString Influence::title() const
{
    return "";
}

weak_ptr<Location> Influence::location() const
{
    return location_;
}

weak_ptr<Player> Influence::owner() const
{
    return owner_;
}

void Influence::setOwner(std::weak_ptr<Player> owner)
{
    owner_ = owner;
}

unsigned short Influence::amount() const
{
	return amount_;
}

} // Interface
