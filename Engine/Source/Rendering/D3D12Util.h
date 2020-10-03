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

		SD3D12U_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other, int32_t OffsetScaledByIncrementSize)
		{
			InitOffsetted(Other, OffsetScaledByIncrementSize);
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other, int32_t OffsetInDescriptors, uint32_t DescriptorIncrementSize)
		{
			InitOffsetted(Other, OffsetInDescriptors, DescriptorIncrementSize);
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE& Offset(int32_t OffsetInDescriptors, uint32_t DescriptorIncrementSize)
		{
			ptr = uint64_t(int64_t(ptr) + int64_t(OffsetInDescriptors) * int64_t(DescriptorIncrementSize));

			return *this;
		}

		SD3D12U_CPU_DESCRIPTOR_HANDLE& Offset(int32_t OffsetScaledByIncrementSize)
		{
			ptr = uint64_t(int64_t(ptr) + int64_t(OffsetScaledByIncrementSize));

			return *this;
		}

		bool operator==(const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr == Other.ptr); }

		bool operator!=(const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr != Other.ptr); }

		SD3D12U_CPU_DESCRIPTOR_HANDLE& operator=(const D3D12_CPU_DESCRIPTOR_HANDLE& Other)
		{
			ptr = Other.ptr;

			return *this;
		}

		inline void InitOffsetted(const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int32_t OffsetScaledByIncrementSize) { InitOffsetted(*this, Base, OffsetScaledByIncrementSize); }

		inline void InitOffsetted(const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int32_t OffsetInDescriptors, uint32_t DescriptorIncrementSize)
		{
			InitOffsetted(*this, Base, OffsetInDescriptors, DescriptorIncrementSize);
		}

		static inline void InitOffsetted(D3D12_CPU_DESCRIPTOR_HANDLE& Handle, const D3D12_CPU_DESCRIPTOR_HANDLE& Base, int32_t OffsetScaledByIncrementSize)
		{
			Handle.ptr = uint64_t(int64_t(Base.ptr) + int64_t(OffsetScaledByIncrementSize));
		}

		static inline void InitOffsetted(D3D12_CPU_DESCRIPTOR_HANDLE& Handle, const D3D12_CPU_DESCRIPTOR_HANDLE& Base
			, int32_t OffsetInDescriptors, uint32_t DescriptorIncrementSize)
		{
			Handle.ptr = uint64_t(int64_t(Base.ptr) + int64_t(OffsetInDescriptors) * int64_t(DescriptorIncrementSize));
		}

	};

	struct UMA_API SD3D12U_RESOURCE_BARRIER : public D3D12_RESOURCE_BARRIER
	{
		SD3D12U_RESOURCE_BARRIER() = default;

		explicit SD3D12U_RESOURCE_BARRIER(const D3D12_RESOURCE_BARRIER& Other)
			: D3D12_RESOURCE_BARRIER(Other)
		{}

		static inline SD3D12U_RESOURCE_BARRIER Transition(ID3D12Resource* Resource, D3D12_RESOURCE_STATES StateBefore
			, D3D12_RESOURCE_STATES StateAfter, uint32_t Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES
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
