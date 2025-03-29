#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/dir.h>

#include <iostream>
#include <string>
#include <filesystem>

class Window : public wxFrame {
	std::vector<wxStaticBitmap*> folder_icons;
	std::vector<wxStaticBitmap*> text_icons;

	// int folder_count = 0;
	wxPanel *quick_panel;
	wxPanel *working_panel;

	wxBoxSizer *main_sizer;
	wxFlexGridSizer* working_sizer;
	wxBoxSizer *quick_panel_sizer;

	wxGrid *quick_path;
	std::string cur_path = "/home/tinnitus";

public:
	wxBitmap folder_img;
	wxBitmap text_img;

	Window(const wxString wTitle, wxPoint wPosition, wxSize wSize);
	void GridSelectHandler(wxGridEvent &ev);
	void SetQuickAccess();
	void AddFolderIcons(int count);
	int GetFolderCount();
	int GetTextFilesCount();
};