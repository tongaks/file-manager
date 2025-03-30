#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/dir.h>

#include <iostream>
#include <string>
#include <filesystem>

class Window : public wxFrame {
	std::vector<wxStaticBitmap*> folder_icons;
	std::vector<wxStaticBitmap*> text_icons;

	std::vector<wxPanel*> folders_container;

	std::vector<wxStaticText*> file_name_label;
	std::vector<std::string> folder_names;
	std::vector<std::string> text_file_names;

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
	void AddIcon(int count, wxBitmap img, std::vector<std::string> fname, std::vector<wxStaticBitmap*> &icons, std::vector<wxStaticText*> &icon_label);
};