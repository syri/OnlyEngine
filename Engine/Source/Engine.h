// Written by syri.
//
#pragma once
// External
#ifndef FMT_HEADER_ONLY
	#define FMT_HEADER_ONLY
#endif
#include <fmt/color.h>
#include <iostream>
#include <shellapi.h>
#include <string.h>
#include <vector>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <wrl/client.h>

#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3dx12.h>

// Internal
#include "EngineDefinitions.h"
#include "Core/API.h"
