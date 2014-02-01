/***************************************************************
 * Name:      scdlr3App.cpp
 * Purpose:   Code for Application Class
 * Author:    Technowise (avsharath@gmail.com)
 * Created:   2014-02-01
 * Copyright: Technowise (http://technowise.in)
 * License:
 **************************************************************/

#include "scdlr3App.h"

//(*AppHeaders
#include "scdlr3Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(scdlr3App);

bool scdlr3App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	scdlr3Dialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
