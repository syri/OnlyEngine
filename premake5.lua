-- Written by Syri.
--
workspace "Praesegmen"
    architecture "x64"
    configurations { "Development", "Release", "Shipping" }

project "Engine"
    location "Intermediates/ProjectFiles"
    kind "SharedLib"
    language "C++"
    targetname "Praesegmen"

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "Vendor/fmt/include",
        "Vendor/D3DX12"
    }

    links {
        "d3d12.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    filter "architecture:x64"
      targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
      objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines { "PRAESEGMEN_PLATFORM_WINDOWS", "PRAESEGMEN_BUILD_DLL" }
    
    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAESEGMEN_DEBUG" }
        symbols "ON"
    
    filter "configurations:Release"
        defines { "PRAESEGMEN_RELEASE" }
        optimize "On"

    filter "configurations:Shipping"
        defines { "PRAESEGMEN_SHIPPING" }
        optimize "On"

project "Game"
    location "Intermediates/ProjectFiles"
    kind "ConsoleApp"
    language "C++"

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "Engine/Source",
        "Vendor/fmt/include",
        "Vendor/D3DX12"
    }

    links { "Engine" }

    filter "architecture:x64"
        targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
        objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines { "PRAESEGMEN_PLATFORM_WINDOWS" }

        postbuildcommands {
          "IF EXIST ..\\..\\Binaries\\Win64\\$(ProjectName)\\Development\\Praesegmen.dll (del ..\\..\\Binaries\\Win64\\$(ProjectName)\\Development\\Praesegmen.dll)",
          "{COPY} ../../Binaries/Win64/Engine/%{cfg.buildcfg}/Praesegmen.dll ../../Binaries/Win64/%{prj.name}/%{cfg.buildcfg}/"
        }

    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAESEGMEN_DEBUG" }
        buildoptions "/MDd"
        symbols "ON"

    filter "configurations:Release"
        defines { "PRAESEGMEN_RELEASE" }
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Shipping"
        defines { "PRAESEGMEN_SHIPPING" }
        buildoptions "/MD"
        optimize "On"
