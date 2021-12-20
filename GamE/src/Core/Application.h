#pragma once

namespace GE {

	class Application
	{
	public:
		Application();
		virtual ~Application();

	};

	// define by client & return new Application()
	Application* create();

}