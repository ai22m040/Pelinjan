#include <Pelinjan.h>

class Sandbox : public Pelinjan::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


Pelinjan::Application* Pelinjan::CreateApplication()
{
	return new Sandbox();
}
