// Written by syri.
//
#pragma once
#include "Engine.h"
#include "WindowData.h"
#include "Rendering/Renderers/Renderers.h"


namespace Engine
{
	class PRAESEGMEN_API Window
	{
	public:
		WindowDescriptor* m_WindowDescriptor;
		
		MSG m_Message;

		RendererType m_RendererType;
		IRenderer* m_Renderer;

	private:
		HINSTANCE m_InstanceHandle;

	public:
		Window(WindowDescriptor* InWindowDescriptor, const RendererType InRendererType);
		~Window();

		bool Update();
		void Render();
		
		static LRESULT CALLBACK MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);

	};
}
