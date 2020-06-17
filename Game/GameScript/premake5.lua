-- Written by syri.
--
project "GameScript"
    targetname "GameScript"
    namespace "Game"
    location "../../Intermediates/ProjectFiles"
    language "C#"
    dotnetframework "4.8"
    kind "SharedLib"

    files { "Source/**.cs" }

    links { "EngineScript" }

    filter { "architecture:x64", "system:windows" }
        targetdir ("../../Binaries/Win64")
        objdir ("../../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")
