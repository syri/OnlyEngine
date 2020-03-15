// Written by Syri.
//
#include <OnlyEngine.h>
#include "Sandbox.h"


namespace Sandbox
{
	class Application : public Engine::Application
	{
	public:
		Application() : Engine::Application(L"Beans", 800, 600, false)
		{
			m_Logger->Print(Engine::LogType::Info, fmt::format("Engine: v{}.{}", ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR), true);
			m_Logger->Print(Engine::LogType::Info, fmt::format("Sandbox: v{}.{}", SANDBOX_VERSION_MAJOR, SANDBOX_VERSION_MINOR));
		}

		~Application()
		{}
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox::Application();
}
