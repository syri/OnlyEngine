-- Written by syri.
--
project "Engine"
    targetname "Uma"
    location "../Intermediates/ProjectFiles"
    language "C++"
    kind "SharedLib"

    pchheader "EnginePCH.h"
    pchsource "Source/EnginePCH.cpp"

    files {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs {
        "Source"
    }

    links {
        "d3d12.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    filter { "architecture:x64", "system:windows" }
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"
        toolset "msc-v142"

        targetdir ("../Binaries/Win64")
        objdir ("../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

        defines { "UMA_PLATFORM_WINDOWS", "UMA_BUILD_DLL" }

    filter "configurations:Debug"
        defines { "DEBUG", "TRACE", "UMA_BUILD_DEBUG" }
        buildoptions "/MDd"
        symbols "On"
        runtime "Debug"

    filter "configurations:Development"
        defines { "TRACE", "UMA_BUILD_DEVELOPMENT" }
        buildoptions "/MD"
        symbols "On"
        optimize "On"
        runtime "Release"

    filter "configurations:Shipping"
        defines { "UMA_BUILD_SHIPPING" }
        buildoptions "/MD"
        symbols "Off"
        optimize "On"
        runtime "Release"
