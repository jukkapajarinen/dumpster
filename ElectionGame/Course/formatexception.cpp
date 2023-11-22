#include "formatexception.h"

namespace Interface
{

FormatException::FormatException(const QString &msg):
    GameException(msg)
{
}

} // Interface
