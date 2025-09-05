#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main()
{
    auto input_list = Container::Vertical({});
    std::vector<std::string> items(100, "");
    for (int i = 0; i < 100; ++i)
    {
        input_list->Add(Input(&(items[i]), "placeholder " + std::to_string(i)));
    }

    auto render = Renderer(input_list, [&] {
        return input_list->Render() | frame | vscroll_indicator | border | size(HEIGHT, LESS_THAN, 10);
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(render);

    return 0;
}