// Written by syri.
//
#include <GamePCH.h>
#include <Game.h>


namespace Game
{
	Engine::SWindowDescriptor GameWindowDescriptor = Engine::SWindowDescriptor(TEXT("Game"), 800, 600, Engine::EWindowMode::Windowed);

	class CApplication : public Engine::CApplication
	{
	public:
		CApplication()
			: Engine::CApplication()
		{
			Engine::CLogger::Print(Engine::ELogType::Info, TEXT("Engine Version:"));
			Engine::CLogger::Print(Engine::ELogType::Info, TEXT("Project Version:"));

			GameWindowDescriptor.ClearColour = Engine::SColour(0.6f, 0.6f, 0.6f, 1.f);
			CreateNewWindow(GameWindowDescriptor, Engine::ERendererType::D3D12);
		}

		~CApplication()
		{}

	};
}

Engine::CApplication* Engine::CreateApplication() { return new Game::CApplication(); }
