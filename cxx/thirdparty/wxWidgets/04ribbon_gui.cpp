#include <wx/wx.h>
#include <wx/ribbon/bar.h>

class Widget : public wxFrame
{
    wxRibbonBar* m_ribbon;
public:
    Widget() : wxFrame(nullptr, wxID_ANY, "wxRibbon Sample Application", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE)
    {
        m_ribbon = new wxRibbonBar(this,-1,wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL
                                    | wxRIBBON_BAR_SHOW_PAGE_LABELS
                                    | wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
                                    | wxRIBBON_BAR_SHOW_TOGGLE_BUTTON
                                    | wxRIBBON_BAR_SHOW_HELP_BUTTON
                                    );
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