project "AppFrame"
	kind "StaticLib"
	language "C++"
	targetdir ("../Build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../Build/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp"
	}

	defines {
	}


	includedirs {
		"%{prj.location}/src/",
		"%{IncludeDir.AL}",
		"%{IncludeDir.glew}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}", 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}"
	}

	libdirs {
		"%{LibraryDir.AL}",
		"%{LibraryDir.glew}",
		"%{LibraryDir.GLFW}"
	}	

	links {
		"glew32",
		"OpenAL32",
		"opengl32.lib",
		"glfw3_mt"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			--"ENGINE_PLATFORM_WINDOWS",
			"BUILD_ENGINE_DLL",
			"IMGUI_API=__declspec(dllexport)",
			"_WINDLL"
		}
		
		postbuildcommands {
			"{COPY} ../Build/bin/" .. outputdir .. "/%{prj.name}/*.dll ../Build/bin/" .. outputdir .. "/ArcticFox"
		}

		filter { "configurations:Debug" }
			runtime "Debug"
			defines "DEBUG"
			symbols "On"

		filter { "configurations:Release" }
			runtime "Release"
			defines "RELEASE"
			optimize "On"