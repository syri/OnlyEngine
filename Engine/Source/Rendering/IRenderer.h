// Written by syri.
//
#pragma once
#include <Engine.h>


namespace Engine
{
	struct SWindowDescriptor;

	enum class UMA_API ERendererType : unsigned int
	{
		D3D12 = 1,
		Vulkan
	};

	class UMA_API IRenderer
	{
	public:
		SWindowDescriptor& Descriptor;

	public:
		IRenderer(SWindowDescriptor& InDescriptor);
		virtual ~IRenderer() {}

		virtual void Initialise() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;

		// TODO: Generic types for hardware adapters.
		virtual void GetHardwareAdapter(IDXGIFactory2* FactoryPointer, IDXGIAdapter1** AdapterPointer) = 0;

	private:
		virtual void LoadPipeline() = 0;
		virtual void LoadAssets() = 0;
		virtual void PopulateCommandList() = 0;
		virtual void WaitForPreviousFrame() = 0;

	};
}
