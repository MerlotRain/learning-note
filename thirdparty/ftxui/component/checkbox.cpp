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
    bool download = false;
    bool upload = false;
    bool ping = false;

    auto container = Container::Vertical({
            Checkbox("Download", &download),
            Checkbox("Upload", &upload),
            Checkbox("Ping", &ping),
    });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(container);

    std::cout << "---" << std::endl;
    std::cout << "Download: " << download << std::endl;
    std::cout << "Upload: " << upload << std::endl;
    std::cout << "Ping: " << ping << std::endl;
    std::cout << "---" << std::endl;

    return 0;
}