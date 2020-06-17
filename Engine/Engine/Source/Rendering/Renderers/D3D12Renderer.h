// Written by syri.
//
#pragma once
#include "Engine.h"
#include "Application/WindowData.h"
#include "Rendering/D3D12Util.h"
#include "Rendering/IRenderer.h"


namespace Engine
{
	class D3D12Renderer : public IRenderer
	{
	private:
		static const unsigned int m_FrameCount = 2;
		unsigned int m_renderTargetViewDescriptorSize;
		unsigned int m_FrameIndex;
		HANDLE m_FenceEvent;
		unsigned __int64 m_FenceValue;
		bool m_UseWarpDevice;

		Microsoft::WRL::ComPtr<IDXGISwapChain3> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[m_FrameCount];
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RenderTargetViewHeap;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PipelineState;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;

	public:
		PRAESEGMEN_API D3D12Renderer(WindowDescriptor* InWindowDescriptor);

		PRAESEGMEN_API void Initialise();
		PRAESEGMEN_API void Update();
		PRAESEGMEN_API void Render();
		PRAESEGMEN_API void Destroy();

		PRAESEGMEN_API void GetHardwareAdapter(IDXGIFactory2* FactoryPointer, IDXGIAdapter1** AdapterPointer);

	private:
		PRAESEGMEN_API void LoadPipeline();
		PRAESEGMEN_API void LoadAssets();
		PRAESEGMEN_API void PopulateCommandList();
		PRAESEGMEN_API void WaitForPreviousFrame();

	};
}
