project "OrangeEditor"
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
		orange .. "src/Orange",
		orange .. "dependencies/spdlog/include",
		orange .. "dependencies/ImGui",
	}

	links
	{
		"Orange",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ORANGE_EDITOR_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "ORANGE_EDITOR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "ORANGE_EDITOR_RELEASE"
		runtime "Release"
		symbols "on"