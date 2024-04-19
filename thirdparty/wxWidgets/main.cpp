#include <iostream>
#include <wx/wx.h>

class Widget : public wxFrame
{
public:
    Widget(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(450, 300))
    {
        SetIcon(wxIcon(wxT("")));
        // 如果不设置这个panel，button的size就会充满整个窗口
        wxPanel *panel = new wxPanel(this, wxID_ANY);
        wxButton *btn = new wxButton(panel, wxID_EXIT, wxT("PushButton"), wxPoint(0, 0), wxSize(80, 32));
        btn->Bind(wxEVT_BUTTON, &Widget::OnQuit, this);
        Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Widget::OnQuit));
        btn->SetFocus();

        wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
        /*
        在 wxWidgets 中，proportion 是一个属性，用于控制当前控件在 sizer 中所占用的空间大小。
        当您使用 sizer 来布局窗口中的控件时，proportion 属性决定了当窗口大小改变时，控件如何相对于其他控件调整其大小。

        proportion 的值可以是 0 或非零的正数。

        当 proportion 取值为 0 时，控件的大小固定不变，与其实际所需的大小相同。
        这意味着即使窗口大小改变，该控件也不会自动调整其大小。

        当 proportion 取值为非零时，该控件将与其他具有非零 proportion 值的控件按照其 proportion 的比例来分配额外的空间。
        例如，如果有两个控件 A 和 B，A 的 proportion 为 1，B 的 proportion 为 2，那么当窗口变大时，B 将获得比 A 多两倍的额外空间。

        使用 proportion 属性可以帮助您创建灵活且响应式的界面布局，
        使控件能够根据窗口大小的变化自动调整其大小，从而提供更好的用户体验。
        */
        hBox->Add(btn, 1, wxEXPAND | wxALL, 5);

        Centre();
    }

    void OnQuit(wxCommandEvent &event)
    {
        Close(true);
    }
};

class Application : public wxApp
{
public:
    virtual bool OnInit()
    {
        Widget *w = new Widget("Application");
        w->Show();
        return true;
    }
};
wxDECLARE_APP(Application);

wxIMPLEMENT_APP(Application);