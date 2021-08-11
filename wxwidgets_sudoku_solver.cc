// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/button.h>
#include <vector>
#include <fstream>

#include "Sudoku_Puzzle/sudoku_puzzle.h"
#include "sudoku_logic_stack.h"

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

int BUTTON_SIZE = 35;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class SelectNumberDialog: public wxDialog
{
	public:
		SelectNumberDialog (wxWindow * parent, int event_id, wxPoint position);
		int index;

	private:
		void OnSelectNumber(wxCommandEvent& event);
		
};

SelectNumberDialog::SelectNumberDialog (wxWindow * parent, int event_id, wxPoint position)
	: wxDialog(parent, wxID_ANY, std::to_string(event_id), position+wxPoint(3*BUTTON_SIZE,3*BUTTON_SIZE), wxSize(BUTTON_SIZE*3,BUTTON_SIZE*5))
{
	index = event_id;
	int current_number = 0;
	new wxButton(this, 0 ,"0", wxPoint(0, 3*BUTTON_SIZE),wxSize(BUTTON_SIZE*3,BUTTON_SIZE));
	Bind(wxEVT_BUTTON, &SelectNumberDialog::OnSelectNumber, this, current_number);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			current_number++;
			new wxButton(this, current_number, std::to_string(current_number),wxPoint((0+j)*BUTTON_SIZE,(0+i)*BUTTON_SIZE),wxSize(BUTTON_SIZE,BUTTON_SIZE));
			Bind(wxEVT_BUTTON, &SelectNumberDialog::OnSelectNumber, this, current_number);
		}
	}
}

class MyFrame : public wxFrame
{
	public:
		MyFrame();
		SudokuPuzzle puzzle{};
	private:
		std::vector<wxButton *> buttons;
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnSelectSquare(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnLoad(wxCommandEvent& event);
		void OnSolve(wxCommandEvent& event);
		void OnClear(wxCommandEvent& event);
		void OnRefresh(wxCommandEvent& event);
		void Refresh();
		void WriteFile(const SudokuPuzzle &p1, std::string file);
		void ReadFile(SudokuPuzzle &p1, std::string file);
};

void MyFrame::WriteFile(const SudokuPuzzle &p1, std::string file)
{
        std::ofstream outFile(file);
        for(int i=0; i<9; i++)
        {
                for(int j=0; j<9; j++) outFile<<p1.Read_(i,j)<<" ";
        }
        outFile<<std::endl;
}

void MyFrame::ReadFile(SudokuPuzzle &p1, std::string file)
{
        int value=0;
	std::vector<int> v1; 
        std::ifstream inFile(file);
        while(inFile >> value){v1.push_back(value);}
        p1=v1;

}
void SelectNumberDialog::OnSelectNumber(wxCommandEvent& event)
{
	int selection = event.GetId();
	int square = this->index;
	int row = square/9;
	int col = square-row*9;
	MyFrame *myParent = (MyFrame *) GetParent();
	myParent->puzzle.Write_(row,col,selection);
	GetParent()->GetEventHandler()->AddPendingEvent(wxCommandEvent(wxEVT_BUTTON, 200));
	Close(true);
}


//wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Sudoku Solver", wxDefaultPosition, wxSize(BUTTON_SIZE*9,BUTTON_SIZE*12))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(102, "&Solve\tCtrl-X", "Solve");
    menuFile->AppendSeparator();
    menuFile->Append(101, "&Save\tCtrl-S", "Save");
    menuFile->AppendSeparator();
    menuFile->Append(103, "&Load\tCtrl-L", "Load");
    menuFile->AppendSeparator();
    menuFile->Append(104, "&Clear\tCtrl-C", "Clear");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to Sudoku Solver!");
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, 101);
    Bind(wxEVT_MENU, &MyFrame::OnLoad, this, 103);
    Bind(wxEVT_MENU, &MyFrame::OnSolve, this, 102);
    Bind(wxEVT_MENU, &MyFrame::OnClear, this, 104);

    Bind(wxEVT_BUTTON, &MyFrame::OnRefresh, this, 200);

    wxButton *button;
    int button_count = 0;
    for(int i=0; i<9; i++)
    {
	    for(int j=0; j<9; j++)
	    {
		    button =new wxButton(this, button_count, std::to_string(puzzle.Read_(i,j)), wxPoint(0+j*BUTTON_SIZE,0+i*BUTTON_SIZE), wxSize(BUTTON_SIZE,BUTTON_SIZE),0);
		    Bind(wxEVT_BUTTON, &MyFrame::OnSelectSquare, this, button_count);
		    buttons.push_back(button);
		    button_count++;
	    }
		    
    }
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a Sudoku Solver User Interface using wxWidgets");
}

void MyFrame::OnSelectSquare(wxCommandEvent& event)
{
	SelectNumberDialog *input = new SelectNumberDialog(this, event.GetId(), this->GetScreenPosition());
	input->ShowModal();
}

void MyFrame::OnSave(wxCommandEvent& event)
{
	wxMessageDialog *message = new wxMessageDialog(this, "Are you Sure?\nYou will overwrite current save.", "Are you Sure?", wxYES_NO, wxDefaultPosition);
	if(message->ShowModal() == wxID_YES)
	{
		WriteFile(puzzle, "./save.txt");
	}
}

void MyFrame::OnLoad(wxCommandEvent& event)
{
	wxMessageDialog *message = new wxMessageDialog(this, "Are you Sure?\nYou will lose all unsaved work.", "Are you Sure?", wxYES_NO, wxDefaultPosition);
	if(message->ShowModal() == wxID_YES)
	{
		ReadFile(puzzle, "./save.txt");
		Refresh();
	}
}

void MyFrame::OnSolve(wxCommandEvent& event)
{
	wxMessageDialog *message = new wxMessageDialog(this, "Are you Sure?\nYou will lose all unsaved work.", "Are you Sure?", wxYES_NO, wxDefaultPosition);
	if(message->ShowModal() == wxID_YES)
	{
		SudokuPuzzle puzzle_save = puzzle;
		puzzle = SudokuSolver(puzzle);
		if(puzzle_save == puzzle)
		{
			wxMessageDialog *message = new wxMessageDialog(this, "Your Puzzle is not solvable.", "Your Puzzle is not solvable.", wxOK, wxDefaultPosition);
			message->ShowModal();
		}
		Refresh();
	}
}

void MyFrame::OnClear(wxCommandEvent& event)
{
	wxMessageDialog *message = new wxMessageDialog(this, "Are you Sure?\nYou will lose all unsaved work.", "Are you Sure?", wxYES_NO, wxDefaultPosition);
	if(message->ShowModal() == wxID_YES)
	{
		SudokuPuzzle p1{};
		puzzle = p1; 
		Refresh();
	}
}

void MyFrame::OnRefresh(wxCommandEvent& event)
{
	Refresh();
}

void MyFrame::Refresh()
{
	int counter = 0;
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			buttons[i*9+j]->SetLabel(std::to_string(puzzle.Read_(i,j)));
			counter++;
		}
	}
}
