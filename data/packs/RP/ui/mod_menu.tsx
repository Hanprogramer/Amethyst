import { Button, Common, GetRef, Image, ImageProps, Label, Panel, PanelProps, StackPanel, UiFile, createFile, createMinecraftElement } from "Regolith-Generators";

const modMenu = new UiFile("mod_menu");

const BaseScreen = GetRef("common", "base_screen");

const BgBase = GetRef<ImageProps>("common", "dialog_background_hollow_common");

modMenu.addControl("mods_list", 
    <StackPanel size={["100%", "100%c"]}>
        <Panel size={["100%", "30px"]}>
            <Label text="Mods" />
            <Image texture="textures/ui/Black" />
        </Panel>
    </StackPanel>
)

const TopBar = GetRef("common_store", "store_top_bar");

modMenu.addControl("test",
    <Label text="Test" />
)

modMenu.addControl("mod_info",
    <StackPanel size={["100%", "100%c"]} key="test_factory" factory={{
        control_ids: {
            test: "@mod_menu.test"
        },
        name: "test_factory",
    }} />
)

modMenu.addControl("root_panel",
    <BaseScreen>
        <Common.CommonPanel size={["100%", "20px"]} anchors="top_left" $show_close_button>
            <TopBar />

            <Common.Button size={[16, 16]} anchors="left_middle" hover_control="hover" offset={[2, 0]} $pressed_button_name="button.amethyst:close_mods_list">
                <Label text="<" anchors="center" color="$title_text_color" />
                <Image key="hover" texture="textures/ui/Black" alpha={0.2} />
            </Common.Button>
            
            <Label text="amethyst:menu.mods" anchors="center" color="$title_text_color" />
        </Common.CommonPanel>
        <Panel size={["30%", "100% - 20px"]} anchors="top_left" offset={[0, "20px"]}>
            <BgBase />
            <Common.ScrollingPanel $show_background={false} $scrolling_content="mod_menu.mods_list" size={["100% - 16px", "100% - 16px"]} />
        </Panel>
        <Panel size={["70%", "100% - 20px"]} anchors="top_right" offset={[0, "20px"]}>
            <BgBase />
            <Common.ScrollingPanel $show_background={false} $scrolling_content="mod_menu.mod_info" size={["100% - 16px", "100% - 16px"]} />
        </Panel>
    </BaseScreen>
)

createFile(JSON.stringify(modMenu.toJson(), null, 4));