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
IncludeDir["Glad"] = "Alpha/vendor/Glad/include"
IncludeDir["ImGui"] = "Alpha/vendor/imgui"

include "Alpha/vendor/GLFW"
include "Alpha/vendor/Glad"
include "Alpha/vendor/imgui"

project "Alpha"
    location "Alpha"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "AP_BUILD_DLL",
            "AP_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
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
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "On"
        runtime "Release"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        runtime "Debug"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "On"
        runtime "Release"