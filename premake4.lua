solution "libirr"
	configurations { "Debug", "Release" }
	configuration { "linux" }
		links { "Irrlicht", "GL", "Xxf86vm", "Xext", "X11", "Xcursor", "BulletCollision", "BulletDynamics" }
		includedirs { "/usr/include/irrlicht", "/usr/include/bullet" }
		libdirs { "/usr/lib" }
	configuration { "macosx" }
		includedirs { "/usr/local/include/irrlicht", "/usr/local/include/bullet" }
		links { "Irrlicht", "BulletCollision", "BulletDynamics", "LinearMath", "/Library/Frameworks/OpenGL.framework", "/Library/Frameworks/AppKit.framework", "/Library/Frameworks/IOKit.framework" }
		libdirs { "/usr/local/lib" }
	configuration { "windows" }
		if os.getenv("IRR_INCLUDE_DIR") == nil then
			print("Warning (Windows builds): Environment variable IRR_INCLUDE_DIR has not been set")
		end
		if os.getenv("IRR_LIBRARY_DIR") == nil then
			print("Warning (Windows builds): Environment variable IRR_LIBRARY_DIR has not been set")
		end
		defines { "WINDOWS" }
		includedirs { os.getenv("IRR_INCLUDE_DIR") }
		links { "Irrlicht" }
		libdirs { os.getenv("IRR_LIBRARY_DIR") }
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
