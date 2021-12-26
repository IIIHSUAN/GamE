#pragma once

#include "../Input.h"

namespace GE {

	class Win_Input :public Input
	{
	private:
		virtual bool isKeyPressed_impl(int keyCode) override;
		virtual bool isMousePressed_impl(int mouseCode) override;
		virtual std::pair<float, float> getMousePos_impl() const override;
		virtual bool getMouseX_impl()  const override;
		virtual bool getMouseY_impl() const override;
	};

}