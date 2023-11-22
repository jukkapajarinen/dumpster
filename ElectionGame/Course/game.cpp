#include "game.h"

#include "deck.h"
#include "location.h"
#include "player.h"
#include "settingsreader.h"

#include <set>

using Course::Deck;
using Interface::Player;
using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace Interface
{

Game::Game():
    players_(),
    locations_(),
    councilorDeck_(),
    active_(false),
    currentPlayer_(0)
{
    shared_ptr<Deck> councilorDeck = make_shared<Deck>(false);
    connect(councilorDeck.get(), &Deck::deckChanged, this, &Game::updateCouncilors);
    councilorDeck_ = councilorDeck;
}

vector<shared_ptr<const Player> > Game::players() const
{
    vector<shared_ptr<const Player> > players;
    for (shared_ptr<Player> player: players_)
    {
        players.push_back(player);
    }
    return players;
}

vector<shared_ptr<Player> > Game::players()
{
    return players_;
}

vector<shared_ptr<const Location> > Game::locations() const
{
    vector<shared_ptr<const Location> > locations;
    for (shared_ptr<Location> location: locations_)
    {
        locations.push_back(location);
    }
    return locations;
}

vector<shared_ptr<Location> > Game::locations()
{
    return locations_;
}

shared_ptr<const DeckInterface> Game::councilorDeck() const
{
    return councilorDeck_;
}

shared_ptr<DeckInterface> Game::councilorDeck()
{
    return councilorDeck_;
}

bool Game::active() const
{
    return active_;
}

void Game::setActive(bool active)
{
    active_ = active;
}

std::shared_ptr<const Player> Game::currentPlayer() const
{
    return players_.at(currentPlayer_);
}

shared_ptr<Player> Game::currentPlayer()
{
    return players_.at(currentPlayer_);
}

void Game::addLocation(std::shared_ptr<Location> location)
{
    locations_.push_back(location);
}

std::shared_ptr<Player> Game::addPlayer(const QString &name)
{
    shared_ptr<Player> player = make_shared<Player>(shared_from_this(), players_.size(), name);
    addPlayer(player);
    return player;
}

void Game::addPlayer(std::shared_ptr<Player> player)
{
    bool ok = true;
    uint maxPlayers = SettingsReader::READER.getValue("MAX_PLAYERS").toUInt(&ok);
    uint prevPlayers = players_.size();
    Q_ASSERT(ok && prevPlayers < maxPlayers);

    players_.push_back(player);
}

void Game::nextPlayer()
{
    shared_ptr<Player> prevPlayer = currentPlayer();

    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    notify(prevPlayer);
}

void Game::notify(shared_ptr<const Player> prevPlayer) const
{
    shared_ptr<const Player> player = prevPlayer != nullptr ? prevPlayer : currentPlayer();

    emit playerChanged(player);
}

void Game::updateCouncilors()
{
    emit councilorDeckChanged();
}

} // Interface
