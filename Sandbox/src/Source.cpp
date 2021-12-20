#include <GamE.h>

#include <iostream>

namespace Sandbox {

	class Application: public GE::Application
	{
	public:
		Application() { COUT_YEL("Sandbox Init"); };
		~Application() {};
	};

}

GE::Application* GE::create()
{
	return new Sandbox::Application();
}