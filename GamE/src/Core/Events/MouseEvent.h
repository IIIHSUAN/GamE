#pragma once

#include "Event.h"

namespace GE {

	using MouseCode = uint16_t;
	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Mouse0 = 0,
			Mouse1 = 1,
			Mouse2 = 2,
			Mouse3 = 3,
			Mouse4 = 4,
			Mouse5 = 5,
			Mouse6 = 6,
			Mouse7 = 7,

			MouseLast = Mouse7,
			MouseLeft = Mouse0,
			MouseRight = Mouse1,
			MouseMiddle = Mouse2
		};
	}

	class  MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float mouseX, const float mouseY)
			: _mouseX(mouseX), _mouseY(mouseY) {}

		float GetX() const { return _mouseX; }
		float GetY() const { return _mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << _mouseX << ',' << _mouseY << ')';
			return ss.str();
		}

		EVENT_TYPE_MACRO_FUNC(MouseMoved)
		EVENT_CATEGORY_MACRO_FUNC(EventCategoryMouse | EventCategoryInput)
	private:
		float _mouseX, _mouseY;
	};

	class  MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float offsetX, const float offsetY)
			: _offsetX(offsetX), _offsetY(offsetY) {}

		float GetXOffset() const { return _offsetX; }
		float GetYOffset() const { return _offsetY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << GetXOffset() << ',' << GetYOffset() << ')';
			return ss.str();
		}

		EVENT_TYPE_MACRO_FUNC(MouseScrolled)
		EVENT_CATEGORY_MACRO_FUNC(EventCategoryMouse | EventCategoryInput)
	private:
		float _offsetX, _offsetY;
	};

	class  MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return _mouseBotton; }

		EVENT_CATEGORY_MACRO_FUNC(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(const MouseCode button)
			: _mouseBotton(button) {}

		MouseCode _mouseBotton;
	};

	class  MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << _mouseBotton;
			return ss.str();
		}

		EVENT_TYPE_MACRO_FUNC(MouseButtonPressed)
	};

	class  MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << _mouseBotton;
			return ss.str();
		}

		EVENT_TYPE_MACRO_FUNC(MouseButtonReleased)
	};

}
