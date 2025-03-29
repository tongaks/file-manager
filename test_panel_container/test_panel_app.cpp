#include "test_panel.h"
#include "test_panel_app.h"

bool App::OnInit() {
	wxInitAllImageHandlers();

	Window *window = new Window("tets", wxPoint(30, 30), wxSize(600, 500));
	window->Show(true);
	return true;
}

wxIMPLEMENT_APP(App);