#include "councilor.h"

using std::weak_ptr;

namespace Interface
{

Councilor::Councilor(const QString &name, const QString &title, weak_ptr<Location> location):
    name_(name),
    title_(title),
    location_(location),
    owner_()
{
}

QString Councilor::typeName() const
{
    return "Councilor";
}

QString Councilor::name() const
{
    return name_;
}

QString Councilor::title() const
{
    return title_;
}

weak_ptr<Location> Councilor::location() const
{
    return location_;
}

weak_ptr<Player> Councilor::owner() const
{
    return owner_;
}

void Councilor::setOwner(std::weak_ptr<Player> owner)
{
    owner_ = owner;
}

weak_ptr<const Player> Councilor::player() const
{
    return player_;
}

std::weak_ptr<Player> Councilor::player()
{
	return player_;
}

void Councilor::setPlayer(weak_ptr<Player> player)
{
	player_ = player;
}

} // Interface
