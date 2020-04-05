// Written by syri.
//
#pragma once


#ifdef PRAE_PLATFORM_WINDOWS
    extern Engine::Application* Engine::CreateApplication();

    int main(int argc, char** argv)
    {
        Engine::Application* Application = Engine::CreateApplication();
        Application->Run();
        delete Application;
    }
#endif
