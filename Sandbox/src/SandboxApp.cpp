#include "pch.h"
#include "ChengboStudio.h"

class TestLayer : public ChengboStudio::Layer
{
public:
	TestLayer()
		: Layer("Test!") {}

	void OnUpdate() override
	{
		CB_INFO("TestLayer Updated");
	}

	void OnEvent(ChengboStudio::Event& evt) override
	{		CB_TRACE("{0}", evt.ToString());
	}
};

class Sandbox : public ChengboStudio::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	};

	~Sandbox()
	{
	
	};
};

ChengboStudio::Application* ChengboStudio::CreateApplication()
{
	return new Sandbox();
};