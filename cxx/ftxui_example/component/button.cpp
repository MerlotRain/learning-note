#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

ButtonOption Style()
{
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState &s) {
        auto element = text(s.label);
        if (s.focused)
        {
            element |= bold;
        }
        return element | center | borderEmpty | flex;
    };
    return option;
}

int main()
{
    int value = 50;
    auto btn_dec_01 = Button("-1", [&] { value -= 1; }, Style());
    auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
    auto btn_dec_10 = Button("-10", [&] { value -= 10; }, Style());
    auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());

    int row = 0;
    auto buttons = Container::Vertical({
            Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
            Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,
    });

    auto component = Renderer(buttons, [&] {
        return vbox({
                       text("value = " + std::to_string(value)),
                       separator(),
                       buttons->Render() | flex,
               }) |
               flex | border;
    });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component);
    return 0;
}