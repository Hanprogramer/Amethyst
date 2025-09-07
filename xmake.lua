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

-- Project dependencies
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

    add_files("src/**.cpp")

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
    add_links("user32", "oleaut32", "windowsapp", path.join(os.curdir(), "generated/lib/Minecraft.Windows.lib"))
    add_includedirs("src", {public = true})

    add_headerfiles("src/**.hpp")

    before_build(function (target)
        local generated_dir = path.join(os.curdir(), "generated")
        local input_dir = path.join(os.curdir(), "AmethystAPI/src"):gsub("\\", "/")
        local include_dir = path.join(os.curdir(), "AmethystAPI/include"):gsub("\\", "/")

        local symbol_generator_exe = path.join(os.curdir(), "tools/RuntimeImporter/Amethyst.SymbolGenerator.exe")
        local library_generator_exe = path.join(os.curdir(), "tools/RuntimeImporter/Amethyst.LibraryGenerator.exe")

        local gen_sym_args = {
            symbol_generator_exe,
            "--input", string.format("%s", input_dir),
            "--output", string.format("%s", generated_dir),
            "--filters", "minecraft",
            "--",
            "-x c++",
            "-std=c++23",
            "-fms-extensions",
            "-fms-compatibility",
            string.format('-I%s', include_dir),
            string.format('-I%s', input_dir)
        }
        print('Generating *.symbols.json files for headers...')
        os.exec(table.concat(gen_sym_args, " "))
        local gen_lib_args = {
            library_generator_exe,
            "--input", string.format("%s/symbols", generated_dir),
            "--output", string.format("%s/lib", generated_dir)
        }
        print('Generating Minecraft.Windows.lib file...')
        os.exec(table.concat(gen_lib_args, " "))
    end)

    after_build(function (target)
        local generated_dir = path.join(os.curdir(), "generated")
        local src_json = path.join(os.curdir(), "mod.json")
        local dst_json = path.join(modFolder, "mod.json")
        if not os.isdir(modFolder) then
            os.mkdir(modFolder)
        end
        os.cp(src_json, dst_json)

        local module_tweaker_exe = path.join(os.curdir(), "tools/RuntimeImporter/Amethyst.ModuleTweaker.exe")

        local tweaker_args = {
            module_tweaker_exe,
            "--module", target:targetfile(),
            "--symbols", string.format("%s/symbols", generated_dir)
        }
        print('Tweaking output file...')
        os.exec(table.concat(tweaker_args, " "))
    end)