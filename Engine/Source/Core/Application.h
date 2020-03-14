// Written by Syri.
//
#pragma once


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
