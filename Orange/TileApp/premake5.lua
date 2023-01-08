project "TileApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir(bin_dir)
	objdir(bin_int_dir)

	pchheader("pch.h")	
	pchsource("src/pch.cpp")

	files
	{
		"src/**.cpp",
		"src/**.h",
	}

	orange = sln .. "Orange/"

	includedirs
	{
		"src",
		orange .. "src",
		orange .. "dependencies/spdlog/include",
	}

	links
	{
		"Orange",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TILEAPP_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "TILEAPP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "TILEAPP_RELEASE"
		runtime "Release"
		symbols "on"