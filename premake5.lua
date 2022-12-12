workspace "iw4x-validator"
startproject "iw4x-validator"
location "./build"
objdir "%{wks.location}/obj"
targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

configurations {"Debug", "Release"}

if os.istarget("darwin") then
	platforms {"x64", "arm64"}
else
	platforms {"x86", "x64"}
end

filter "platforms:x86"
	architecture "x86"
filter {}

filter "platforms:x64"
	architecture "x86_64"
filter {}

filter "platforms:arm64"
	architecture "ARM64"
filter {}

filter {"language:C++", "toolset:not msc*"}
	buildoptions "-std=c++14"
filter {}

filter "toolset:msc*"
	buildoptions "/std:c++14"
filter {}

filter {"system:windows"}
	systemversion "latest"
filter {}

filter {"system:macosx"}
	systemversion "12.0"
filter {}

symbols "On"
staticruntime "On"
editandcontinue "Off"
warnings "Extra"
characterset "ASCII"

if os.istarget("linux") or os.istarget("darwin") then
	buildoptions "-pthread"
	linkoptions "-pthread"
end

if os.getenv("CI") then
	defines "CI"
end

flags {"NoIncrementalLink", "NoMinimalRebuild", "MultiProcessorCompile", "No64BitChecks"}

filter "configurations:Release"
	optimize "Speed"
	defines "NDEBUG"
	flags "FatalCompileWarnings"
filter {}

filter "configurations:Debug"
	optimize "Debug"
	defines {"DEBUG", "_DEBUG"}
filter {}

project "iw4x-validator"
kind "ConsoleApp"
language "C++"

pchheader "std_include.hpp"
pchsource "src/std_include.cpp"

files {"./src/**.hpp", "./src/**.cpp"}

includedirs {"./src", "%{prj.location}/src"}

filter {"system:windows", "toolset:not msc*"}
	resincludedirs {
		"%{_MAIN_SCRIPT_DIR}/src"
	}
filter {}

filter {"system:windows", "toolset:msc*"}
	linkoptions {"/IGNORE:4254", "/SAFESEH:NO", "/LARGEADDRESSAWARE", "/PDBCompress"}
	resincludedirs {
		"$(ProjectDir)src"
	}
filter {}
