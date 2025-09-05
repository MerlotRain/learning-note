#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component Inner(std::vector<Component> children)
{
    Component vlist = Container::Vertical(std::move(children));
    return Renderer(vlist, [vlist] {
        return hbox({
                text(" "),
                vlist->Render(),
        });
    });
}

Component Empty()
{
    return std::make_shared<ComponentBase>();
}


int main()
{
    auto component = Collapsible(
            "Collapsible 1", Inner({
                                     Collapsible("Collapsible 1.1", Inner({
                                                                            Collapsible("Collapsible 1.1.1", Empty()),
                                                                            Collapsible("Collapsible 1.1.2", Empty()),
                                                                            Collapsible("Collapsible 1.1.3", Empty()),
                                                                    })),
                                     Collapsible("Collapsible 1.2", Inner({
                                                                            Collapsible("Collapsible 1.2.1", Empty()),
                                                                            Collapsible("Collapsible 1.2.2", Empty()),
                                                                            Collapsible("Collapsible 1.2.3", Empty()),
                                                                    })),
                                     Collapsible("Collapsible 1.3", Inner({
                                                                            Collapsible("Collapsible 1.3.1", Empty()),
                                                                            Collapsible("Collapsible 1.3.2", Empty()),
                                                                            Collapsible("Collapsible 1.3.3", Empty()),
                                                                    })),
                             }));

    ScreenInteractive::FitComponent().Loop(component);
}