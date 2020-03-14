// Written by Syri.
//
#pragma once
#include "../API.h"


namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}
