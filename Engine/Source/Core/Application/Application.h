// Written by syri.
//
#pragma once
#include "../../Engine.h"
#include "Logger.h"
#include "Window.h"


namespace Engine
{
    class PRAE_API Application
    {
    public:
        std::wstring m_ApplicationName;
        std::vector<Window*> m_Window;

    private:
        bool m_Running;

    public:
        Application(std::wstring ApplicationName);
        virtual ~Application();

        void Run();
        void CreateNewWindow(WindowDescriptor* InWindowDescriptor);
    };

    Application* CreateApplication();
}
