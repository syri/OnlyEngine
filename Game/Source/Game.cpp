// Written by syri.
//
#include <GamePCH.h>
#include <Game.h>


namespace Game
{
	Engine::SWindowDescriptor GameWindowDescriptor = Engine::SWindowDescriptor(TEXT("Game"), 800, 600, Engine::EWindowMode::Windowed);
	class CStringFormatArgument;
	class CApplication : public Engine::CApplication
	{
	public:
		CApplication()
			: Engine::CApplication()
		{
			Engine::CLogger::PrintLine(Engine::ELogType::Info, TEXT("Engine Version: {0}.{1}.{2}"),
				std::vector<std::variant<int32_t>>{ GetEngineVersionYear(), GetEngineVersionMajor(), GetEngineVersionMinor() });
			Engine::CLogger::PrintLine(Engine::ELogType::Info, TEXT("Project Version: {0}.{1}.{2}"),
				std::vector<std::variant<int32_t>>{ GetProjectVersionYear(), GetProjectVersionMajor(), GetProjectVersionMinor() });

			GameWindowDescriptor.ClearColour = Engine::SColour(0.6f, 0.6f, 0.6f, 1.f);
			CreateNewWindow(GameWindowDescriptor, Engine::ERendererType::D3D12);
		}

		~CApplication()
		{}

	};
}

Engine::CApplication* Engine::CreateApplication() { return new Game::CApplication(); }
