#include "rangeexception.h"

namespace Interface
{

RangeException::RangeException(const QString &msg):
    GameException(msg)
{
}

} // Interface
