#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main()
{
    std::string first_name;
    std::string last_name;
    std::string password;
    std::string phoneNumber;

    auto input_first_name = Input(&first_name, "first name");
    auto input_last_name = Input(&last_name, "last name");

    InputOption password_option;
    password_option.password = true;
    auto input_password = Input(&password, "password", password_option);

    auto input_phone_number = Input(&phoneNumber, "phone number");
    input_phone_number |=
            CatchEvent([&](Event event) { return event.is_character() && !std::isdigit(event.character()[0]); });
    input_phone_number |= CatchEvent([&](Event event) { return event.is_character() && phoneNumber.size() > 10; });

    auto renderer = Renderer([&] {
        return vbox({
                       hbox(text(" First name : "), input_first_name->Render()),
                       hbox(text(" Last name  : "), input_last_name->Render()),
                       hbox(text(" Password   : "), input_password->Render()),
                       hbox(text(" Phone num  : "), input_phone_number->Render()),
                       separator(),

                       text("Hello " + first_name + " " + last_name),
                       text("Your password is " + password),
                       text("Your phone number is " + phoneNumber),

               }) |
               border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}