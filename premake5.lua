-- Written by Syri.
--
workspace "Prae"
    architecture "x64"
    configurations { "Development", "Release", "Shipping" }

project "Engine"
    location "Intermediates/ProjectFiles"
    kind "SharedLib"
    language "C++"
    targetname "Prae"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs { "Vendor/fmt/include" }

    filter "architecture:x64"
      targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
      objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines { "PRAE_PLATFORM_WINDOWS", "PRAE_BUILD_DLL" }
    
    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAE_DEBUG" }
        buildoptions "/MDd"
        symbols "ON"
    
    filter "configurations:Release"
        defines { "PRAE_RELEASE" }
        optimize "On"

    filter "configurations:Shipping"
        defines { "PRAE_SHIPPING" }
        optimize "On"

project "Game"
    location "Intermediates/ProjectFiles"
    kind "ConsoleApp"
    language "C++"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs
    {
        "Engine/Source",
        "Vendor/fmt/include"
    }

    links { "Engine" }

    filter "architecture:x64"
      targetdir ("Binaries/Win64/%{prj.name}/%{cfg.buildcfg}")
      objdir ("Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines { "PRAE_PLATFORM_WINDOWS" }

        postbuildcommands { "{COPY} ../../Binaries/Win64/Engine/%{cfg.buildcfg}/Prae.dll ../../Binaries/Win64/%{prj.name}/%{cfg.buildcfg}/" }

    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAE_DEBUG" }
        symbols "ON"

    filter "configurations:Release"
        defines { "PRAE_RELEASE" }
        optimize "On"

    filter "configurations:Shipping"
        defines { "PRAE_SHIPPING" }
        optimize "On"
