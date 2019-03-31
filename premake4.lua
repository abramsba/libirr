solution "libirr"
	configurations { "Debug", "Release" }
	configuration { "linux" }
		links { "Irrlicht", "GL", "Xxf86vm", "Xext", "X11", "Xcursor" }
		includedirs { "/usr/include/irrlicht" }
		libdirs { "/usr/lib" }
	configuration "Debug"
		flags { "Symbols" }
	configuration "Release"
		flags { "Optimize" }
	project "irr"
		kind "SharedLib"
		language "C++"
		files {
			"src/**.c",
			"src/**.h",
			"src/**.cpp",
			"src/**.hpp"
		}
