#include "../headers/window.h"

Window::Window(const wxString wTitle, wxPoint wPosition, wxSize wSize)
: wxFrame(NULL, wxID_ANY, wTitle, wPosition, wSize) {

	wxPanel *main_panel = new wxPanel(this); 

	wxImage folder_ico("images/folder-ico.png", wxBITMAP_TYPE_PNG);
	folder_ico = folder_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	folder_img = wxBitmap(folder_ico);

	wxImage text_ico("images/text-icon-png.jpg", wxBITMAP_TYPE_PNG);
	text_ico = text_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	text_img = wxBitmap(text_ico);

	wxPanel *container_panel = new wxPanel(this); 

	working_panel = new wxPanel(container_panel, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
	quick_panel = new wxPanel(container_panel, wxID_ANY, wxDefaultPosition, wxSize(200, 500));
	quick_panel->SetBackgroundColour(wxColour(0, 0, 0));

	wxPanel *command_panel = new wxPanel(this);
	command_panel->SetBackgroundColour(wxColour(230, 230, 230));

	command_input = new wxTextCtrl(command_panel, wxID_ANY, "");
	command_input->SetHint("Enter command here...");
	path_input = new wxTextCtrl(command_panel, wxID_ANY, cur_path);

	wxBoxSizer *command_sizer = new wxBoxSizer(wxHORIZONTAL);
	command_sizer->Add(path_input, 1, wxEXPAND);
	command_sizer->Add(command_input, 1, wxEXPAND);
	command_panel->SetSizer(command_sizer);


	SetQuickAccess();
    working_sizer = new wxFlexGridSizer(7, 0, 0);
    for (int i = 0; i < 7; i++) working_sizer->AddGrowableCol(i);
	working_panel->SetSizer(working_sizer);

	wxBoxSizer *container_sizer = new wxBoxSizer(wxHORIZONTAL);
	container_sizer->Add(quick_panel, 0, wxEXPAND);
	container_sizer->Add(working_panel, 0, wxEXPAND);
	container_panel->SetSizer(container_sizer);

	main_sizer = new wxBoxSizer(wxVERTICAL);
	main_sizer->Add(command_panel, 1, wxEXPAND);
	main_sizer->Add(container_panel, 0);
	SetSizerAndFit(main_sizer);
}

void Window::GridSelectHandler(wxGridEvent &ev) {

	for (auto *i : folder_icons) i->Destroy();
	folder_icons.clear();

	for (auto *i : text_icons) i->Destroy();
	text_icons.clear();

	folder_names.clear();

	working_sizer->Clear(true);
	
	int row = ev.GetRow();
	switch (row) {
		case 0: cur_path = "/home/tinnitus"; break;
		case 1: cur_path = "/home/tinnitus/Documents"; break;
		case 2: cur_path = "/home/tinnitus/Downloads/"; break;
	}

	path_input->SetValue(cur_path);

	int folder_count = GetFolderCount();
	int text_file_count = GetTextFilesCount();

	AddIcon(folder_count, folder_img, folder_names, folder_icons, file_name_label);
	AddIcon(text_file_count, text_img, text_file_names, text_icons, file_name_label);

	working_panel->Layout();
	working_panel->Fit();
	ev.Skip();
}

void Window::SetQuickAccess() {
	quick_path = new wxGrid(quick_panel, wxID_ANY);
	quick_path->CreateGrid(3, 1);
	quick_path->SetColLabelValue(0, "Quick Access");

	quick_path->SetCellValue(0, 0, "Home");
	quick_path->SetCellValue(1, 0, "Documents");
	quick_path->SetCellValue(2, 0, "Downloads");

	quick_path->DisableDragRowSize();
	quick_path->EnableEditing(false);
	quick_path->HideRowLabels();

	quick_path->Bind(wxEVT_GRID_SELECT_CELL, &Window::GridSelectHandler, this);
	int grid_size = quick_panel->GetSize().GetWidth();
	quick_path->SetColSize(0, grid_size);

	quick_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
	quick_panel_sizer->Add(quick_path, 1, wxEXPAND);
	quick_panel->SetSizer(quick_panel_sizer);
	quick_path->Layout();
}

int Window::GetFolderCount() {
	int folder_count = 0;

    for (const auto & entry : std::filesystem::directory_iterator(cur_path)) {
    	std::string fname = entry.path().filename().string();

    	if (entry.is_directory() && fname[0] != '.') {
    		folder_names.push_back(fname);
    		folder_count+=1;
    	}
    } return folder_count;
}

int Window::GetTextFilesCount() {	
    wxDir dir(cur_path);

    wxString filename;
    bool cont = dir.GetFirst(&filename, "*.*", wxDIR_FILES | wxDIR_DIRS);

	int txt_file_count = 0;
    while (cont) {
    	txt_file_count++;
    	text_file_names.push_back(std::string(filename));
        cont = dir.GetNext(&filename);
    } return txt_file_count;
}

void Window::AddIcon(int count, wxBitmap img, std::vector<std::string> fname, std::vector<wxStaticBitmap*> &icons, std::vector<wxStaticText*> &icon_label) {
	if (count == 0) return;

	for (int i = 0; i < count; i++) {
		wxPanel *panel = new wxPanel(working_panel);

		wxStaticBitmap *icon = new wxStaticBitmap(panel, wxID_ANY, img);
		icon->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent &mev) {
			if ((fname[i].find(".")) != std::string::npos) {
				wxMessageBox(fname[i], "Text file");
			} else wxMessageBox(fname[i], "Folder");
		});

		wxStaticText *label = new wxStaticText(panel, wxID_ANY, fname[i]);
		label->Wrap(-1);

		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(icon, 0, wxALIGN_CENTER);
		sizer->Add(label, 0, wxALIGN_CENTER);
		panel->SetSizer(sizer);

		working_sizer->Add(panel, 0, wxLEFT, 10);

		icons.push_back(icon);
		icon_label.push_back(label);
	}
}