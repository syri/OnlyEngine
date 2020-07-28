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

        UMA_API int GetEngineVersionYear() const { return 2020; }
        UMA_API int GetEngineVersionMajor() const { return 0; }
        UMA_API int GetEngineVersionMinor() const { return 7; }

		UMA_API int GetProjectVersionYear() const { return 2020; }
		UMA_API int GetProjectVersionMajor() const { return 0; }
		UMA_API int GetProjectVersionMinor() const { return 5; }

    };

    CApplication* CreateApplication();
    
}
