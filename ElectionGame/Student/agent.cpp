#include "agent.h"
#include "stateexception.h"
#include <QDebug>
#include <memory>

using Interface::AgentInterface;
using Interface::Location;
using Interface::Player;
using Interface::StateException;

Agent::Agent(const QString &name, std::weak_ptr<Location> placement,
             int connections = 0):
    name_(name),
    location_(placement),
    connections_(connections) {}

QString Agent::typeName() const {
    return "Agent";
}

QString Agent::name() const {
    return name_;
}

QString Agent::title() const {
    return "";
}

std::weak_ptr<Location> Agent::location() const {
    return location_;
}

std::weak_ptr<Player> Agent::owner() const {
    return owner_;
}

void Agent::setOwner(std::weak_ptr<Player> owner) {
    owner_ = owner;
}

bool Agent::isCommon() const {
    return location_.expired();
}

std::weak_ptr<Location> Agent::placement() const {
    return location_;
}

void Agent::setPlacement(std::weak_ptr<Location> placement) {
    if(!placement.expired()) {
        location_ = placement;
    } else {
        location_ = std::weak_ptr<Location>();
    }
}

unsigned short Agent::connections() const {
    return connections_;
}

void Agent::setConnections(unsigned short connections) {
    if(location_.expired()) {
        throw StateException(QString("Invariant violated!"));
    }
    connections_ = connections;
}

void Agent::modifyConnections(short amount) {
    if(location_.expired() || amount < 0) {
        throw StateException(QString("Invariant violated!"));
    }
    connections_ = amount;
}
