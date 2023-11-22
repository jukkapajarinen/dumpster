#include "gameexception.h"

namespace Interface
{

GameException::GameException(const QString& msg):
    msg_(msg)
{
}

QString GameException::msg() const
{
    return msg_;
}

} // Interface
