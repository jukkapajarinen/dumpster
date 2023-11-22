#include "manualcontrol.h"

using std::shared_ptr;

namespace Interface
{

ManualControl::ManualControl()
{
}

shared_ptr<ActionInterface> ManualControl::nextAction()
{
    shared_ptr<ActionInterface> action = action_;
    action_ = nullptr;
    return action;
}

void ManualControl::setNextAction(std::shared_ptr<ActionInterface> action)
{
    action_ = action;
}

} // Interface
