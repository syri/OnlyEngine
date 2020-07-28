// Written by syri.
//
#pragma once


namespace Engine
{
	struct UMA_API SD3D12U_DEFAULT {};

	struct UMA_API SD3D12U_CPU_DESCRIPTOR_HANDLE : public D3D12_CPU_DESCRIPTOR_HANDLE
	{
		SD3D12U_CPU_DESCRIPTOR_HANDLE() = default;

		explicit SD3D12U_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other)
			: D3D12_CPU_DESCRIPTOR_HANDLE(Other)
		{}

		SD3D12U_CPU_DESCRIPTOR_HANDLE(SD3D12U_DEFAULT) { ptr = 0; }

		SD3D12U_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other, int OffsetScaledByIncrementSize)
		{
			InitOffsetted(Other, OffsetScaledByIncrementSize);
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other, int OffsetInDescriptors, unsigned int DescriptorIncrementSize)
		{
			InitOffsetted(Other, OffsetInDescriptors, DescriptorIncrementSize);
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE& Offset(int OffsetInDescriptors, unsigned int DescriptorIncrementSize)
		{
			ptr = unsigned __int64(__int64(ptr) + __int64(OffsetInDescriptors) * __int64(DescriptorIncrementSize));

			return *this;
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE& Offset(int OffsetScaledByIncrementSize)
		{
			ptr = unsigned __int64(__int64(ptr) + __int64(OffsetScaledByIncrementSize));

			return *this;
		}

		bool operator==(const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr == Other.ptr); }

		bool operator!=(const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr != Other.ptr); }

		SD3D12U_CPU_DESCRIPTOR_HANDLE& operator=(const D3D12_CPU_DESCRIPTOR_HANDLE& Other)
		{
			ptr = Other.ptr;

			return *this;
		}

		inline void InitOffsetted(const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int OffsetScaledByIncrementSize) { InitOffsetted(*this, Base, OffsetScaledByIncrementSize); }

		inline void InitOffsetted(const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int OffsetInDescriptors, unsigned int DescriptorIncrementSize)
		{
			InitOffsetted(*this, Base, OffsetInDescriptors, DescriptorIncrementSize);
		}

		static inline void InitOffsetted(D3D12_CPU_DESCRIPTOR_HANDLE& Handle, const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int OffsetScaledByIncrementSize)
		{
			Handle.ptr = unsigned __int64(__int64(Base.ptr) + __int64(OffsetScaledByIncrementSize));
		}

		static inline void InitOffsetted(D3D12_CPU_DESCRIPTOR_HANDLE& Handle, const D3D12_CPU_DESCRIPTOR_HANDLE& Base
			, int OffsetInDescriptors, unsigned int DescriptorIncrementSize)
		{
			Handle.ptr = unsigned __int64(__int64(Base.ptr) + __int64(OffsetInDescriptors) * __int64(DescriptorIncrementSize));
		}

	};

	struct UMA_API SD3D12U_RESOURCE_BARRIER : public D3D12_RESOURCE_BARRIER
	{
		SD3D12U_RESOURCE_BARRIER() = default;

		explicit SD3D12U_RESOURCE_BARRIER(const D3D12_RESOURCE_BARRIER& Other)
			: D3D12_RESOURCE_BARRIER(Other)
		{}

		static inline SD3D12U_RESOURCE_BARRIER Transition(ID3D12Resource* Resource, D3D12_RESOURCE_STATES StateBefore
			, D3D12_RESOURCE_STATES StateAfter, unsigned int Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
			, D3D12_RESOURCE_BARRIER_FLAGS Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE)
		{
			SD3D12U_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			Result.Flags = Flags;
			Barrier.Transition.pResource = Resource;
			Barrier.Transition.StateBefore = StateBefore;
			Barrier.Transition.StateAfter = StateAfter;
			Barrier.Transition.Subresource = Subresource;

			return Result;
		}

		static inline SD3D12U_RESOURCE_BARRIER Aliasing(ID3D12Resource* ResourceBefore, ID3D12Resource* ResourceAfter)
		{
			SD3D12U_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_ALIASING;
			Barrier.Aliasing.pResourceBefore = ResourceBefore;
			Barrier.Aliasing.pResourceAfter = ResourceAfter;

			return Result;
		}

		static inline SD3D12U_RESOURCE_BARRIER UAV(ID3D12Resource* Resource)
		{
			SD3D12U_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			Barrier.UAV.pResource = Resource;

			return Result;
		}

	};
}
