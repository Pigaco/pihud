#include <pihud/FocusEvent.hpp>
#include <pihud/FocusManager.hpp>

namespace PiH
{
    FocusEvent::FocusEvent()
    {

    }
    FocusEvent::FocusEvent(const piga::GameEvent &gameEvent)
    {
        if(gameEvent.type() == piga::GameEvent::GameInput)
        {
            if(gameEvent.gameInput.state())
            {
                switch(gameEvent.gameInput.control())
                {
                    case piga::GameControl::UP:
                        direction = Direction::UP;
                        break;
                    case piga::GameControl::DOWN:
                        direction = Direction::DOWN;
                        break;
                    case piga::GameControl::LEFT:
                        direction = Direction::LEFT;
                        break;
                    case piga::GameControl::RIGHT:
                        direction = Direction::RIGHT;
                        break;
                    default:
                        break;
                }
            }
            else 
            {
                direction = Direction::DIRECTION_NOT_SET;
            }
        }
        else 
        {
            direction = Direction::DIRECTION_NOT_SET;
        }
    }
    FocusEvent::~FocusEvent()
    {

    }
    void FocusEvent::setHandled(bool handled) const
    {
        m_handled = handled;
    }
    bool FocusEvent::wasHandled() const
    {
        return m_handled;
    }
    bool FocusEvent::leftOrRight() const
    {
        if(direction == Direction::LEFT || Direction::RIGHT)
            return true;
        return false;
    }
    bool FocusEvent::upOrDown() const
    {
        if(direction == Direction::UP || Direction::DOWN)
            return true;
        return false;
    }
    FocusEvent& FocusEvent::operator=(const FocusEvent &other)
    {
        m_forced = other.wasForced();
        m_handled = other.wasHandled();
        direction = other.direction;
        return *this;
    }
    bool FocusEvent::wasForced() const
    {
        return m_forced;
    }
}
