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
        LPCWSTR m_ApplicationName;
		Window* m_Window;

    private:
        bool m_Running;

    public:
        Application(LPCWSTR ApplicationName, int Width, int Height, bool Fullscreen);
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}
