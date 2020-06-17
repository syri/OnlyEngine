// Written by syri.
//
#pragma once
#include <Engine.h>


namespace Engine
{
    enum class RendererType : unsigned int;
    struct WindowDescriptor;
    class Window;

    class Application
    {
    public:
        std::wstring m_ApplicationName;
        std::vector<Window*> m_Window;

		MonoDomain* Domain;
		MonoAssembly* Assembly;
		MonoImage* Image;
		MonoClass* ProjectClass;
		MonoObject* ProjectInstance;
		MonoMethodDesc* ProjectOnStartupDescriptor;
		MonoMethodDesc* ProjectOnUpdateDescriptor;
		MonoMethod* ProjectOnStartupMethod;
		MonoMethod* ProjectOnUpdateMethod;

    private:
        bool m_Running;

    public:
        PRAESEGMEN_API Application(std::wstring_view ApplicationName);
        PRAESEGMEN_API virtual ~Application();

        PRAESEGMEN_API void Run();
        PRAESEGMEN_API void CreateNewWindow(WindowDescriptor* InWindowDescriptor, const RendererType InRendererType);

        PRAESEGMEN_API int GetEngineVersionYear() const { return 2020; }
        PRAESEGMEN_API int GetEngineVersionMajor() const { return 0; }
        PRAESEGMEN_API int GetEngineVersionMinor() const { return 4; }

		PRAESEGMEN_API int GetProjectVersionYear() const { return 2020; }
		PRAESEGMEN_API int GetProjectVersionMajor() const { return 0; }
		PRAESEGMEN_API int GetProjectVersionMinor() const { return 3; }

    };

    Application* CreateApplication();
}
