#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;

int main()
{
    int value = 50;
    auto buttons = Container::Horizontal({
            Button(
                    "Decrease", [&] { value--; }, ButtonOption::Animated(Color::Red)),
            Button(
                    "Reset", [&] { value = 50; }, ButtonOption::Animated(Color::Green)),
            Button(
                    "Increase", [&] { value++; }, ButtonOption::Animated(Color::Blue)),
    });

    auto component = Renderer(buttons, [&] {
        return vbox({
                vbox({
                        text("value = " + std::to_string(value)),
                        separator(),
                        gauge(value * 0.01f),
                }) | border,
                buttons->Render(),
        });
    });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component);
    return 0;
}