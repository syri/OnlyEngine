// Written by syri.
//
#pragma once


#ifdef UMA_PLATFORM_WINDOWS
	#ifdef UMA_BUILD_DLL
		#define UMA_API __declspec(dllexport)
	#else
		#define UMA_API __declspec(dllimport)
	#endif
#else
	#error "Unsupported Platform Found!"
#endif


// Forward declarations.
namespace Engine
{
	enum class EColourType : uint32_t;
	enum class ELogType : uint32_t;
	enum class ERendererType : uint32_t;
	enum class EWindowMode : uint32_t;

	struct SColour;
	struct SRotator;
	struct STransform;
	struct SWindowDescriptor;
	struct SVector2;
	struct SVector3;
	struct SVector4;

	class IRenderer;

	class CApplication;
	class CD3D12Renderer;
	class CLogger;
	class CWindow;
}
