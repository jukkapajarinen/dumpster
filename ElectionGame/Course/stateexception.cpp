#include "stateexception.h"

namespace Interface
{

StateException::StateException(const QString &msg):
    GameException(msg)
{
}

} // Interface
