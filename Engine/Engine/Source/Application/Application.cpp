// Written by syri.
//
#include "Application.h"

#include <Application/Window.h>


namespace Engine
{
	Application::Application(std::wstring_view ApplicationName)
        : m_ApplicationName(ApplicationName), m_Running(true)
    {
		const char* AssemblyPath = "F:\\Development\\Praesegmen\\Binaries\\Win64\\GameScript.dll";
		const char* ProjectOnStartupDescriptorName = "Game:OnStartup()";
		const char* ProjectOnUpdateDescriptorName = "Game:OnUpdate()";
		
		mono_set_dirs("Mono\\lib", "Mono\\etc");
		
		Domain = mono_jit_init("Game");
		if (!Domain) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Initialise JIT."));

		Assembly = mono_domain_assembly_open(Domain, AssemblyPath);
		if (!Assembly) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Open Domain Assembly."));

		Image = mono_assembly_get_image(Assembly);
		if (!Image) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Get Image."));

		ProjectClass = mono_class_from_name(Image, "Game", "Game");
		if (!ProjectClass) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Get Project Class."));

		ProjectInstance = mono_object_new(Domain, ProjectClass);
		if (!ProjectInstance) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Instance of the Project Class."));
		mono_runtime_object_init(ProjectInstance);
		
		ProjectOnStartupDescriptor = mono_method_desc_new(ProjectOnStartupDescriptorName, NULL);
		if (!ProjectOnStartupDescriptor) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Create OnStartup Method Descriptor."));
		
		ProjectOnStartupMethod = mono_method_desc_search_in_image(ProjectOnStartupDescriptor, Image);
		if (!ProjectOnStartupMethod) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Find Method Inside Image."));

		ProjectOnUpdateDescriptor = mono_method_desc_new(ProjectOnUpdateDescriptorName, NULL);
		if (!ProjectOnUpdateDescriptor) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Create OnUpdate Method Descriptor."));

		ProjectOnUpdateMethod = mono_method_desc_search_in_image(ProjectOnUpdateDescriptor, Image);
		if (!ProjectOnUpdateMethod) Logger::Print(LogType::Error, true, TEXT("Mono Failed to Find Method Inside Image."));

		mono_runtime_invoke(ProjectOnStartupMethod, ProjectInstance, nullptr, nullptr);
    }

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

			mono_runtime_invoke(ProjectOnUpdateMethod, ProjectInstance, nullptr, nullptr);
        }
    }

	void Application::CreateNewWindow(WindowDescriptor* InWindowDescriptor, const RendererType InRendererType)
	{
        Window* NewWindow = new Window(InWindowDescriptor, InRendererType);

        m_Window.push_back(NewWindow);
	}
}
