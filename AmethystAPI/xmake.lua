set_languages("c++23")

add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})
add_linkdirs("lib")

toolchain("nasm")
    set_kind("standalone")
    on_load(function (toolchain)
        toolchain:set_tools("as", "nasm")
    end)
toolchain_end()

package("libhat")
    set_kind("static")
    add_urls("https://github.com/BasedInc/libhat.git")
    add_versions("commit", "3321c66b7e699e5585948bdb663c105efa48c680")
    add_deps("cmake")

    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_CXX_STANDARD=23")
        table.insert(configs, "-DCMAKE_CXX_STANDARD_REQUIRED=ON")
        table.insert(configs, "-DCMAKE_CXX_EXTENSIONS=OFF")
        table.insert(configs, "-DLIBHAT_TESTING=OFF")
        table.insert(configs, "-DLIBHAT_EXAMPLES=OFF")
        table.insert(configs, "-DLIBHAT_MODULE_TARGET=OFF")
        table.insert(configs, "-DLIBHAT_STATIC_C_LIB=OFF")
        table.insert(configs, "-DLIBHAT_SHARED_C_LIB=OFF")
        table.insert(configs, "-DLIBHAT_INSTALL_TARGET=ON")
        table.insert(configs, "-DCMAKE_CXX_FLAGS=/O2 /Zi /DNDEBUG /MD /EHsc /FS")

        import("package.tools.cmake").install(package, configs)
        os.cp("include", package:installdir())
    end)
package_end()

add_requires("libhat", { system = false })

target("AmethystAPI")
    set_kind("static")
    set_toolchains("nasm")

    add_files(
        "src/**.cpp",
        "src/**.c",
        "src/**.asm"
    )

    -- Deps
    add_packages("libhat")
    add_links("fmt")

    add_includedirs("C:/Users/blake/AppData/Local/.xmake/packages/l/libhat/@default/3c332be551f6485e8d17e1830ee49789/include")
    add_includedirs("include", "src", {public = true})

    add_headerfiles("src/**.hpp", "include/**.hpp", "include/**.h")