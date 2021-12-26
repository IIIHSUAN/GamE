#pragma once

// interface: polling for Input setting in Window.cpp

#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

namespace GE {

	class Input
	{
	public:
		static bool isKeyPressed(int keyCode) { return _input->isKeyPressed_impl(keyCode); }
		static bool isMousePressed(int mouseCode) { return _input->isMousePressed_impl(mouseCode); }
		static std::pair<float, float> getMousePos() { return _input->getMousePos_impl(); }
		static float getMouseX() { return _input->getMouseX_impl(); }
		static float getMouseY() { return _input->getMouseY_impl(); }
	protected:
		virtual bool isKeyPressed_impl(int keyCode) = 0;
		virtual bool isMousePressed_impl(int mouseCode) = 0;
		virtual std::pair<float, float> getMousePos_impl() const = 0;
		virtual bool getMouseX_impl() const = 0;
		virtual bool getMouseY_impl() const = 0;
	private:
		static Input* _input;
	};
}