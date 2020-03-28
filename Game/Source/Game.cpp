// Written by syri.
//
#include "Game.h"


namespace Game
{
	class Application : public Engine::Application
	{
	public:
		Application() : Engine::Application(PROJECT_NAME, 800, 600, false)
		{
			Engine::Logger::Setup();
			Engine::Logger::Print(Engine::LogType::Info, fmt::format("Engine: v{0}.{1}.{2}", PRAE_VERSION_YEAR, PRAE_VERSION_MAJOR, PRAE_VERSION_MINOR), true);
			Engine::Logger::Print(Engine::LogType::Info, fmt::format("Project: v{0}.{1}.{2}", PROJECT_VERSION_YEAR, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR));
		}

		~Application()
		{}
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Game::Application();
}
