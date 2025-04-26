#include "../headers/app.h"
#include "../headers/window.h"

bool App::OnInit() {
	wxInitAllImageHandlers();
	
	Window *window = new Window("File manager", wxPoint(100, 100), wxSize(1000, 500));
	window->Show(true);
	return true;
}

wxIMPLEMENT_APP(App);