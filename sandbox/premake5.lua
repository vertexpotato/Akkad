project "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}
	includedirs {
		"%{wks.location}/Akkad/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.box2d}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.json}",

	}

	links {
	"Akkad"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "AK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AK_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Debug"
		if _OPTIONS['target-emscripten'] then
				executable_suffix (".html")
				buildoptions   {"-s NO_DISABLE_EXCEPTION_CATCHING", "-s FORCE_FILESYSTEM=1", "-s USE_WEBGL2=1", "-s FULL_ES3=1", "-s OFFSCREEN_FRAMEBUFFER=1"}
				preload_dir = path.getabsolute("assets/")
				linkoptions    {"-s NO_DISABLE_EXCEPTION_CATCHING", "-s ALLOW_MEMORY_GROWTH", "-s USE_WEBGL2=1", "-s FULL_ES3=1", "-s OFFSCREEN_FRAMEBUFFER=1", "--preload-file " .. preload_dir .. "@assets", "-s FORCE_FILESYSTEM=1"}
		end