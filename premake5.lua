workspace "Alpha"
    startproject "Sandbox"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Alpha/vendor/GLFW/include"

include "Alpha/vendor/GLFW"

project "Alpha"
    location "Alpha"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "appch.h"
    pchsource "Alpha/src/appch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include;",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AP_BUILD_DLL",
            "AP_PLATFORM_WINDOWS"
        }
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ..\\bin\\" .. outputdir .. "\\Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
        "AP_DEBUG",
        "AP_ENABLE_ASSERTS"
        }
        symbols "On"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Alpha/vendor/spdlog/include",
        "Alpha/src"
    }

    links
    {
        "Alpha"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "AP_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "On"