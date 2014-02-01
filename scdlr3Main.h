/***************************************************************
 * Name:      scdlr3Main.h
 * Purpose:   Defines Application Frame
 * Author:    Technowise (avsharath@gmail.com)
 * Created:   2014-02-01
 * Copyright: Technowise (http://technowise.in)
 * License:
 **************************************************************/

#ifndef SCDLR3MAIN_H
#define SCDLR3MAIN_H

//(*Headers(scdlr3Dialog)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
//*)

class scdlr3Dialog: public wxDialog
{
    public:

        scdlr3Dialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~scdlr3Dialog();

    private:

        //(*Handlers(scdlr3Dialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnDownloadButtonClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(scdlr3Dialog)
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_CHECKBOX1;
        static const long ID_DIRPICKERCTRL1;
        static const long ID_GAUGE1;
        //*)

        //(*Declarations(scdlr3Dialog)
        wxButton* DownloadButton;
        wxCheckBox* OpenContaningFolderCheckBox;
        wxDirPickerCtrl* DirPickerCtrl;
        wxTextCtrl* UrlTextCtrl;
        wxGauge* ProgressGauge;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SCDLR3MAIN_H
