#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <iostream>

using namespace ftxui;

int main()
{
    std::array<bool, 30> states;

    auto container = Container::Vertical({});
    for (int i = 0; i < 30; ++i)
    {
        states[i] = false;
        container->Add(Checkbox("Checkbox" + std::to_string(i), &states[i]));
    }

    auto render = Renderer(container, [&] {
        return container->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10) | border;
    });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(render);

    return 0;
}