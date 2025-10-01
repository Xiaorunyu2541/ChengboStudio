#include "ChengboStudio.h"

class Sandbox : public ChengboStudio::Application {
public:
	Sandbox()
	{

	};

	~Sandbox()
	{
	
	};
};

ChengboStudio::Application* ChengboStudio::CreateApplication()
{
	return new Sandbox();
};