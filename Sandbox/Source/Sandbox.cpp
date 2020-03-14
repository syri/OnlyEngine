// Written by Syri.
//
#include <Engine.h>


class Sandbox : public Engine::Application
{
public:
    Sandbox()
    {
        printf("Only Engine: v%i.%i", ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR);
    }

    ~Sandbox() {}
};

Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();
}
