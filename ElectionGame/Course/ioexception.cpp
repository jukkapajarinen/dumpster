#include "ioexception.h"

namespace Interface
{

IoException::IoException(const QString &msg):
    GameException(msg)
{
}

} // Interface
