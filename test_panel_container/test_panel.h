#include <wx/wx.h>
#include <vector>

class Window : public wxFrame {
	// std::vector<wxPanel*> files;
	// std::vector<wxStaticBitmap*> file_icons;
	// std::vector<wxStaticText*> file_names;

	wxFlexGridSizer *main_sizer;

	// wxPanel *container_panel;
public:
	wxBitmap folder_img;
	wxBitmap text_file_img;

	Window(const wxString wTitle, wxPoint wPosition, wxSize wSize);
	void CreateFileIcon(int count, wxBitmap img, std::vector<std::string> fname);
};