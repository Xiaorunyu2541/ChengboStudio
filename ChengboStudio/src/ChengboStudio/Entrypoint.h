#pragma once
#ifdef STUDIO_WINDOWS_PLATFORM

extern ChengboStudio::Application* ChengboStudio::CreateApplication();

int main(int argc, char** argv)
{
	ChengboStudio::Log::Init();
	ChengboStudio::Log::GetCoreLogger()->warn("studio");
	ChengboStudio::Log::GetClientLogger()->info("cli");

	auto app = ChengboStudio::CreateApplication();
	app->Run();
	delete app;
}
#endif // STUDIO_WINDOWS_PLATFORM
