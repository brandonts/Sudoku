#include <wx/wxprec.h>
#include <fstream>

#include "wxwidgets_sudoku_solver.cc"
#include "ncurses_sudoku_solver.cc"
#include "sudoku_solver.cc"

int main(int argc, char *argv[])
{
	if(argc > 2)
	{
		std::cout<<"Sudoku Solver accepts one or no arguments\n";
		return -1;
	}
	if(argc == 1)
	{
		wxApp::SetInstance( new MyApp() );
		wxEntryStart( argc, argv );
		wxTheApp->CallOnInit();

		wxTheApp->OnRun();
		wxTheApp->OnExit();
		wxEntryCleanup();
		return 0;
	}

	if(strcmp(argv[1],"n") == 0)
	{
		ncurse::ncurses_interface();
		return 0;
	}

	if(strcmp(argv[1],"b") == 0)
	{
		basic::basic_interface();
		return 0;
	}
	return 0;
}
