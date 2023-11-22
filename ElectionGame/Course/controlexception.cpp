#include "controlexception.h"

namespace Interface
{

ControlException::ControlException(const QString &msg):
    GameException(msg)
{
}

} // Interface
