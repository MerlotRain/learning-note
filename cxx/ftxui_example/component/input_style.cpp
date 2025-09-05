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
    InputOption style_1 = InputOption::Default();

    InputOption style_2 = InputOption::Spacious();

    InputOption style_3 = InputOption::Spacious();
    style_3.transform = [](InputState state) {
        state.element |= borderEmpty;

        if (state.is_placeholder)
        {
            state.element |= dim;
        }

        if (state.focused)
        {
            state.element |= borderDouble;
            state.element |= bgcolor(Color::White);
            state.element |= color(Color::Black);
        }
        else if (state.hovered)
        {
            state.element |= borderRounded;
            state.element |= bgcolor(LinearGradient(90, Color::Blue, Color::Red));
            state.element |= color(Color::White);
        }
        else
        {
            state.element |= border;
            state.element |= bgcolor(LinearGradient(0, Color::Blue, Color::Red));
            state.element |= color(Color::White);
        }

        return state.element;
    };

    InputOption style_4 = InputOption::Spacious();
    style_4.transform = [](InputState state) {
        state.element = hbox({
                text("Theorem") | center | borderEmpty | bgcolor(Color::Red),
                separatorEmpty(),
                separator() | color(Color::White),
                separatorEmpty(),
                std::move(state.element),
        });

        state.element |= borderEmpty;
        if (state.is_placeholder)
        {
            state.element |= dim;
        }

        if (state.focused)
        {
            state.element |= bgcolor(Color::Black);
        }
        else
        {
            state.element |= bgcolor(Color::Blue);
        }

        if (state.hovered)
        {
            state.element |= bgcolor(Color::GrayDark);
        }

        return vbox({state.element, separatorEmpty()});
    };

    auto generateUiFromStyle = [&](InputOption style) {
        auto first_name = new std::string(); // Leaked
        auto middle_name = new std::string();// Leaked
        auto last_name = new std::string();  // Leaked
        return Container::Vertical({
                       Input(first_name, "first name", style),
                       Input(middle_name, "middle name", style),
                       Input(last_name, "last name", style),
               }) |
               borderEmpty;
    };

    auto ui = Container::Horizontal({
            generateUiFromStyle(style_1),
            generateUiFromStyle(style_2),
            generateUiFromStyle(style_3),
            generateUiFromStyle(style_4),
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(ui);
}