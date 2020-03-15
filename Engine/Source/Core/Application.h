// Written by Syri.
//
#pragma once
#include "../Engine.h"
#include "Logger.h"


namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Logger* m_Logger = NULL;

    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}
