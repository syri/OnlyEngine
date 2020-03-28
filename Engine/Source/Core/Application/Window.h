// Written by syri.
//
#pragma once
#include "../../Engine.h"


namespace Engine
{
	class PRAE_API Window
	{
	public:
		int m_X;
		int m_Y;
		int& m_Width;
		int& m_Height;
		bool m_Fullscreen;

		LPCWSTR m_WindowTitle;
		MSG m_Message;

	private:
		HINSTANCE m_InstanceHandle;
		HWND m_WindowHandle;

	public:
		Window(LPCWSTR WindowTitle, int& Width, int& Height, bool Fullscreen);
		~Window();

		bool Frame();

		static LRESULT CALLBACK MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
	};
}
