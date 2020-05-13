// Written by syri.
//
#pragma once
#include "../../../Engine.h"
#include "../../Application/WindowData.h"
#include "../D3D12Util.h"
#include "../IRenderer.h"


using Microsoft::WRL::ComPtr;

namespace Engine
{
	class PRAESEGMEN_API D3D12Renderer : public IRenderer
	{
	private:
		static const unsigned int m_FrameCount = 2;
		unsigned int m_renderTargetViewDescriptorSize;
		unsigned int m_FrameIndex;
		HANDLE m_FenceEvent;
		unsigned __int64 m_FenceValue;
		bool m_UseWarpDevice;

		ComPtr<IDXGISwapChain3> m_SwapChain;
		ComPtr<ID3D12Device> m_Device;
		ComPtr<ID3D12Resource> m_renderTargets[m_FrameCount];
		ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
		ComPtr<ID3D12CommandQueue> m_CommandQueue;
		ComPtr<ID3D12DescriptorHeap> m_RenderTargetViewHeap;
		ComPtr<ID3D12PipelineState> m_PipelineState;
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		ComPtr<ID3D12Fence> m_Fence;

	public:
		D3D12Renderer(WindowDescriptor* InWindowDescriptor);

		void Initialise();
		void Update();
		void Render();
		void Destroy();

		void GetHardwareAdapter(IDXGIFactory2* FactoryPointer, IDXGIAdapter1** AdapterPointer);

	private:
		void LoadPipeline();
		void LoadAssets();
		void PopulateCommandList();
		void WaitForPreviousFrame();

	};
}
