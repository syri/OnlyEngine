// Written by Syri.
//
#include <Prae.h>
#include "Game.h"


namespace Game
{
	class Application : public Engine::Application
	{
	public:
		Application() : Engine::Application(L"Game", 800, 600, false)
		{
			m_Logger->Print(Engine::LogType::Info, fmt::format("Engine: v{}.{}", PRAE_VERSION_MAJOR, PRAE_VERSION_MINOR), true);
			m_Logger->Print(Engine::LogType::Info, fmt::format("Game: v{}.{}", GAME_VERSION_MAJOR, GAME_VERSION_MINOR));
		}

		~Application()
		{}
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Game::Application();
}
