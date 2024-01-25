project "glad"
    kind "SharedLib" -- dll
    language "C"
    staticruntime "off"
    warnings "off"

    targetdir ("bin/" .. output_dir .. "/%{prj.name}")
    objdir ("bin-int/" .. output_dir .. "/%{prj.name}")

    files {
        "include/glad/glad.h",
        "%{prj.location}/include/KHR/khrplatform.h",
        "%{prj.location}/src/glad.c",
    }
    includedirs {
        "%{prj.location}/include/"
    }

    defines {
        "GLAD_GLAPI_EXPORT",
        "GLAD_GLAPI_EXPORT_BUILD"
    }

    filter "system:windows"
        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../../../bin/" .. output_dir .. "/vxp")
        }

    filter "configurations:dbg"
        symbols "on"

    filter "configurations:rel"
        optimize "speed"
        symbols "off"

    filter "configurations:dist"
        optimize "speed"
        symbols "off"