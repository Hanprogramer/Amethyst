set_languages("c++23")

add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

includes("packages/libhat")

set_toolchains("msvc", {asm = "nasm"})

target("AmethystAPI")
    set_kind("static")
    set_default(false)

    add_files("src/**.cpp", "src/**.c", "include/**.cpp")

    add_files("src/**.asm")
        set_toolset("as", "nasm")
        add_asflags("-f win64", { force = true })

    add_defines("JSONCPP_VALUE_USE_INTERNAL_MAP=1")

    -- Deps
    add_deps("libhat")

    add_includedirs("include", "src", {public = true})
    add_headerfiles("src/**.hpp", "include/**.hpp", "include/**.h")