#pragma once

#include <piga/GameEvent.hpp>

#include <pihud/DirectionEvent.hpp>
#include <pihud/InputEvent.hpp>
#include <pihud/FocusEvent.hpp>

namespace PiH
{
    enum class EventType
    {
        NotSet,
        Direction,
        Input,
        Mouse,
        Focus,

        _COUNT
    };

    class Event
    {
        public:
            Event();
            Event(const DirectionEvent &dirEvent);
            Event(const InputEvent &inputEvent);
            Event(const FocusEvent &focusEvent);
            Event(const piga::GameEvent &gameEvent);
            virtual ~Event();

			EventType type;

            union
            {
				DirectionEvent dir;
                InputEvent input;
                FocusEvent focus;
            };
    };
}
