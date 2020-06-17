-- Written by syri.
--
project "Engine"
    targetname "Praesegmen"
    location "../../Intermediates/ProjectFiles"
    language "C++"
    kind "SharedLib"

    files {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs {
        "Source",
        "Vendor/Mono/include"
    }

    libdirs { "Vendor/Mono/lib" }

    links {
        "d3d12.lib",
        "dxgi.lib",
        "d3dcompiler.lib",
        "mono-2.0-sgen.lib"
    }

    filter { "architecture:x64", "system:windows" }
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "10.0.19631.0"
        toolset "msc-v142"

        targetdir ("../../Binaries/Win64")
        objdir ("../../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

        defines { "PRAESEGMEN_PLATFORM_WINDOWS", "PRAESEGMEN_BUILD_DLL" }

        postbuildcommands {
          "{COPY} ../../%{prj.name}/%{prj.name}/Vendor/Mono/bin/mono-2.0-sgen.dll ../../Binaries/Win64",
          "{COPY} ../../%{prj.name}/%{prj.name}/Vendor/Mono/lib/mono/4.5 ../../Binaries/Win64/Mono/lib/mono/4.5"
        }

    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAESEGMEN_BUILD_DEBUG" }
        symbols "ON"
        runtime "Debug"
    
    filter "configurations:Release"
        defines { "PRAESEGMEN_BUILD_RELEASE" }
        optimize "On"
        runtime "Release"

    filter "configurations:Shipping"
        defines { "PRAESEGMEN_BUILD_SHIPPING" }
        optimize "On"
        runtime "Release"
