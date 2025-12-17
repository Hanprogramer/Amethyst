import { Button, ButtonProps, Common, GetRef, Image, ImageProps, Label, Panel, PanelProps, StackPanel, UiFile, createFile, createMinecraftElement, InputPanel, CustomProps, ToggleProps, InputPanelProps } from "Regolith-Generators";

const modMenu = new UiFile("mod_menu");

const BaseScreen = GetRef("common", "base_screen");

const OptionToggle = GetRef<ToggleProps>("settings_common", "option_toggle");
const TextEditBox = GetRef<InputPanelProps>("common", "text_edit_box");
const Dropdown = GetRef<PanelProps>("settings_common", "option_dropdown");
const Slider = GetRef<PanelProps>("settings_common", "option_slider");
const OptionRadioDropdownGroup = GetRef<PanelProps>("settings_common", "option_radio_dropdown_group");
const TopBar = GetRef("common_store", "store_top_bar");


interface LightTextButttonProps extends ButtonProps {
    $button_text: string;
    $pressed_button_name: string;
}

const LightTextButtton = GetRef<LightTextButttonProps>("common_buttons", "light_text_button");

modMenu.addControl("mod_info_panel",
    <StackPanel orientation="vertical">
        {/* Header */}
        <StackPanel orientation="horizontal" size={["100%", "48px"]}>
            <Image texture="$mod_icon" size={["48px", "48px"]} />
            <Panel size={[10, 0]} />
            <StackPanel orientation="vertical">
                <Label size={["100%", "default"]} text="$mod_name" font_size="medium" font_scale_factor={1.5} />
                <Label size={["100%", "default"]} text="$mod_version" color={[0.55, 0.55, 0.55]} />
                <Panel size={[0, 4]} />
                <Label size={["100%", "default"]} text="$mod_author" color={[0.55, 0.55, 0.55]} />
            </StackPanel>
        </StackPanel>
        <Panel size={["100%", 20]}>
            <Image texture="textures/ui/list_item_divider_line_light" anchors="center" size={["100% - 30px", 1]} />
        </Panel>
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

            mod_settings_item_options: "@mod_menu.mod_settings_item_options",
            mod_settings_item_slider: "@mod_menu.mod_settings_item_slider",
        },
        name: "mod_info_factory",
    }} />
)

modMenu.addControl("mod_settings_item_bool",
    <StackPanel anchors="left_middle" size={["100%", "30px"]} orientation="horizontal"
        defaults={{
            $is_enabled: false
        }}>
        <Panel size={["fill", "30px"]}>
            <Label anchors="left_middle" text="$settings_label" layer={5} offset={[10, 0]} />
        </Panel>
        <OptionToggle
            size={["fill", "30px"]}
            $toggle_default_state="$is_enabled"
            $option_binding_name="#settings_label"
            $toggle_name="$settings_label"
            $option_label="Enabled"
        />
    </StackPanel>
)
modMenu.addControl("mod_settings_item_int",
    <StackPanel anchors="left_middle" size={["100%", "30px"]} orientation="horizontal">
        <Panel size={["fill", "30px"]}>
            <Label anchors="left_middle" text="$settings_label" layer={5} offset={[10, 0]} />
        </Panel>
        <TextEditBox size={["fill", "30px"]}
            $place_holder_text="0"
            text_type="NumberChars"
            max_length={256}
            text_box_name="textedit.amethyst:mod_setting_int" />
    </StackPanel>
)
modMenu.addControl("mod_settings_item_string",
    <StackPanel anchors="left_middle" size={["100%", "30px"]} orientation="horizontal">
        <Panel size={["fill", "30px"]}>
            <Label anchors="left_middle" text="$settings_label" layer={5} offset={[10, 0]} />
        </Panel>
        <TextEditBox size={["fill", "30px"]}
            max_length={256}
            text_box_name="textedit.amethyst:mod_setting_string" />
    </StackPanel>
)
modMenu.addControl("mod_settings_item_slider",
    <StackPanel anchors="left_middle" size={["100%", "30px"]} orientation="horizontal"
    >
        <Panel size={["fill", "30px"]}>
            <Label anchors="left_middle" text="$settings_label" layer={5} offset={[10, 0]} />
        </Panel>
        {/* <Slider size={["fill", "30px"]} 
            $slider_name="$settings_label"
            $slider_value_binding_name="#chat_line_spacing"/> */}
    </StackPanel>
)
modMenu.addControl("mod_settings_item_options",
    <StackPanel anchors="left_middle" size={["100%", "30px"]} orientation="horizontal">
        <Panel size={["fill", "30px"]}>
            <Label anchors="left_middle" text="$settings_label" layer={5} offset={[10, 0]} />
        </Panel>
        <Dropdown size={["fill", "30px"]}
            $dropdown_content="mod_menu.custom_dropdown_content"
            $dropdown_area="content_area"
            $dropdown_name="$settings_control_name"
 
            // $option_enabled_binding_name="#tmi_bool_1"
            $options_dropdown_toggle_label_binding="#item_name"
            $dropdown_scroll_content_size={["100%", "300%"]}
        />
    </StackPanel>
)

modMenu.addControl("mod_list_item",
    <Panel anchors="top_left" size={["100%", "30px"]}>
        <LightTextButtton $button_text="" $pressed_button_name="$mod_name" layer={2} size={["100%", "100%"]} />
        <StackPanel orientation="horizontal" size={["100% - 6px", "100% - 6px"]}>
            <Image texture="$mod_icon" size={["24px", "24px"]} layer={12} />

            <Panel size={["fill", "24px"]}>
                <Label anchors="left_middle" text="$mod_name" layer={12} color={[0.0, 0.0, 0.0]} offset={[10, 0]} />
            </Panel>
        </StackPanel>
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
    <BaseScreen button_mappings={[
        {
            "from_button_id": "button.menu_cancel",
            "to_button_id": "button.amethyst:close_mods_list",
            "mapping_type": "global"
        }
    ]}>
        <Common.CommonPanel size={["100%", "20px"]} anchors="top_left" $show_close_button>
            <TopBar />
            <Common.Button size={[16, 16]} anchors="left_middle" hover_control="hover" offset={[2, 0]} $pressed_button_name="button.amethyst:close_mods_list" >
                <Label text="<" anchors="center" color="$title_text_color" />
                <Image key="hover" texture="textures/ui/Black" alpha={0.2} />
            </Common.Button>
            <Label text="amethyst:menu.mods" anchors="center" color="$title_text_color" />
        </Common.CommonPanel>
        <Panel size={["30%", "100% - 20px"]} anchors="top_left" offset={[0, "20px"]}>
            <Image texture="textures/ui/background_with_border" size={["100%", "100%"]} layer={-1} alpha={0.8} />
            <Common.ScrollingPanel $show_background={false} $scrolling_content="mod_menu.mods_list" size={["100% - 16px", "100% - 16px"]} />
        </Panel>
        <Panel size={["70%", "100% - 20px"]} anchors="top_right" offset={[0, "20px"]}>
            <Image texture="textures/ui/background_with_border" size={["100%", "100%"]} layer={-1} alpha={0.8} />
            <Common.ScrollingPanel $show_background={false} $scrolling_content="mod_menu.mod_info" size={["100% - 16px", "100% - 16px"]} />
        </Panel>
    </BaseScreen>
)

createFile(JSON.stringify(modMenu.toJson(), null, 4));