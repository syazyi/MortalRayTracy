add_rules("mode.debug", "mode.release")
add_requires("openmp")

set_languages("cxx17")
if is_mode("debug") then 
    add_cxflags("-DDEBUG")
    set_targetdir("bin/debug")
elseif is_mode("release") then 
    add_cxflags("-DNDEBUG")
    set_targetdir("bin/release")
end

--https://zhuanlan.zhihu.com/p/596605872
target("external")
    set_kind("shared")
    add_rules("utils.symbols.export_all", {export_classes = true})
    add_includedirs("src/ext/stb_image/", {public = true})
    add_files("src/ext/stb_image/**.cpp", { public = true  })
    add_includedirs("src/ext/objloader/", {public = true})
    add_files("src/ext/objloader/**.cpp", { public = true  })

target("scene")
    set_kind("static")
    add_packages("openmp")
    add_deps("external")
    add_includedirs("src/Core/math", {public = true })
    add_includedirs("src/Core/", {public = true })
    add_files("src/Core/**.cpp")

target("MortalRayTracer")
    set_kind("binary")
    add_packages("openmp")
    add_deps("scene")
    add_files("src/main.cpp")