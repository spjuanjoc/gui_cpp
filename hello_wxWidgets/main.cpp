#include <wx/wxprec.h>
#include <wx/wx.h>

class OptionsLoader : public wxFrame
{
public:
  OptionsLoader();
  void init();

private:
  void OnHello(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  wxMenuBar* m_menu_bar{};
  wxMenu* m_option_file{};
  wxMenu* m_option_help{};
};

class ApplicationLoader : public wxApp
{
public:
  bool OnInit() override;

private:
  OptionsLoader* m_options_menu{};
};

enum
{
  ID_Hello = 1
};

bool ApplicationLoader::OnInit()
{
  m_options_menu = new OptionsLoader();
  m_options_menu->init();
  m_options_menu->Show(true);
  return true;
}

OptionsLoader::OptionsLoader() : wxFrame(nullptr, wxID_ANY, "Hello World")
{
  m_menu_bar = new wxMenuBar();
  m_option_file = new wxMenu();
  m_option_help = new wxMenu();

  m_option_file->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  m_option_file->AppendSeparator();
  m_option_file->Append(wxID_EXIT);
  m_option_help->Append(wxID_ABOUT);
  m_menu_bar->Append(m_option_file, "&File");
  m_menu_bar->Append(m_option_help, "&Help");
}

void OptionsLoader::OnExit(wxCommandEvent& event)
{
  Close(true);
}

void OptionsLoader::OnAbout(wxCommandEvent& event)
{
  wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void OptionsLoader::OnHello(wxCommandEvent& event)
{
  wxLogMessage("Hello world from wxWidgets!");
}

void OptionsLoader::init()
{
  SetMenuBar(m_menu_bar);
  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets");
  Bind(wxEVT_MENU, &OptionsLoader::OnHello, this, ID_Hello);
  Bind(wxEVT_MENU, &OptionsLoader::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &OptionsLoader::OnExit, this, wxID_EXIT);
}

wxIMPLEMENT_APP_NO_MAIN(ApplicationLoader);

int main(int argc, char* argv[])
{
  wxEntry(argc, argv);

  return 0;
}
