// Written by syri.
//
#include "Window.h"


namespace Engine
{
	Window::Window(WindowDescriptor* InWindowDescriptor, RendererType InRendererType)
		: m_WindowDescriptor(InWindowDescriptor), m_RendererType(InRendererType)
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
		WindowClass.lpszClassName = m_WindowDescriptor->WindowTitle.c_str();
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&WindowClass);

		if (m_WindowDescriptor->Fullscreen)
		{
			// Handle full screen display settings and window creation.
			m_WindowDescriptor->Width = GetSystemMetrics(SM_CXSCREEN);
			m_WindowDescriptor->Height = GetSystemMetrics(SM_CYSCREEN);

			memset(&ScreenSettings, 0, sizeof(ScreenSettings));
			ScreenSettings.dmSize = sizeof(ScreenSettings);
			ScreenSettings.dmPelsWidth = m_WindowDescriptor->Width;
			ScreenSettings.dmPelsHeight = m_WindowDescriptor->Height;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);

			m_WindowDescriptor->WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_WindowDescriptor->WindowTitle.c_str(), m_WindowDescriptor->WindowTitle.c_str(),
				WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, m_WindowDescriptor->X, m_WindowDescriptor->Y,
				m_WindowDescriptor->Width, m_WindowDescriptor->Height, 0, 0, m_InstanceHandle, 0);
		}
		else
		{
			// Normal window creation.
			m_WindowDescriptor->X = (GetSystemMetrics(SM_CXSCREEN) - m_WindowDescriptor->Width) / 2;
			m_WindowDescriptor->Y = (GetSystemMetrics(SM_CYSCREEN) - m_WindowDescriptor->Height) / 2;

			m_WindowDescriptor->WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_WindowDescriptor->WindowTitle.c_str(), m_WindowDescriptor->WindowTitle.c_str(),
				WS_OVERLAPPEDWINDOW, m_WindowDescriptor->X, m_WindowDescriptor->Y, m_WindowDescriptor->Width, m_WindowDescriptor->Height, 0, 0, m_InstanceHandle, 0);
		}

		ShowWindow(m_WindowDescriptor->WindowHandle, SW_SHOW);
		SetForegroundWindow(m_WindowDescriptor->WindowHandle);

		if (m_RendererType == RendererType::D3D12) m_Renderer = new D3D12Renderer(m_WindowDescriptor);

		if (m_Renderer) m_Renderer->Initialise();
	}

	Window::~Window()
	{
		if (m_WindowDescriptor->Fullscreen) ChangeDisplaySettings(NULL, 0);

		DestroyWindow(m_WindowDescriptor->WindowHandle);
		m_WindowDescriptor->WindowHandle = NULL;

		UnregisterClass(m_WindowDescriptor->WindowTitle.c_str(), m_InstanceHandle);
		m_InstanceHandle = NULL;

		m_Renderer->Destroy();
		m_Renderer = 0;
		delete m_Renderer;
	}

	bool Window::Update()
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

	void Window::Render()
	{
		m_Renderer->Update();
		m_Renderer->Render();
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
