// Written by Syri.
//
#include "Application.h"


namespace Engine
{
    Application::Application()
    {
        m_Logger = new Logger();
    }

    Application::~Application()
    {
        m_Logger = NULL;
        delete m_Logger;
    }

    void Application::Run()
    {
        while (true);
    }
}
