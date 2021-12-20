workspace "GamE"
   configurations { "Debug", "Release" }
   architecture "x64"
   startproject "Sandbox"

---------------------------------------------

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

---------------------------------------------

-- include "**/premake5.lua"

project "GamE"
   location "GamE"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-tmp/" .. outputdir .. "/%{prj.name}")
   staticruntime "on"
   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }
   includedirs
   {
      --"%{prj.name}/module/spdlog/include",
      "%{prj.name}/src"
   }
   pchheader "pch.h"
   pchsource "%{prj.name}/src/pch.cpp"

   filter "system:windows"
        systemversion "latest"
        defines { "GE_WINDOWS" }

   filter "configurations:Debug"
      defines { "GE_DEBUG" }
      runtime "Debug"
      symbols "On"
   filter "configurations:Release"
      defines { "GE_RELEASE" }
      runtime "Release"
      optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-tmp/" .. outputdir .. "/%{prj.name}")
   staticruntime "on"
   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }
   includedirs
   {
      "%{wks.location}/GamE/module/spdlog/include",
      "%{wks.location}/GamE/src",
      "%{wks.location}/GamE/module"
   }
   links
   {
      "GamE"
   }

   filter "system:windows"
        systemversion "latest"
        defines { "GE_WINDOWS" }
   filter "configurations:Debug"
      defines { "GE_DEBUG" }
      runtime "Debug"
      symbols "On"
   filter "configurations:Release"
      defines { "GE_RELEASE" }
      runtime "Release"
      optimize "On"