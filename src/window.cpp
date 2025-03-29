#include "../headers/window.h"

Window::Window(const wxString wTitle, wxPoint wPosition, wxSize wSize)
: wxFrame(NULL, wxID_ANY, wTitle, wPosition, wSize) {

	wxImage folder_ico("images/folder-ico.png", wxBITMAP_TYPE_PNG);
	folder_ico = folder_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	folder_img = wxBitmap(folder_ico);

	wxImage text_ico("images/text-icon-png.jpg", wxBITMAP_TYPE_PNG);
	text_ico = text_ico.Scale(70, 70, wxIMAGE_QUALITY_HIGH);
	text_img = wxBitmap(text_ico);

	working_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
	quick_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 500));
	quick_panel->SetBackgroundColour(wxColour(196, 196, 196));

	SetQuickAccess();
    working_sizer = new wxFlexGridSizer(7, 0, 0);
    for (int i = 0; i < 7; i++) working_sizer->AddGrowableCol(i);
	working_panel->SetSizer(working_sizer);

	main_sizer = new wxBoxSizer(wxHORIZONTAL);
	main_sizer->Add(quick_panel, 0, wxEXPAND);
	main_sizer->Add(working_panel, 0, wxEXPAND);
	SetSizerAndFit(main_sizer);
}

void Window::GridSelectHandler(wxGridEvent &ev) {

	folder_icons.clear();
	text_icons.clear();
	working_sizer->Clear(true);
	
	int row = ev.GetRow();
	switch (row) {
		case 0: cur_path = "/home/tinnitus"; break;
		case 1: cur_path = "/home/tinnitus/Documents"; break;
		case 2: cur_path = "/home/tinnitus/Downloads/"; break;
	}

	int folder_count = GetFolderCount();
	int txt_count = GetTextFilesCount();

    for (size_t i = 0; i < folder_count; i++) {
		wxStaticBitmap *folder = new wxStaticBitmap(working_panel, wxID_ANY, folder_img, wxDefaultPosition, wxSize(70, 70));
		folder_icons.push_back(folder);
	}

    for (size_t i = 0; i < txt_count; i++) {
		wxStaticBitmap *txt = new wxStaticBitmap(working_panel, wxID_ANY, text_img, wxDefaultPosition, wxSize(70, 70));
		text_icons.push_back(txt);
	}

	for (wxStaticBitmap *i : folder_icons) {
		working_sizer->Add(i, 0);
	}

	for (wxStaticBitmap *i : text_icons) {
		working_sizer->Add(i, 0);
	}

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
	quick_panel_sizer->Add(quick_path, 0, wxEXPAND);
	quick_panel->SetSizer(quick_panel_sizer);
	quick_path->Layout();
}

int Window::GetFolderCount() {
	int folder_count = 0;

    for (const auto & entry : std::filesystem::directory_iterator(cur_path)) {
    	if (entry.is_directory()) folder_count+=1;
    } return folder_count;
}

int Window::GetTextFilesCount() {	
    wxDir dir(cur_path);

    wxString filename;
    bool cont = dir.GetFirst(&filename, "*.*", wxDIR_FILES | wxDIR_DIRS);

	int txt_file_count = 0;
    while (cont) {
    	txt_file_count++;
        cont = dir.GetNext(&filename);
    } return txt_file_count;
}