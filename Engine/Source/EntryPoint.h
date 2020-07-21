// Written by syri.
//
#pragma once


#ifdef UMA_PLATFORM_WINDOWS
    extern Engine::CApplication* Engine::CreateApplication();

    int main(int argc, char** argv)
    {
        Engine::CApplication* Application = Engine::CreateApplication();
        Application->Run();
        delete Application;
    }
#endif
