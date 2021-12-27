#pragma once

// interface: Time step differ in platforms setting in Window.cpp

namespace GE {

	class Time
	{
	public:
		static inline float getSeconds() { return _time->getSeconds_impl(); }
		static inline float getMillisecond() { return _time->getSeconds_impl()*1000.0f; }
	protected:
		virtual float getSeconds_impl() = 0;
	private:
		static Time* _time;
	};

}