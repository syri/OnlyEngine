-- Written by syri.
--
workspace "Praesegmen"
    architecture "x64"
    startproject "Game"

    configurations { "Development", "Release", "Shipping" }
    flags { "MultiProcessorCompile" }

group "Engine"
    include "Engine/Engine"
    include "Engine/EngineScript"
group ""

group "Project"
    include "Game/Game"
    include "Game/GameScript"
group ""

group "Tools"
    include "Tools/ProjectBuilder"
group ""
