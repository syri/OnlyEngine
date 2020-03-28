// Written by syri.
//
#include "Window.h"


namespace Engine
{
	Window::Window(LPCWSTR WindowTitle, int& Width, int& Height, bool Fullscreen)
		: m_WindowTitle(WindowTitle), m_Width(Width), m_Height(Height), m_Fullscreen(Fullscreen), m_X(0), m_Y(0)
	{
		WNDCLASSEX WindowClass;
		DEVMODE ScreenSettings;

		ZeroMemory(&m_Message, sizeof(MSG));

		m_InstanceHandle = GetModuleHandle(NULL);

		WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		WindowClass.lpfnWndProc = MessageHandler;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = m_InstanceHandle;
		WindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		WindowClass.hIconSm = WindowClass.hIcon;
		WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		WindowClass.lpszMenuName = NULL;
		WindowClass.lpszClassName = m_WindowTitle;
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&WindowClass);

		if (m_Fullscreen)
		{
			// Handle full screen display settings and window creation.
			m_Width = GetSystemMetrics(SM_CXSCREEN);
			m_Height = GetSystemMetrics(SM_CYSCREEN);

			memset(&ScreenSettings, 0, sizeof(ScreenSettings));
			ScreenSettings.dmSize = sizeof(ScreenSettings);
			ScreenSettings.dmPelsWidth = (unsigned long)m_Width;
			ScreenSettings.dmPelsHeight = (unsigned long)m_Height;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);

			m_WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_WindowTitle, m_WindowTitle, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,
				m_X, m_Y, m_Width, m_Height, NULL, NULL, m_InstanceHandle, NULL);
		}
		else
		{
			// Normal window creation.
			m_X = (GetSystemMetrics(SM_CXSCREEN) - m_Width) / 2;
			m_Y = (GetSystemMetrics(SM_CYSCREEN) - m_Height) / 2;

			m_WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_WindowTitle, m_WindowTitle, WS_OVERLAPPEDWINDOW,
				m_X, m_Y, m_Width, m_Height, NULL, NULL, m_InstanceHandle, NULL);
		}

		ShowWindow(m_WindowHandle, SW_SHOW);
		SetForegroundWindow(m_WindowHandle);
		SetFocus(m_WindowHandle);
	}

	Window::~Window()
	{
		if (m_Fullscreen) ChangeDisplaySettings(NULL, 0);

		DestroyWindow(m_WindowHandle);
		m_WindowHandle = NULL;

		UnregisterClass(m_WindowTitle, m_InstanceHandle);
		m_InstanceHandle = NULL;
	}

	bool Window::Frame()
	{
		// Handle and dispatch messages.
		if (PeekMessage(&m_Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}

		if (m_Message.message == WM_QUIT) return false;

		return true;
	}

	LRESULT CALLBACK Window::MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(WindowHandle, Message, WParam, LParam);
		}
	}
}
