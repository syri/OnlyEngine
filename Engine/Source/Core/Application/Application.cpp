// Written by syri.
//
#include "Application.h"


namespace Engine
{
	Application::Application(std::wstring ApplicationName)
        : m_ApplicationName(ApplicationName), m_Running(true)
    {}

    Application::~Application()
    {
        for (Window* WindowReference : m_Window)
        {
            WindowReference = 0;
            delete WindowReference;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
			for (Window* WindowReference : m_Window)
			{
				if (!WindowReference->Update()) m_Running = false;
				else WindowReference->Render();
			}
        }
    }

	void Application::CreateNewWindow(WindowDescriptor* InWindowDescriptor)
	{
        m_Window.push_back(new Window(InWindowDescriptor));
	}
}
