// Written by Syri.
//
#pragma once
#include "../Engine.h"
#include "Logger.h"
#include "Window.h"


namespace Engine
{
    class ENGINE_API Application
    {
    public:
        std::string m_ApplicationName;

		Window* m_Window;
		Logger* m_Logger;

    private:
        bool m_Running;

    public:
        Application(std::string ApplicationName, int Width, int Height, bool Fullscreen);
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}
