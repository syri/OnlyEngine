// Written by syri.
//
#include <EnginePCH.h>
#include "Window.h"

#include <Rendering/Renderers/Renderers.h>


namespace Engine
{
	CWindow::CWindow(int InID, SWindowDescriptor& InWindowDescriptor, const ERendererType InRHIRendererType)
		: ID(InID), WindowDescriptor(InWindowDescriptor), RHIRendererType(InRHIRendererType)
	{
		WNDCLASSEX WindowClass;
		DEVMODE ScreenSettings;
		
		ZeroMemory(&Message, sizeof(MSG));

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
		WindowClass.lpszClassName = WindowDescriptor.Title;
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&WindowClass);

		if (WindowDescriptor.Mode == EWindowMode::Fullscreen)
		{
			// Handle full screen display settings and window creation.
			WindowDescriptor.Width = GetSystemMetrics(SM_CXSCREEN);
			WindowDescriptor.Height = GetSystemMetrics(SM_CYSCREEN);

			memset(&ScreenSettings, 0, sizeof(ScreenSettings));
			ScreenSettings.dmSize = sizeof(ScreenSettings);
			ScreenSettings.dmPelsWidth = WindowDescriptor.Width;
			ScreenSettings.dmPelsHeight = WindowDescriptor.Height;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);

			WindowDescriptor.Handle = CreateWindowEx(WS_EX_APPWINDOW, WindowDescriptor.Title, WindowDescriptor.Title
				, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, WindowDescriptor.X, WindowDescriptor.Y
				, WindowDescriptor.Width, WindowDescriptor.Height, 0, 0, m_InstanceHandle, 0);
		}
		else
		{
			// Normal window creation.
			WindowDescriptor.X = (GetSystemMetrics(SM_CXSCREEN) - WindowDescriptor.Width) / 2;
			WindowDescriptor.Y = (GetSystemMetrics(SM_CYSCREEN) - WindowDescriptor.Height) / 2;

			WindowDescriptor.Handle = CreateWindowEx(WS_EX_APPWINDOW, WindowDescriptor.Title, WindowDescriptor.Title
				, WS_OVERLAPPEDWINDOW, WindowDescriptor.X, WindowDescriptor.Y, WindowDescriptor.Width, WindowDescriptor.Height, 0, 0, m_InstanceHandle, 0);
		}

		ShowWindow(WindowDescriptor.Handle, SW_SHOW);
		SetForegroundWindow(WindowDescriptor.Handle);

		if (RHIRendererType == ERendererType::D3D12) Renderer = new CD3D12Renderer(WindowDescriptor);

		if (Renderer) Renderer->Initialise();
	}

	CWindow::~CWindow()
	{
		if (WindowDescriptor.Mode == EWindowMode::Fullscreen) ChangeDisplaySettings(NULL, 0);

		DestroyWindow(WindowDescriptor.Handle);
		WindowDescriptor.Handle = NULL;

		UnregisterClass(WindowDescriptor.Title, m_InstanceHandle);
		m_InstanceHandle = NULL;

		Renderer->Destroy();
		Renderer = 0;
		delete Renderer;
	}

	bool CWindow::Update()
	{
		// Handle and dispatch messages.
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (Message.message == WM_QUIT) return false;

		return true;
	}

	void CWindow::Render()
	{
		Renderer->Update();
		Renderer->Render();
	}

	LRESULT CALLBACK CWindow::MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
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
