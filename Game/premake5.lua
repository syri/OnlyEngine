-- Written by syri.
--
project "Game"
    targetname "Game"
    location "../Intermediates/ProjectFiles"
    language "C++"
    kind "ConsoleApp"

    files {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs {
        "Source",
        "../Engine/Source"
    }

    links { "Engine" }

    filter { "architecture:x64", "system:windows" }
        cppdialect "C++17"
        systemversion "latest"
        toolset "msc-v142"

        targetdir ("../Binaries/Win64")
        objdir ("../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")

        defines { "UMA_PLATFORM_WINDOWS" }

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
