-- Written by syri.
--
project "Game"
    targetname "Game"
    location "../../Intermediates/ProjectFiles"
    language "C++"
    kind "ConsoleApp"

    files {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs {
        "Source",
        "../../Engine/Engine/Source",
        "../../Engine/Engine/Vendor/Mono/include"
    }

    links { "Engine" }

    filter { "architecture:x64", "system:windows" }
        cppdialect "C++17"
        systemversion "10.0.19631.0"
        toolset "msc-v142"

        targetdir ("../../Binaries/Win64")
        objdir ("../../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

        defines { "PRAESEGMEN_PLATFORM_WINDOWS" }

    filter "configurations:Development"
        defines { "DEBUG", "TRACE", "PRAESEGMEN_BUILD_DEBUG" }
        buildoptions "/MDd"
        symbols "ON"
        runtime "Debug"

    filter "configurations:Release"
        defines { "PRAESEGMEN_BUILD_RELEASE" }
        buildoptions "/MD"
        optimize "On"
        runtime "Release"

    filter "configurations:Shipping"
        defines { "PRAESEGMEN_BUILD_SHIPPING" }
        buildoptions "/MD"
        optimize "On"
        runtime "Release"
