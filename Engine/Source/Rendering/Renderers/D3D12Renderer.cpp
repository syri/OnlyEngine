// Written by syri.
//
#include "D3D12Renderer.h"

#include <Application/WindowData.h>
#include <Rendering/D3D12Util.h>


namespace Engine
{
	CD3D12Renderer::CD3D12Renderer(SWindowDescriptor& InDescriptor)
		: IRenderer(InDescriptor), m_FrameIndex(0), m_renderTargetViewDescriptorSize(0)
		, m_bUseWarpDevice(false), m_FenceEvent(0), m_FenceValue(0)
	{}

	void CD3D12Renderer::Initialise()
	{
		LoadPipeline();
		LoadAssets();
	}

	void CD3D12Renderer::LoadPipeline()
	{
		unsigned int DXGIFactoryFlags = 0;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug> DebugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
		{
			DebugController->EnableDebugLayer();
			DXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif

		Microsoft::WRL::ComPtr<IDXGIFactory4> Factory;
		if (FAILED(CreateDXGIFactory2(DXGIFactoryFlags, IID_PPV_ARGS(&Factory))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create DXGI Factory."));
		}

		if (m_bUseWarpDevice)
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter> WarpAdapter;
			if (FAILED(Factory->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter))))
			{
				CLogger::Print(ELogType::Error, TEXT("Failed to enumerate the Warp Adapter."));
			}

			if (FAILED(D3D12CreateDevice(WarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device))))
			{
				CLogger::Print(ELogType::Error, TEXT("Failed to create the D3D12 Device."));
			}
		}
		else
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter1> HardwareAdapter;
			GetHardwareAdapter(Factory.Get(), &HardwareAdapter);

			if (FAILED(D3D12CreateDevice(HardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device))))
			{
				CLogger::Print(ELogType::Error, TEXT("Failed to create the D3D12 Device."));
			}
		}

		D3D12_COMMAND_QUEUE_DESC QueueDescriptor = {};
		QueueDescriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		QueueDescriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		if (FAILED(m_Device->CreateCommandQueue(&QueueDescriptor, IID_PPV_ARGS(&m_CommandQueue))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Command Queue."));
		}

		DXGI_SWAP_CHAIN_DESC1 SwapChainDescriptor = {};
		SwapChainDescriptor.BufferCount = s_FrameCount;
		SwapChainDescriptor.Width = 800;
		SwapChainDescriptor.Height = 600;
		SwapChainDescriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		SwapChainDescriptor.SampleDesc.Count = 1;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain1> SwapChain;
		if (FAILED(Factory->CreateSwapChainForHwnd(m_CommandQueue.Get(), Descriptor.Handle, &SwapChainDescriptor, nullptr, nullptr, &SwapChain)))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Swap Chain."));
		}

		// TODO: Fullscreen implementation
		if (FAILED(Factory->MakeWindowAssociation(Descriptor.Handle, DXGI_MWA_NO_ALT_ENTER)))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Window Association."));
		}

		if (FAILED(SwapChain.As(&m_SwapChain)))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to assign Swap Chain."));
		}
		m_FrameIndex = m_SwapChain->GetCurrentBackBufferIndex();

		D3D12_DESCRIPTOR_HEAP_DESC RenderTargetViewDescriptor = {};
		RenderTargetViewDescriptor.NumDescriptors = s_FrameCount;
		RenderTargetViewDescriptor.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		RenderTargetViewDescriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if (FAILED(m_Device->CreateDescriptorHeap(&RenderTargetViewDescriptor, IID_PPV_ARGS(&m_RenderTargetViewHeap))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Render Target View Descriptor Heap."));
		}
		m_renderTargetViewDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12U_CPU_DESCRIPTOR_HANDLE RenderTargetViewHandle(m_RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart());
		for (unsigned int BufferIndex = 0; BufferIndex < s_FrameCount; BufferIndex++)
		{
			if (FAILED(m_SwapChain->GetBuffer(BufferIndex, IID_PPV_ARGS(&m_renderTargets[BufferIndex]))))
			{
				CLogger::Print(ELogType::Error, TEXT("Failed to get Swap Chain Buffer"));
			}

			m_Device->CreateRenderTargetView(m_renderTargets[BufferIndex].Get(), nullptr, RenderTargetViewHandle);
			RenderTargetViewHandle.Offset(1, m_renderTargetViewDescriptorSize);
		}

		if (FAILED(m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CommandAllocator))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Command Allocator."));
		}
	}

	void CD3D12Renderer::LoadAssets()
	{
		if (FAILED(m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_CommandList))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Command List."));
		}

		if (FAILED(m_CommandList->Close()))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to close Command List"));
		}

		if (FAILED(m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence))))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to create Fence."));
		}
		m_FenceValue = 1;

		m_FenceEvent = CreateEvent(nullptr, false, false, nullptr);
		if (m_FenceEvent == nullptr)
		{
			if (FAILED(HRESULT_FROM_WIN32(GetLastError())))
			{
				CLogger::Print(ELogType::Error, TEXT("Error was thrown by the D3D12Renderer Fence."));
			}
		}
	}

	void CD3D12Renderer::Update()
	{
		//m_WindowDescriptor.ClearColour = FloatColour(((float)rand() / (RAND_MAX)), ((float)rand() / (RAND_MAX)), ((float)rand() / (RAND_MAX)), 1.0f);
	}

	void CD3D12Renderer::Render()
	{
		PopulateCommandList();

		ID3D12CommandList* CommandListPointer[] = { m_CommandList.Get() };
		m_CommandQueue->ExecuteCommandLists(_countof(CommandListPointer), CommandListPointer);

		if (FAILED(m_SwapChain->Present(1, 0)))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to present frame."));
		}

		WaitForPreviousFrame();
	}

	void CD3D12Renderer::Destroy()
	{
		WaitForPreviousFrame();
		CloseHandle(m_FenceEvent);
	}

	void CD3D12Renderer::PopulateCommandList()
	{
		if (FAILED(m_CommandAllocator->Reset()))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to reset Command Allocator."));
		}

		if (FAILED(m_CommandList->Reset(m_CommandAllocator.Get(), m_PipelineState.Get())))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to reset Command List."));
		}

		m_CommandList->ResourceBarrier(1, &D3D12U_RESOURCE_BARRIER::Transition(m_renderTargets[m_FrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		D3D12U_CPU_DESCRIPTOR_HANDLE RenderTargetViewHandle(m_RenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart(), m_FrameIndex, m_renderTargetViewDescriptorSize);

		float ClearColor[4] = { Descriptor.ClearColour.Red, Descriptor.ClearColour.Green, Descriptor.ClearColour.Blue, Descriptor.ClearColour.Alpha };
		m_CommandList->ClearRenderTargetView(RenderTargetViewHandle, ClearColor, 0, nullptr);

		m_CommandList->ResourceBarrier(1, &D3D12U_RESOURCE_BARRIER::Transition(m_renderTargets[m_FrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		if (FAILED(m_CommandList->Close()))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to close Command List."));
		}
	}

	void CD3D12Renderer::WaitForPreviousFrame()
	{
		// TODO: Implement Frame Buffering
		const unsigned __int64 Fence = m_FenceValue;
		if (FAILED(m_CommandQueue->Signal(m_Fence.Get(), Fence)))
		{
			CLogger::Print(ELogType::Error, TEXT("Failed to signal to D3D12Renderer Fence."));
		}
		m_FenceValue++;

		if (m_Fence->GetCompletedValue(), Fence)
		{
			if (FAILED(m_Fence->SetEventOnCompletion(Fence, m_FenceEvent)))
			{
				CLogger::Print(ELogType::Error, TEXT("Failed while waiting on Fence."));
			}
			WaitForSingleObject(m_FenceEvent, INFINITE);
		}

		m_FrameIndex = m_SwapChain->GetCurrentBackBufferIndex();
	}

	void CD3D12Renderer::GetHardwareAdapter(IDXGIFactory2* FactoryPointer, IDXGIAdapter1** AdapterPointer)
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
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
