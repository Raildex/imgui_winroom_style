set_project("trle-imgui")
set_version("0.1.0")
set_xmakever("2.8.0")

add_rules("mode.debug", "mode.release")
set_languages("c++17")
set_warnings("all")

-- Dear ImGui from xmake-repo, built with the GLFW + OpenGL3 backends.
-- GLFW is pulled in automatically as a dependency of the imgui package.
add_requires("imgui", {configs = {glfw = true, opengl3 = true}})

-- Reusable style library: drop this target into any ImGui project
target("trle_style")
    set_kind("static")
    add_files("src/trle_style.cpp")
    add_headerfiles("src/trle_style.h")
    add_includedirs("src", {public = true})
    add_packages("imgui", {public = true})

-- Demo application
target("trle_demo")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("trle_style")
    add_packages("imgui")

    if is_plat("windows") then
        add_syslinks("opengl32", "user32", "gdi32", "shell32")
        -- Use the console-less subsystem in release builds
        if is_mode("release") then
            add_ldflags("/SUBSYSTEM:WINDOWS", "/ENTRY:mainCRTStartup", {force = true})
        end
    elseif is_plat("macosx") then
        add_frameworks("OpenGL", "Cocoa", "IOKit")
    elseif is_plat("linux") then
        add_syslinks("GL", "dl", "pthread")
    end
