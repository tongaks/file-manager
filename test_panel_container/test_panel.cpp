#include "test_panel.h"

Window::Window(const wxString wTitle, wxPoint wPosition, wxSize wSize)
: wxFrame(NULL, wxID_ANY, wTitle, wPosition, wSize) {

	wxColour gray(126, 126, 126);
	wxPanel *main_panel = new wxPanel(this);

	wxImage folder_ico("../images/folder-ico.png", wxBITMAP_TYPE_PNG);
	folder_ico = folder_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	folder_img = wxBitmap(folder_ico);

	wxImage text_file_ico("../images/text-icon-png.jpg", wxBITMAP_TYPE_PNG);
	text_file_ico = text_file_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	text_file_img = wxBitmap(text_file_ico);

	main_sizer = new wxFlexGridSizer(5, 0, 0);
	for (int i = 0; i < 5; i++) main_sizer->AddGrowableCol(i);

	std::vector<std::string> file_names = {"test.txt", "testicles.cpp", "shittae.hpp", "test.txt", "fiile.java"};
	std::vector<std::string> folder_names = {"folder1", "Documents", "Downloads", "Videos", "Home"};
	
	CreateFileIcon(5, folder_img, folder_names);
	CreateFileIcon(5, text_file_img, file_names);

	SetSizer(main_sizer);
}

void Window::CreateFileIcon(int count, wxBitmap img, std::vector<std::string> fname) {
	if (count == 0) return;

	// filling proud figuring this shit out
	// now, gonna have to find a way to mix this to main
	for (int i = 0; i < count; i++) {
		wxPanel *container_panel = new wxPanel(this);
		wxStaticBitmap *folder_icon = new wxStaticBitmap(container_panel, wxID_ANY, img);
		wxStaticText *label = new wxStaticText(container_panel, wxID_ANY, fname[i]);

		wxBoxSizer *container_panel_sizer = new wxBoxSizer(wxVERTICAL);
		container_panel_sizer->Add(folder_icon, 0, wxALIGN_CENTER);
		container_panel_sizer->Add(label, 0, wxALIGN_CENTER);
		container_panel->SetSizer(container_panel_sizer);

		main_sizer->Add(container_panel, 0, wxTOP, 10);
	}

	// for (wxPanel *p : files) {
	// 	wxStaticBitmap *folder_icon = new wxStaticBitmap(p, wxID_ANY, folder_img);
	// 	wxStaticText *label = new wxStaticText(p, wxID_ANY, "Test folder");

	// 	wxBoxSizer *container_panel_sizer = new wxBoxSizer(wxVERTICAL);
	// 	container_panel_sizer->Add(folder_icon, 0, wxALIGN_CENTER);
	// 	container_panel_sizer->Add(label, 0, wxALIGN_CENTER);
	// 	p->SetSizer(container_panel_sizer);
	// 	container_panel_sizer->Add(p, 0);
	// }
}