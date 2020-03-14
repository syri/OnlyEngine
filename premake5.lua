-- Written with ❤️ by Syri.
--
workspace "OnlyEngine"
    architecture "x64"
    configurations { "Development", "Release", "Shipping" }

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    filter "architecture:x64"
      targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
      objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS", "ENGINE_BUILD_DLL" }
    
    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "ENGINE_DEBUG" }
        symbols "ON"
    
    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        optimize "On"

    filter "configurations:Shipping"
        defines { "ENGINE_SHIPPING" }
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs { "Engine/Source" }

    links { "Engine" }

    filter "architecture:x64"
      targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
      objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines { "ENGINE_PLATFORM_WINDOWS" }

        postbuildcommands { "{COPY} ../Binaries/Win64/Engine/%{cfg.buildcfg}/Engine.dll ../Binaries/Win64/Sandbox/%{cfg.buildcfg}/" }

    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "ENGINE_DEBUG" }
        symbols "ON"

    filter "configurations:Release"
        defines { "ENGINE_RELEASE" }
        optimize "On"

    filter "configurations:Shipping"
        defines { "ENGINE_SHIPPING" }
        optimize "On"
