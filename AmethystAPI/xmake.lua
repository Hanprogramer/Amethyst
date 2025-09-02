set_languages("c++23")

add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

includes("packages/libhat")

set_toolchains("msvc", {asm = "nasm"})

target("AmethystAPI")
    set_kind("static")
    set_toolchains("nasm")
    set_default(false)

    add_files("src/**.cpp", "src/**.c")
    add_files("src/**.asm")

    -- Deps
    add_deps("libhat")

    add_includedirs("include", "src", {public = true})
    add_headerfiles("src/**.hpp", "include/**.hpp", "include/**.h")