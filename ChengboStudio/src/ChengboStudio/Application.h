#pragma once
#include "Core.h"
#include "Event/Event.h"

namespace ChengboStudio 
{
	class CHENGBO_API Application 
	{
	public:

		Application();
		virtual ~Application();

		void Run();

	};

	Application* CreateApplication(); //will be defined in sandbox project
}