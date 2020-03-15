// Written by Syri.
//
#include "Application.h"


namespace Engine
{
    Application::Application(LPCWSTR ApplicationName, int Width, int Height, bool Fullscreen)
        : m_ApplicationName(ApplicationName), m_Running(true)
    {
        m_Logger = new Logger();
        m_Window = new Window(m_ApplicationName, Width, Height, Fullscreen);
    }

    Application::~Application()
    {
        m_Logger = NULL;
        delete m_Logger;

        m_Window = NULL;
        delete m_Window;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            if (!m_Window->Frame()) m_Running = false;
        }
    }
}
