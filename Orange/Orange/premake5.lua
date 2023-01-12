
group "Dependencies"
	include "dependencies/GLFW"
	include "dependencies/Glad"
group ""

project "Orange"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir(bin_dir)
	objdir(bin_int_dir)
	
	pchheader("pchOrange.h")	
	pchsource("src/pchOrange.cpp")

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		"src/Orange",
		"dependencies/stb_image",
		"dependencies/spdlog/include",
		"dependencies/GLFW/include",
		"dependencies/Glad/include",
	}

	links
	{
		"GLFW",
		"Glad",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ORANGE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "ORANGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "ORANGE_RELEASE"
		runtime "Release"
		symbols "on"