workspace "Pelinjan"

	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
project "Pelinjan"
	location "Pelinjan"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
		defines
		{
			-- preprocessor definitions
			"PE_PLATFORM_WINDOWS",
			"PE_BUILD_DLL"
		}
	
		postbuildcommands
		{
			-- copy everything in Pelinjan\bin\[outputdir] into Sandbox - for now that's the Pelinjan.dll
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
		filter "configurations:Debug"
			defines "PE_DEBUG"
			symbols "On"
		
		filter "configurations:Release"
			defines "PE_RELEASE"
			optimize "On"
		
		filter "configurations:Dist"
			defines "PE_DIST"
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
		"Pelinjan/vendor/spdlog/include",
		"Pelinjan/src"
	}
	
	links
	{
		"Pelinjan"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
		defines
		{
			-- preprocessor definitions
			"PE_PLATFORM_WINDOWS"
		}
	
		filter "configurations:Debug"
			defines "PE_DEBUG"
			symbols "On"
		
		filter "configurations:Release"
			defines "PE_RELEASE"
			optimize "On"
		
		filter "configurations:Dist"
			defines "PE_DIST"
			optimize "On"