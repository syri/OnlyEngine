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
			Engine::Logger::Print(Engine::LogType::Info, true, "Engine v{0}.{1}.{2}", PRAESEGMEN_VERSION_YEAR, PRAESEGMEN_VERSION_MAJOR, PRAESEGMEN_VERSION_MINOR);
			Engine::Logger::Print(Engine::LogType::Info, true, "Project v{0}.{1}.{2}", PROJECT_VERSION_YEAR, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);

			// TODO: Abstract out renderer modes so they can be assigned to windows individually
			GameWindowDescriptor.ClearColour = Engine::FloatColour(0.6f, 0.6f, 0.6f, 1.0f);
			CreateNewWindow(&GameWindowDescriptor, Engine::RendererType::D3D12);
		}

		~Application()
		{}
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Game::Application();
}
