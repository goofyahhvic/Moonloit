IncludeDir = {}
IncludeDir["glad"] = "external/glad/include/"
IncludeDir["spdlog"] = "submods/spdlog/include/"
IncludeDir["glm"] = "submods/glm/"

project "Moonloit"
    kind "StaticLib"

    staticruntime "off"

    language "C++"
    cppdialect "C++17"

    pchheader "mlt_pch.hpp"
    pchsource "src/Moonloit/mlt_pch.cpp"

    files {
        "include/**.hpp",
        "include/**.h",
        "src/**.hpp",
        "src/**.cpp",
		"src/**.h",
        "src/**.c"
    }
    includedirs {
        "src/",
        "src/Moonloit/",
        "include/",
        "include/Moonloit/",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}",
        os.getenv("VULKAN_SDK") .. "/Include/"
    }
	libdirs {
		os.getenv("VULKAN_SDK") .. "/Lib/"
	}
    links {
		"vulkan-1"
    }

    defines {
        "MLT_STATIC_LIB",
        "GLAD_GLAPI_EXPORT"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions {
            "/Zc:__cplusplus"
        }

        defines {
            "MLT_PLATFORM_WINDOWS"
        }

    filter "system:linux"
        systemversion "latest"
        toolset "clang"

        defines {
            "MLT_PLATFORM_LINUX"
        }

    filter "configurations:dbg"
        defines {
            "MLT_DEBUG",
            "MLT_ASSERTIONS_ENABLED"
        }
        symbols "On"
    filter "configurations:rel"
        defines {
            "MLT_RELEASE"
        }
        optimize "speed"
        symbols "off"
    filter "configurations:dist"
        defines {
            "MLT_DISTRIBUTION"
        }
        optimize "speed"
        symbols "off"