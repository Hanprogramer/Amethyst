-- Mod Options
local mod_name = "AmethystRuntime"
local modMajor = 2
local modMinor = 0
local modPatch = 0

-- Minecraft version
local major = 1
local minor = 21
local patch = 3

set_languages("c++23")
set_project(mod_name)
set_version(string.format("%d.%d.%d", modMajor, modMinor, modPatch))

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
        table.insert(configs, "-DCMAKE_CXX_FLAGS=/O2 /Zi /DNDEBUG /MD /EHsc /FS")

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

local modFolder = path.join(
    amethystFolder,
    "mods",
    string.format("%s@%d.%d.%d", mod_name, modMajor, modMinor, modPatch)
)

set_symbols("debug")
set_targetdir(modFolder)

target("AmethystRuntime")
    set_kind("shared")
    set_toolchains("nasm")
    add_deps("AmethystAPI", {public = true})
    set_default(true)

    add_files(
        "src/**.cpp"
    )

    add_defines(
        string.format('MOD_VERSION="%d.%d.%d"', modMajor, modMinor, modPatch),
        string.format('MOD_TARGET_VERSION_MAJOR=%d', major),
        string.format('MOD_TARGET_VERSION_MINOR=%d', minor),
        string.format('MOD_TARGET_VERSION_PATCH=%d', patch),
        'ENTT_PACKED_PAGE=128',
        'AMETHYST_EXPORTS'
    )

    -- Deps
    add_packages("AmethystAPI", "libhat")

    local localAppData = os.getenv("LOCALAPPDATA")

    -- need to figure out how to fix this shit lmao
    add_links("user32", "oleaut32", "windowsapp", 
        path.join(localAppData, ".xmake/packages/l/libhat/@default/3c332be551f6485e8d17e1830ee49789/lib/libhat"))
    add_includedirs(
        path.join(localAppData, ".xmake/packages/l/libhat/@default/3c332be551f6485e8d17e1830ee49789/include"))
    add_includedirs("src", {public = true})

    add_headerfiles("src/**.hpp")

    after_build(function (target)
        local src_json = path.join(os.curdir(), "mod.json")
        local dst_json = path.join(modFolder, "mod.json")
        if not os.isdir(modFolder) then
            os.mkdir(modFolder)
        end
        os.cp(src_json, dst_json)
    end)