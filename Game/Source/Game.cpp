// Written by syri.
//
#include "Game.h"


namespace Game
{
	Engine::WindowDescriptor GameWindowDescriptor = Engine::WindowDescriptor(L"Game", 800, 600, false);

	class Application : public Engine::Application
	{
	public:
		Application() : Engine::Application(GameWindowDescriptor.WindowTitle)
		{
			Engine::Logger::Setup();
			Engine::Logger::Print(Engine::LogType::Info, fmt::format("Engine: v{0}.{1}.{2}", PRAE_VERSION_YEAR, PRAE_VERSION_MAJOR, PRAE_VERSION_MINOR), true);
			Engine::Logger::Print(Engine::LogType::Info, fmt::format("Project: v{0}.{1}.{2}", PROJECT_VERSION_YEAR, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR), true);

			// TODO: Abstract out renderer modes so they can be assigned to windows individually
			GameWindowDescriptor.ClearColour = Engine::FloatColour(0.6f, 0.6f, 0.6f, 1.0f);
			CreateNewWindow(&GameWindowDescriptor);
		}

		~Application()
		{}
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Game::Application();
}
