-- Mod Options
local mod_name = "AmethystRuntime"
local major = 2
local minor = 0
local patch = 0

set_languages("c++23")
set_project(mod_name)
set_version(string.format("%d.%d.%d", major, minor, patch))

-- RelWithDebInfo flags
add_cxxflags("/O2", "/Zi", "/DNDEBUG", "/MD", "/EHsc", "/FS", "/MP")
add_ldflags("/DEBUG", "/OPT:REF", "/OPT:ICF", "/INCREMENTAL:NO", {force = true})
includes(path.join(os.getenv("AMETHYST_SRC"), "AmethystAPI"))

-- Use NASM for generated asm thunks
toolchain("nasm")
    set_kind("standalone")
    on_load(function (toolchain)
        toolchain:set_tools("as", "nasm")
    end)
toolchain_end()

-- Project dependencies
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
        table.insert(configs, "-DCMAKE_CXX_FLAGS=/GL")
        table.insert(configs, "-DCMAKE_EXE_LINKER_FLAGS=/LTCG")
        table.insert(configs, "-DCMAKE_SHARED_LINKER_FLAGS=/LTCG")
        table.insert(configs, "-DCMAKE_STATIC_LINKER_FLAGS=/LTCG")

        import("package.tools.cmake").install(package, configs)

        os.cp("include", package:installdir())
    end)
package_end()

add_requires("libhat", { system = false })

local amethystFolder = path.join(
    os.getenv("localappdata"),
    "Packages",
    "Microsoft.MinecraftUWP_8wekyb3d8bbwe",
    "LocalState",
    "games",
    "com.mojang",
    "amethyst"
)

set_targetdir(path.join(
    amethystFolder,
    "mods",
    string.format("%s@%d.%d.%d", mod_name, major, minor, patch)
))

target("AmethystRuntime")
    set_kind("shared")
    set_toolchains("nasm")
    add_deps("AmethystAPI")

    add_files(
        "src/**.cpp"
    )

    add_defines(
        string.format('MOD_VERSION="%d.%d.%d"', major, minor, patch),
        string.format('MOD_TARGET_VERSION_MAJOR=%d', major),
        string.format('MOD_TARGET_VERSION_MINOR=%d', minor),
        string.format('MOD_TARGET_VERSION_PATCH=%d', patch),
        'ENTT_PACKED_PAGE=128',
        'AMETHYST_EXPORTS'
    )

    -- Deps
    add_linkdirs("../AmethystAPI/lib")
    add_packages("AmethystAPI", "libhat")
    add_links("fmt")

    add_includedirs("C:/Users/blake/AppData/Local/.xmake/packages/l/libhat/@default/3c332be551f6485e8d17e1830ee49789/include")
    add_includedirs("include", "src", {public = true})
