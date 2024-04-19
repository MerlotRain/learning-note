#include <wx/wx.h>
#include <wx/file.h>

void string_demo()
{
    wxString str;
    str.Printf(wxT("Hello world, %d\n"), 10);

    wxPuts(wxT("A wxWidgets console application"));
    wxPuts(str);

    wxString str2 = "A wxWidgets console application";
    wxString u_str = str2.Upper();
    wxPuts(u_str);

    // 数字转字符串可以通过std::to_string实现
}

void util_demo()
{
    wxPuts(wxGetHomeDir());
    wxPuts(wxGetUserName());
    wxPuts(wxGetUserId());
    wxPuts(wxGetFullHostName());
    wxPuts(wxGetOsDescription());
}

void time_demo()
{
    wxDateTime now = wxDateTime::Now();
    wxPrintf(wxT("   Tokyo: %s\n"), now.Format(wxT("%a %T"),
                                               wxDateTime::GMT9)
                                        .c_str());
    wxPrintf(wxT("  Moscow: %s\n"), now.Format(wxT("%a %T"),
                                               wxDateTime::MSD)
                                        .c_str());
    wxPrintf(wxT("Budapest: %s\n"), now.Format(wxT("%a %T"),
                                               wxDateTime::CEST)
                                        .c_str());
    wxPrintf(wxT("  London: %s\n"), now.Format(wxT("%a %T"),
                                               wxDateTime::WEST)
                                        .c_str());
    wxPrintf(wxT("New York: %s\n"), now.Format(wxT("%a %T"),
                                               wxDateTime::EDT)
                                        .c_str());
}

void file_demo()
{
    wxString str = wxT("You make me want to be a better man.\n");

    wxFile file;
    file.Create(wxT("quote"), true);

    if (file.IsOpened())
        wxPuts(wxT("the file is opened"));

    file.Write(str);
    file.Close();

    if (!file.IsOpened())
        wxPuts(wxT("the file is not opened"));
}

int main(int argc, char **argv)
{
    // string_demo();

    // util_demo();

    // time_demo();

    file_demo();
    
    return 0;
}