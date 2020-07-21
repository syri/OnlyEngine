-- Written by syri.
--
workspace "Uma"
    architecture "x64"
    startproject "Game"

    configurations { "Debug", "Development", "Shipping" }
    flags { "MultiProcessorCompile" }

group "Engine"
    include "Engine"
group ""

group "Projects"
    include "Game"
group ""

group "Tools"
    include "Tools/ProjectBuilder"
group ""
