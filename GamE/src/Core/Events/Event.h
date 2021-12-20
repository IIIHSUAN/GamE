#pragma once

#include <string>
#include <sstream>

#define BIT(x) (1<<x)

namespace GE {

	/* current event method: blocking-event
	 * todo: nonblocking, queue events
	 */

	// generate code
#define EVENT_TYPE_MACRO_FUNC(type) \
	static EventType getPrototype() { return EventType::type; }\
	virtual EventType getType() const override { return getPrototype(); }\
	virtual const char* getName() const override { return #type; }

#define EVENT_CATEGORY_MACRO_FUNC(category) virtual int getCategoryFlags() const override { return category; }

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		bool isPropagation = true;

		// override
		virtual EventType getType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}
	};

	class  EventHandler
	{
	public:
		EventHandler(Event& event)
			: _event(event) {}

		// Func will be deduced by the compiler
		template<typename T, typename Func>
		bool dispatch(const Func& func)
		{
			if (_event.getType() == T::getPrototype())
			{
				_event.isPropagation |= func(static_cast<T&>(_event));
				return true;
			}
			return false;
		}
	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

}

