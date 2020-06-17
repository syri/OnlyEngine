-- Written by syri.
--
project "ProjectBuilder"
    targetname "ProjectBuilder"
    namespace "ProjectBuilder"
    location "../../Intermediates/ProjectFiles"
    language "C#"
    dotnetframework "4.8"
    kind "ConsoleApp"

    files { "Source/**.cs" }

    links { "System" }

    filter { "architecture:x64", "system:windows" }
        targetdir ("../../Binaries/Win64/Tools")
        objdir ("../../Intermediates/Win64/%{prj.name}/%{cfg.buildcfg}")
