// Written by syri.
//
#pragma once
#include <Windows.h>
#include <iostream>
#include <shellapi.h>
#include <string.h>
#include <vector>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <wrl/client.h>

#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

// Internal
#include "API.h"
#include "Profiling/Logger.h"
