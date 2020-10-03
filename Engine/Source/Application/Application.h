// Written by syri.
//
#pragma once
#include <API.h>


namespace Engine
{
    class CApplication
    {
    public:
        std::vector<CWindow*> Windows;

    private:
        bool m_bRunning;

    public:
        UMA_API CApplication();
        UMA_API virtual ~CApplication();

        UMA_API void Run();

        UMA_API void CreateNewWindow(SWindowDescriptor& InWindowDescriptor, const ERendererType InRendererType);

        UMA_API uint32_t GetEngineVersionYear() const { return 2020; }
        UMA_API uint32_t GetEngineVersionMajor() const { return 0; }
        UMA_API uint32_t GetEngineVersionMinor() const { return 7; }

		UMA_API uint32_t GetProjectVersionYear() const { return 2020; }
		UMA_API uint32_t GetProjectVersionMajor() const { return 0; }
		UMA_API uint32_t GetProjectVersionMinor() const { return 5; }

    };

    CApplication* CreateApplication();
    
}
