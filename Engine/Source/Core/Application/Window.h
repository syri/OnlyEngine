// Written by syri.
//
#pragma once
#include "../../Engine.h"
#include "Logger.h"
#include "WindowData.h"
#include "../Rendering/D3D12.h"


namespace Engine
{
	class PRAE_API Window
	{
	public:
		WindowDescriptor* m_WindowDescriptor;
		
		MSG m_Message;

		D3D12* m_Renderer;

	private:
		HINSTANCE m_InstanceHandle;

	public:
		Window(WindowDescriptor* InWindowDescriptor);
		~Window();

		bool Update();
		void Render();
		
		static LRESULT CALLBACK MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
	};
}
