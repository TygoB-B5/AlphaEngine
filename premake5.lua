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
IncludeDir["glm"] = "Alpha/vendor/glm"

include "Alpha/vendor/GLFW"
include "Alpha/vendor/Glad"
include "Alpha/vendor/imgui"

project "Alpha"
    location "Alpha"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "appch.h"
    pchsource "Alpha/src/appch.cpp"

    flags
    {
        "FatalWarnings"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include;",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "AP_BUILD_DLL",
            "AP_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines
        {
        "AP_DEBUG",
        "AP_ENABLE_ASSERTS"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "on"
        runtime "Release"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "on"
        runtime "Release"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    cppdialect "C++17"
    staticruntime "on"

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
        "Alpha/src",
        "Alpha/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Alpha"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "AP_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AP_DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "AP_RELEASE"
        optimize "on"
        runtime "Release"

    filter "configurations:Dist"
        defines "AP_DIST"
        optimize "on"
        runtime "Release"