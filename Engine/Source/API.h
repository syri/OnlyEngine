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
	enum class EColourType : unsigned int;
	enum class ELogType : unsigned int;
	enum class ERendererType : unsigned int;
	enum class EWindowMode : unsigned int;

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
