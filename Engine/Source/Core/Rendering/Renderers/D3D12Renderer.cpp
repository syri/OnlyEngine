// Written by syri.
//
#include "D3D12Renderer.h"


namespace Engine
{
	D3D12Renderer::D3D12Renderer(WindowDescriptor* InWindowDescriptor)
		: IRenderer(InWindowDescriptor), m_FrameIndex(0), m_renderTargetViewDescriptorSize(0),
		m_UseWarpDevice(false), m_FenceEvent(0), m_FenceValue(0)
	{}

	void D3D12Renderer::Initialise()
	{
		LoadPipeline();
		LoadAssets();
	}

	void D3D12Renderer::LoadPipeline()
	{
		unsigned int DXGIFactoryFlags = 0;

#ifdef _DEBUG
		ComPtr<ID3D12Debug> DebugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
		{
			DebugController->EnableDebugLayer();
			DXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif

		ComPtr<IDXGIFactory4> Factory;
		if (FAILED(CreateDXGIFactory2(DXGIFactoryFlags, IID_PPV_ARGS(&Factory))))
		{
			Logger::Print(LogType::Error, true, "Failed to create DXGI Factory.");
		}

		if (m_UseWarpDevice)
		{
			ComPtr<IDXGIAdapter> WarpAdapter;
			if (FAILED(Factory->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter))))
			{
				Logger::Print(LogType::Error, true, "Failed to enumerate the Warp Adapter.");
			}

			if (FAILED(D3D12CreateDevice(WarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device))))
			{
				Logger::Print(LogType::Error, true, "Failed to create the D3D12 Device.");
			}
		}
		else
		{
			ComPtr<IDXGIAdapter1> HardwareAdapter;
			GetHardwareAdapter(Factory.Get(), &HardwareAdapter);

			if (FAILED(D3D12CreateDevice(HardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device))))
			{
				Logger::Print(LogType::Error, true, "Failed to create the D3D12 Device.");
			}
		}

		D3D12_COMMAND_QUEUE_DESC QueueDescriptor = {};
		QueueDescriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		QueueDescriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		if (FAILED(m_Device->CreateCommandQueue(&QueueDescriptor, IID_PPV_ARGS(&m_CommandQueue))))
		{
			Logger::Print(LogType::Error, true, "Failed to create Command Queue.");
		}

		DXGI_SWAP_CHAIN_DESC1 SwapChainDescriptor = {};
		SwapChainDescriptor.BufferCount = m_FrameCount;
		SwapChainDescriptor.Width = 800;
		SwapChainDescriptor.Height = 600;
		SwapChainDescriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		SwapChainDescriptor.SampleDesc.Count = 1;
		

		ComPtr<IDXGISwapChain1> SwapChain;
		if (FAILED(Factory->CreateSwapChainForHwnd(m_CommandQueue.Get(), m_WindowDescriptor->WindowHandle, &SwapChainDescriptor, nullptr, nullptr, &SwapChain)))
		{
			Logger::Print(LogType::Error, true, "Failed to create Swap Chain.");
		}

		// TODO: Fullscreen implementation
		if (FAILED(Factory->MakeWindowAssociation(m_WindowDescriptor->WindowHandle, DXGI_MWA_NO_ALT_ENTER)))
		{
			Logger::Print(LogType::Error, true, "Failed to create Window Association.");
		}

		if (FAILED(SwapChain.As(&m_SwapChain)))
		{
			Logger::Print(LogType::Error, true, "Failed to assign Swap Chain.");
		}
		m_FrameIndex = m_SwapChain->GetCurrentBackBufferIndex();

		D3D12_DESCRIPTOR_HEAP_DESC RenderTargetViewDescriptor = {};
		RenderTargetViewDescriptor.NumDescriptors = m_FrameCount;
		RenderTargetViewDescriptor.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		RenderTargetViewDescriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(m_Device->CreateDescriptorHeap(&RenderTargetViewDescriptor, IID_PPV_ARGS(&m_RenderTargetViewHeap))))
		{
			Logger::Print(LogType::Error, true, "Failed to create Render Target View Descriptor Heap.");
		}
		m_renderTargetViewDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12U_CPU_DESCRIPTOR_HANDLE RenderTargetViewHandle(m_RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart());
		for (unsigned int BufferIndex = 0; BufferIndex < m_FrameCount; BufferIndex++)
		{
			if (FAILED(m_SwapChain->GetBuffer(BufferIndex, IID_PPV_ARGS(&m_renderTargets[BufferIndex]))))
			{
				Logger::Print(LogType::Error, true, "Failed to get Swap Chain Buffer");
			}

			m_Device->CreateRenderTargetView(m_renderTargets[BufferIndex].Get(), nullptr, RenderTargetViewHandle);
			RenderTargetViewHandle.Offset(1, m_renderTargetViewDescriptorSize);
		}

		if (FAILED(m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CommandAllocator))))
		{
			Logger::Print(LogType::Error, true, "Failed to create Command Allocator.");
		}
	}

	void D3D12Renderer::LoadAssets()
	{
		if (FAILED(m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_CommandList))))
		{
			Logger::Print(LogType::Error, true, "Failed to create Command List.");
		}

		if (FAILED(m_CommandList->Close()))
		{
			Logger::Print(LogType::Error, true, "Failed to close Command List");
		}

		if (FAILED(m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence))))
		{
			Logger::Print(LogType::Error, true, "Failed to create Fence.");
		}
		m_FenceValue = 1;

		m_FenceEvent = CreateEvent(nullptr, false, false, nullptr);
		if (m_FenceEvent == nullptr)
		{
			if (FAILED(HRESULT_FROM_WIN32(GetLastError())))
			{
				Logger::Print(LogType::Error, true, "Error was thrown by the D3D12Renderer Fence.");
			}
		}
	}

	void D3D12Renderer::Update()
	{
		// TODO
	}

	void D3D12Renderer::Render()
	{
		PopulateCommandList();

		ID3D12CommandList* CommandListPointer[] = { m_CommandList.Get() };
		m_CommandQueue->ExecuteCommandLists(_countof(CommandListPointer), CommandListPointer);

		if (FAILED(m_SwapChain->Present(1, 0)))
		{
			Logger::Print(LogType::Error, true, "Failed to present frame.");
		}

		WaitForPreviousFrame();
	}

	void D3D12Renderer::Destroy()
	{
		WaitForPreviousFrame();
		CloseHandle(m_FenceEvent);
	}

	void D3D12Renderer::PopulateCommandList()
	{
		if (FAILED(m_CommandAllocator->Reset()))
		{
			Logger::Print(LogType::Error, true, "Failed to reset Command Allocator.");
		}

		if (FAILED(m_CommandList->Reset(m_CommandAllocator.Get(), m_PipelineState.Get())))
		{
			Logger::Print(LogType::Error, true, "Failed to reset Command List.");
		}

		m_CommandList->ResourceBarrier(1, &D3D12U_RESOURCE_BARRIER::Transition(m_renderTargets[m_FrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		D3D12U_CPU_DESCRIPTOR_HANDLE RenderTargetViewHandle(m_RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart(), m_FrameIndex, m_renderTargetViewDescriptorSize);

		float ClearColor[4] = { m_WindowDescriptor->ClearColour.Red, m_WindowDescriptor->ClearColour.Green, m_WindowDescriptor->ClearColour.Blue, m_WindowDescriptor->ClearColour.Alpha };
		m_CommandList->ClearRenderTargetView(RenderTargetViewHandle, ClearColor, 0, nullptr);

		m_CommandList->ResourceBarrier(1, &D3D12U_RESOURCE_BARRIER::Transition(m_renderTargets[m_FrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		if (FAILED(m_CommandList->Close()))
		{
			Logger::Print(LogType::Error, true, "Failed to close Command List.");
		}
	}

	void D3D12Renderer::WaitForPreviousFrame()
	{
		// TODO: Implement Frame Buffering
		const unsigned __int64 Fence = m_FenceValue;
		if (FAILED(m_CommandQueue->Signal(m_Fence.Get(), Fence)))
		{
			Logger::Print(LogType::Error, true, "Failed to signal to D3D12Renderer Fence.");
		}
		m_FenceValue++;

		if (m_Fence->GetCompletedValue(), Fence)
		{
			if (FAILED(m_Fence->SetEventOnCompletion(Fence, m_FenceEvent)))
			{
				Logger::Print(LogType::Error, true, "Failed while waiting on Fence.");
			}
			WaitForSingleObject(m_FenceEvent, INFINITE);
		}

		m_FrameIndex = m_SwapChain->GetCurrentBackBufferIndex();
	}

	void D3D12Renderer::GetHardwareAdapter(IDXGIFactory2* FactoryPointer, IDXGIAdapter1** AdapterPointer)
	{
		ComPtr<IDXGIAdapter1> Adapter;
		*AdapterPointer = nullptr;

		for (unsigned int AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != FactoryPointer->EnumAdapters1(AdapterIndex, &Adapter); ++AdapterIndex)
		{
			DXGI_ADAPTER_DESC1 AdapterDescription;
			Adapter->GetDesc1(&AdapterDescription);

			// Don't use Software rendering adapter.
			if (AdapterDescription.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

			if (SUCCEEDED(D3D12CreateDevice(Adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) break;
		}

		*AdapterPointer = Adapter.Detach();
	}
}