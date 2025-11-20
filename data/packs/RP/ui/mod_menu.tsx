import { Button, ButtonProps, Common, GetRef, Image, ImageProps, Label, Panel, PanelProps, StackPanel, UiFile, createFile, createMinecraftElement, InputPanel } from "Regolith-Generators";

const modMenu = new UiFile("mod_menu");

const BaseScreen = GetRef("common", "base_screen");

const BgBase = GetRef<ImageProps>("common", "dialog_background_hollow_common");
const OptionToggle = GetRef("settings_common", "option_toggle");
const TextEditBox = GetRef<PanelProps>("common", "text_edit_box");
const Dropdown = GetRef<PanelProps>("settings_common", "option_dropdown");

const TopBar = GetRef("common_store", "store_top_bar");


interface LightTextButttonProps extends ButtonProps {
    $button_text: string;
    $pressed_button_name: string;
}

const LightTextButtton = GetRef<LightTextButttonProps>("common_buttons", "light_text_button");

modMenu.addControl("mod_info_panel",
    <StackPanel orientation="vertical">
        {/* Header */}
        <StackPanel orientation="horizontal" size={["100%", "100%c"]}>
            <Image texture="$mod_icon" size={["64px", "64px"]} />
            <StackPanel orientation="vertical">
                <Label text="$mod_name" />
                <Label text="$mod_version" />
                <Label text="$mod_author" />
            </StackPanel>
        </StackPanel>

        {/* Body */}
        <Label text="Settings" />
    </StackPanel>
)

modMenu.addControl("mod_info",
    <StackPanel size={["100%", "100%c"]} factory={{
        control_ids: {
            mod_info_panel: "@mod_menu.mod_info_panel",
            mod_settings_item_bool: "@mod_menu.mod_settings_item_bool",
            mod_settings_item_int: "@mod_menu.mod_settings_item_int",
            mod_settings_item_string: "@mod_menu.mod_settings_item_string",
        },
        name: "mod_info_factory",
    }} />
)

modMenu.addControl("mod_settings_item_bool",
    <StackPanel anchors="top_left" size={["100%", "30px"]} orientation="horizontal">
        <Label anchors="left_middle" text="$settings_label" size={["fill", "30px"]} />
        <OptionToggle $option_label="Enabled" size={["fill", "30px"]} />
    </StackPanel>
)
modMenu.addControl("mod_settings_item_int",
    <StackPanel anchors="top_left" size={["100%", "30px"]} orientation="horizontal">
        <Label anchors="left_middle" text="$settings_label" size={["fill", "30px"]} />
        <TextEditBox size={["fill", "30px"]}/>
    </StackPanel>
)
modMenu.addControl("mod_settings_item_string",
    <StackPanel anchors="top_left" size={["100%", "30px"]} orientation="horizontal">
        <Label anchors="left_middle" text="$settings_label" size={["fill", "30px"]} />
        <TextEditBox size={["fill", "30px"]} />
    </StackPanel>
)

modMenu.addControl("mod_list_item",
    <Panel anchors="top_left" size={["100%", "30px"]}>
        <LightTextButtton $button_text="$mod_name" $pressed_button_name="$mod_name" />
        <Image texture="$mod_icon" size={["30px", "30px"]} />
    </Panel>
)

modMenu.addControl("mods_list",
    <StackPanel size={["100%", "100%c"]} factory={{
        name: "mods_list_factory",
        control_ids: {
            mod_list_item: "@mod_menu.mod_list_item",
        }
    }} />
)

modMenu.addControl("root_panel",
    <BaseScreen >
        <Common.CommonPanel size={["100%", "20px"]} anchors="top_left" $show_close_button>
            <TopBar />
            <Common.Button size={[16, 16]} anchors="left_middle" hover_control="hover" offset={[2, 0]} $pressed_button_name="button.amethyst:close_mods_list" >
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