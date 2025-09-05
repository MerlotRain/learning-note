#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;
/*
  int value = 0;
  auto action = [&] { value++; };
  auto action_renderer =
      Renderer([&] { return text("count = " + std::to_string(value)); });
 
  auto buttons =
      Container::Vertical({
          action_renderer,
          Renderer([] { return separator(); }),
          Container::Horizontal({
              Container::Vertical({
                  Button("Ascii 1", action, ButtonOption::Ascii()),
                  Button("Ascii 2", action, ButtonOption::Ascii()),
                  Button("Ascii 3", action, ButtonOption::Ascii()),
              }),
              Renderer([] { return separator(); }),
              Container::Vertical({
                  Button("Simple 1", action, ButtonOption::Simple()),
                  Button("Simple 2", action, ButtonOption::Simple()),
                  Button("Simple 3", action, ButtonOption::Simple()),
              }),
              Renderer([] { return separator(); }),
              Container::Vertical({
                  Button("Animated 1", action, ButtonOption::Animated()),
                  Button("Animated 2", action, ButtonOption::Animated()),
                  Button("Animated 3", action, ButtonOption::Animated()),
              }),
              Renderer([] { return separator(); }),
              Container::Vertical({
                  Button("Animated 4", action,
                         ButtonOption::Animated(Color::Red)),
                  Button("Animated 5", action,
                         ButtonOption::Animated(Color::Green)),
                  Button("Animated 6", action,
                         ButtonOption::Animated(Color::Blue)),
              }),
          }),
      }) |
      border;
 
  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(buttons);
  return 0;
*/

int main()
{
    int value = 0;
    auto action = [&] { value++; };
    auto action_renderer = Renderer([&] { return text("count = " + std::to_string(value)); });

    auto buttons = Container::Vertical({
                           action_renderer,
                           Renderer([] { return separator(); }),
                           Container::Horizontal({
                                   Container::Vertical({
                                           Button("Ascii 1", action, ButtonOption::Ascii()),
                                           Button("Ascii 2", action, ButtonOption::Ascii()),
                                           Button("Ascii 3", action, ButtonOption::Ascii()),
                                   }),
                                   Renderer([] { return separator(); }),
                                   Container::Vertical({
                                           Button("Simple 1", action, ButtonOption::Simple()),
                                           Button("Simple 2", action, ButtonOption::Simple()),
                                           Button("Simple 3", action, ButtonOption::Simple()),
                                   }),
                                   Renderer([] { return separator(); }),
                                   Container::Vertical({
                                           Button("Animated 1", action, ButtonOption::Animated()),
                                           Button("Animated 2", action, ButtonOption::Animated()),
                                           Button("Animated 3", action, ButtonOption::Animated()),
                                   }),
                                   Renderer([] { return separator(); }),
                                   Container::Vertical({
                                           Button("Animated 4", action, ButtonOption::Animated(Color::Red)),
                                           Button("Animated 5", action, ButtonOption::Animated(Color::Green)),
                                           Button("Animated 6", action, ButtonOption::Animated(Color::Blue)),
                                   }),
                           }),
                   }) |
                   border;

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(buttons);
    return 0;
}