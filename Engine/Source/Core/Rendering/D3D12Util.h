// Written by syri.
//
#pragma once


namespace Engine
{
	struct PRAESEGMEN_API UD3D12_DEFAULT {};

	struct PRAESEGMEN_API UD3D12_CPU_DESCRIPTOR_HANDLE : public D3D12_CPU_DESCRIPTOR_HANDLE
	{
		UD3D12_CPU_DESCRIPTOR_HANDLE() = default;

		explicit UD3D12_CPU_DESCRIPTOR_HANDLE(const D3D12_CPU_DESCRIPTOR_HANDLE& Other) : D3D12_CPU_DESCRIPTOR_HANDLE(Other)
		{}

		UD3D12_CPU_DESCRIPTOR_HANDLE(UD3D12_DEFAULT) { ptr = 0; }

		UD3D12_CPU_DESCRIPTOR_HANDLE(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Other, INT OffsetScaledByIncrementSize)
		{
			InitOffsetted(Other, OffsetScaledByIncrementSize);
		}

		UD3D12_CPU_DESCRIPTOR_HANDLE(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Other, INT OffsetInDescriptors, UINT DescriptorIncrementSize)
		{
			InitOffsetted(Other, OffsetInDescriptors, DescriptorIncrementSize);
		}

		UD3D12_CPU_DESCRIPTOR_HANDLE& Offset(INT OffsetInDescriptors, UINT DescriptorIncrementSize)
		{
			ptr = SIZE_T(INT64(ptr) + INT64(OffsetInDescriptors) * INT64(DescriptorIncrementSize));
			return *this;
		}

		UD3D12_CPU_DESCRIPTOR_HANDLE& Offset(INT OffsetScaledByIncrementSize)
		{
			ptr = SIZE_T(INT64(ptr) + INT64(OffsetScaledByIncrementSize));
			return *this;
		}

		bool operator==(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr == Other.ptr); }

		bool operator!=(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Other) const { return (ptr != Other.ptr); }

		UD3D12_CPU_DESCRIPTOR_HANDLE& operator=(const D3D12_CPU_DESCRIPTOR_HANDLE& Other)
		{
			ptr = Other.ptr;
			return *this;
		}

		inline void InitOffsetted(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Base, INT OffsetScaledByIncrementSize) { InitOffsetted(*this, Base, OffsetScaledByIncrementSize); }

		inline void InitOffsetted(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Base, INT OffsetInDescriptors, UINT DescriptorIncrementSize)
		{
			InitOffsetted(*this, Base, OffsetInDescriptors, DescriptorIncrementSize);
		}

		static inline void InitOffsetted(_Out_ D3D12_CPU_DESCRIPTOR_HANDLE& Handle, _In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Base, INT OffsetScaledByIncrementSize)
		{
			Handle.ptr = SIZE_T(INT64(Base.ptr) + INT64(OffsetScaledByIncrementSize));
		}

		static inline void InitOffsetted(_Out_ D3D12_CPU_DESCRIPTOR_HANDLE& Handle, _In_ const D3D12_CPU_DESCRIPTOR_HANDLE& Base, INT OffsetInDescriptors, UINT DescriptorIncrementSize)
		{
			Handle.ptr = SIZE_T(INT64(Base.ptr) + INT64(OffsetInDescriptors) * INT64(DescriptorIncrementSize));
		}
	};

	struct PRAESEGMEN_API UD3D12_RESOURCE_BARRIER : public D3D12_RESOURCE_BARRIER
	{
		UD3D12_RESOURCE_BARRIER() = default;

		explicit UD3D12_RESOURCE_BARRIER(const D3D12_RESOURCE_BARRIER& Other) :
			D3D12_RESOURCE_BARRIER(Other)
		{}

		static inline UD3D12_RESOURCE_BARRIER Transition(_In_ ID3D12Resource* Resource, D3D12_RESOURCE_STATES StateBefore,
			D3D12_RESOURCE_STATES StateAfter, UINT Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, D3D12_RESOURCE_BARRIER_FLAGS Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE)
		{
			UD3D12_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			Result.Flags = Flags;
			Barrier.Transition.pResource = Resource;
			Barrier.Transition.StateBefore = StateBefore;
			Barrier.Transition.StateAfter = StateAfter;
			Barrier.Transition.Subresource = Subresource;
			return Result;
		}

		static inline UD3D12_RESOURCE_BARRIER Aliasing(_In_ ID3D12Resource* ResourceBefore, _In_ ID3D12Resource* ResourceAfter)
		{
			UD3D12_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_ALIASING;
			Barrier.Aliasing.pResourceBefore = ResourceBefore;
			Barrier.Aliasing.pResourceAfter = ResourceAfter;
			return Result;
		}

		static inline UD3D12_RESOURCE_BARRIER UAV(_In_ ID3D12Resource* Resource)
		{
			UD3D12_RESOURCE_BARRIER Result = {};
			D3D12_RESOURCE_BARRIER& Barrier = Result;
			Result.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
			Barrier.UAV.pResource = Resource;
			return Result;
		}
	};
}