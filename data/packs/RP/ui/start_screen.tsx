import { GetRef, Image, Label, Panel, PanelProps, StackPanel, UiFile, createFile, createMinecraftElement } from "Regolith-Generators";

const startScreen = new UiFile("start");

const BaseVersion = GetRef<PanelProps>("start", "version");

interface VersionLabelProps extends PanelProps {
    text_binding: string;
}

function VersionLabel(props: VersionLabelProps) {
    return (
        <Label 
            color="$main_header_text_color" 
            text={props.text_binding} 
            size={["default", 10]} 
            max_size={["100%", "100%"]} 
            anchors="top_right"
            layer={2}
            bindings={[
                {
                    binding_name: props.text_binding,
                }
            ]}
        >
            <Image texture="textures/ui/Black" anchors="center" alpha={0.6} layer={-1} size={["100% + 2px", "100% + 2px"]} />
        </Label>
    );
}

interface MainButtonProps extends PanelProps {
    $pressed_button_name: string;
    $button_text: string;
}

const MainButton = GetRef<MainButtonProps>("start", "main_button");

startScreen.addControl("version", 
    <BaseVersion>
        <VersionLabel text_binding="#version" offset={[0, -24]} />
        <VersionLabel text_binding="#amethyst_version" offset={[0, -12]} />
        <VersionLabel text_binding="#mods_loaded" offset={[0, 0]} />
    </BaseVersion>
);

const StackedRow = GetRef<PanelProps>("start", "stacked_row");

function TitleScreenButton(props: MainButtonProps) {
    return (
        <StackedRow>
            <MainButton
                $button_text={props.$button_text}
                $pressed_button_name={props.$pressed_button_name}
            />
        </StackedRow>
    )
}

const TitlePanelContent = GetRef<PanelProps>("common_art", "start_title_panel_content");

const NewButtonStack = startScreen.addControl("new_button_stack", 
    <Panel size={[150, "100%c"]}>
        <StackPanel key="stacked_rows" size={["100%", "100%c"]} anchors="center">
            <TitleScreenButton $button_text="menu.play" $pressed_button_name="$play_button_target" />
            <TitleScreenButton $button_text="menu.settings" $pressed_button_name="button.menu_settings" />
            <TitleScreenButton $button_text="amethyst:menu.mods" $pressed_button_name="button.amethyst:mods" />
        </StackPanel>
    </Panel>
)

startScreen.addControl("start_screen_content/main_buttons_and_title_panel", 
    <StackPanel orientation="vertical" size={["100%", "100%"]}>
        <Panel size={["100%", "12%"]} />
        <TitlePanelContent />
        <Panel size={["100%", "12%"]} />

        <Panel key="main_buttons_panel" size={["100%", "100%c"]} propagate_alpha>
            <NewButtonStack />
        </Panel>
        
    </StackPanel>
)

createFile(JSON.stringify(startScreen.toJson(), undefined, 4))