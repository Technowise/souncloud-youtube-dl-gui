/***************************************************************
 * Name:      scdlr3Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Technowise (avsharath@gmail.com)
 * Created:   2014-02-01
 * Copyright: Technowise (http://technowise.in)
 * License:
 **************************************************************/

#include "scdlr3Main.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(scdlr3Dialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(scdlr3Dialog)
const long scdlr3Dialog::ID_TEXTCTRL1 = wxNewId();
const long scdlr3Dialog::ID_BUTTON1 = wxNewId();
const long scdlr3Dialog::ID_CHECKBOX1 = wxNewId();
const long scdlr3Dialog::ID_DIRPICKERCTRL1 = wxNewId();
const long scdlr3Dialog::ID_GAUGE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(scdlr3Dialog,wxDialog)
    //(*EventTable(scdlr3Dialog)
    //*)
END_EVENT_TABLE()

scdlr3Dialog::scdlr3Dialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(scdlr3Dialog)
    wxGridBagSizer* GridBagSizer1;
    wxBoxSizer* BoxSizer1;

    Create(parent, id, _("SoundCloud and YouTube Downloader"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("id"));
    SetClientSize(wxSize(584,242));
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    UrlTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, _("URL"), wxDefaultPosition, wxSize(570,18), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridBagSizer1->Add(UrlTextCtrl, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    DownloadButton = new wxButton(this, ID_BUTTON1, _("Download"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(DownloadButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer1->Add(BoxSizer1, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OpenContaningFolderCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Open Containing folder after download"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    OpenContaningFolderCheckBox->SetValue(false);
    GridBagSizer1->Add(OpenContaningFolderCheckBox, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DirPickerCtrl = new wxDirPickerCtrl(this, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxSize(264,23), wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    GridBagSizer1->Add(DirPickerCtrl, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ProgressGauge = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(179,27), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    GridBagSizer1->Add(ProgressGauge, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridBagSizer1);
    SetSizer(GridBagSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&scdlr3Dialog::OnDownloadButtonClick);
    //*)
}

scdlr3Dialog::~scdlr3Dialog()
{
    //(*Destroy(scdlr3Dialog)
    //*)
}

void scdlr3Dialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void scdlr3Dialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void scdlr3Dialog::OnDownloadButtonClick(wxCommandEvent& event)
{
    wxString selectedPath(this->DirPickerCtrl->GetPath());
    wxString exploreCommand(wxT("explorer "));
    wxString url(this->UrlTextCtrl->GetLineText(1));
    wxString downloadCommand(wxT("youtube-dl "));
    wxString outputFileOption(wxT(" -o "));
    wxString outputFileTitle(wxT("\\%(title)s.%(ext)s "));//ToDo: use platform specific directory separator
    exploreCommand.append(selectedPath);
    downloadCommand.append( outputFileOption );
    downloadCommand.append(selectedPath);
    downloadCommand.append(outputFileTitle);
    downloadCommand.append(url);

    wxArrayString output;
    wxArrayString errors;
    if( selectedPath.Len() < 1)
    {
        wxString msg(wxT("Please select folder to download"));
        wxMessageBox(msg, _("Error"));
    }
    else if( url.Len() <= 3)
    {
        wxString msg(wxT("Please enter URL"));
        wxMessageBox(msg, _("Error"));
    }
    else
    {
        #ifdef __WXMSW__
        this->DirPickerCtrl->Hide();
        this->DownloadButton->Hide();
        this->ProgressGauge->Show();
        this->ProgressGauge->Pulse();
        wxExecute(downloadCommand, output, errors);
        if(this->OpenContaningFolderCheckBox->IsChecked() )
        {
            wxExecute(exploreCommand);
        }
        this->ProgressGauge->Hide();
        this->DirPickerCtrl->Show();
        this->DownloadButton->Show();
        #endif
    }
}
