// Written by syri.
//
#include "Game.h"


namespace Game
{
	Engine::WindowDescriptor GameWindowDescriptor = Engine::WindowDescriptor(TEXT("Game"), 800, 600, false);

	class Application : public Engine::Application
	{
	public:
		Application() : Engine::Application(GameWindowDescriptor.WindowTitle)
		{
			GameWindowDescriptor.ClearColour = Engine::FloatColour(0.6f, 0.6f, 0.6f, 1.0f);
			CreateNewWindow(&GameWindowDescriptor, Engine::RendererType::D3D12);
		}

		~Application()
		{}

	};
}

Engine::Application* Engine::CreateApplication() { return new Game::Application(); }
