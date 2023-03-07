#pragma once

#include "Pelinjan/Core.h"

#include <string>
#include <functional>

namespace Pelinjan {

	// Events in Pelinjan are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory // if we want to filter for certain event types
	{
		// realized as Bitfield as we would like to be able to combine different event categories
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class PE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
		// This class is used to dispatch events to the correct event handler
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; // takes a reference to an event and returns a bool
	
	public:
		EventDispatcher(Event& event)
			: m_Event(event)  // takes a reference to an event and stores it in m_Event
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// (T*)&m_Event casts the event to the correct type (--> T&)
				// func(*(T*)&m_Event) calls the function with the event as parameter
				// then takes return value of func(which is a bool) and performs a bitwise OR operation 
				// with the current value of m_Handled(m_Event.m_Handled)
				// The |= operator is used to set the m_Handled flag to true if the event has been handled 
				// by the listener (i.e. if the callback function returns true), without overwriting any previous 
				// values that may have been set by other listeners.
				m_Event.m_Handled |= func(*(T*)&m_Event);
				return true;
			}
			return false;
		}		

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

