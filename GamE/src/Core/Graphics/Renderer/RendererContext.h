#pragma once

namespace GE {

	class RendererContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffer() = 0;
	};

}