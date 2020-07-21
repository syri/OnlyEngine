// Written by syri.
//
#pragma once
#include <Engine.h>
#include <Application/Application.h>
#include <Application/WindowData.h>
#include <Math/Colour.h>


namespace Engine
{
	enum class ERendererType : unsigned int;
	class IRenderer;

	class UMA_API CWindow
	{
	public:
		const int ID;

		SWindowDescriptor& Descriptor;
		
		MSG Message;

		ERendererType RHIRendererType;
		IRenderer* Renderer;

	private:
		HINSTANCE m_InstanceHandle;

	public:
		CWindow(int InID, SWindowDescriptor& InDescriptor, const ERendererType InRHIRendererType);
		~CWindow();

		bool Update();
		void Render();
		
		static LRESULT CALLBACK MessageHandler(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);

	};
}
