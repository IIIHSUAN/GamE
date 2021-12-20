#include <GamE.h>

#include <iostream>

namespace Sandbox {

	class Application: public GE::Application
	{
	public:
		Application() { std::cout << "Sandbox app init\n"; };
		~Application() {};
	};

}

GE::Application* GE::create()
{
	return new Sandbox::Application();
}