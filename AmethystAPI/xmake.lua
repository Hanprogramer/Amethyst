set_languages("c++23")

add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})

toolchain("nasm")
    set_kind("standalone")
    on_load(function (toolchain)
        toolchain:set_tools("as", "nasm")
    end)
toolchain_end()

includes("packages/libhat")

target("AmethystAPI")
    set_kind("static")
    set_toolchains("nasm")
    set_default(false)

    add_files(
        "src/**.cpp",
        "src/**.c"
    )

    add_files("src/**.asm", { sourcekind = "as" })

    -- Deps
    add_deps("libhat")

    add_includedirs("include", "src", {public = true})
    add_headerfiles("src/**.hpp", "include/**.hpp", "include/**.h")