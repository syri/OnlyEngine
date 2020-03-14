// Written by Syri.
//
#pragma once


#ifdef ENGINE_PLATFORM_WINDOWS
    extern Engine::Application* Engine::CreateApplication();

    int main(int argc, char** argv)
    {
        auto application = Engine::CreateApplication();
        application->Run();
        delete application;
    }
#endif
