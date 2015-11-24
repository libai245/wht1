//--------------------------------------------------
//自己定义的AIS列表框
//----------------------hitwh wht 2015.10.12

#include "MYAISListDialog.h"
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/tokenzr.h>

#include "AISTargetListDialog.h"
#include "ais.h"
#include "AIS_Decoder.h"
#include "AIS_Target_Data.h"
#include "OCPNListCtrl.h"
#include "styles.h"
#include "Select.h"
#include "routemanagerdialog.h"
#include <wx/listctrl.h>


extern wxString g_AisTargetList_perspective;
extern MyConfig *pConfig;
MyAISlistDialog::MyAISlistDialog(wxWindow *parent,wxAuiManager *auimgr){
	wxPanel* MyAISList = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize( 200, 200), wxDEFAULT);


	//列表控件
	wxBoxSizer* topSizer = new wxBoxSizer( wxVERTICAL);
	this->SetSizer( topSizer );
	wxListCtrl *AISList = new wxListCtrl(MyAISList,wxID_ANY,wxDefaultPosition,wxSize(400,400),wxLC_REPORT ,wxDefaultValidator,_T("AISList"));
	//wxListItem itemCol;
	//AISList->SetMask();
	AISList->InsertColumn(Lon,_("Lon"), wxLIST_FORMAT_LEFT, 44); 
	AISList->InsertColumn(Lat,_("Lat"), wxLIST_FORMAT_LEFT, 44); 
	AISList->InsertColumn(MMSI,_("MMSI"), wxLIST_FORMAT_LEFT, 100); 
	/*wxListItem item;
	item.SetId(4);
	item.SetMask(wxLIST_MASK_DATA|wxLIST_MASK_TEXT);
	item.SetText(_T("123"));*/
	
	//AISList->SetItem(item);
	//AISList->SetColumnWidth(0, 40 );
	for (int i = 0;i < 10;i++)
	{
		AISList->InsertItem(Lat, _T("123"));

	}
	
	
	topSizer->Add( AISList, 1, wxEXPAND | wxALL, 0);
	
	
	wxAuiPaneInfo pane =
		wxAuiPaneInfo().Name( _T("AISTargetList") ).CaptionVisible( true ).Float().FloatingPosition( 50, 50 );
	
	m_pAuiManager = auimgr;
	//      Force and/or override any perspective information that is not applicable
	pane.Name( _T("AISTargetList") );
	pane.DestroyOnClose( true );
	pane.TopDockable( false ).BottomDockable( true ).LeftDockable( false ).RightDockable( false );
	pane.Show( true );

	bool b_reset_pos = false;

	if( (pane.floating_size.x != -1) && (pane.floating_size.y != -1)){
#ifdef __WXMSW__
		//  Support MultiMonitor setups which an allow negative window positions.
		//  If the requested window title bar does not intersect any installed monitor,
		//  then default to simple primary monitor positioning.
		RECT frame_title_rect;
		frame_title_rect.left = pane.floating_pos.x;
		frame_title_rect.top = pane.floating_pos.y;
		frame_title_rect.right = pane.floating_pos.x + pane.floating_size.x;
		frame_title_rect.bottom = pane.floating_pos.y + 30;

		if( NULL == MonitorFromRect( &frame_title_rect, MONITOR_DEFAULTTONULL ) )
			b_reset_pos = true;
#else

		//    Make sure drag bar (title bar) of window intersects wxClient Area of screen, with a little slop...
		wxRect window_title_rect;// conservative estimate
		window_title_rect.x = pane.floating_pos.x;
		window_title_rect.y = pane.floating_pos.y;
		window_title_rect.width = pane.floating_size.x;
		window_title_rect.height = 30;

		wxRect ClientRect = wxGetClientDisplayRect();
		ClientRect.Deflate(60, 60);// Prevent the new window from being too close to the edge
		if(!ClientRect.Intersects(window_title_rect))
			b_reset_pos = true;

#endif

		if( b_reset_pos )
			pane.FloatingPosition( 50, 50 );
	}

	//    If the list got accidentally dropped on top of the chart bar, move it away....
	if( pane.IsDocked() && ( pane.dock_row == 0 ) ) {
		pane.Float();
		pane.Row( 1 );
		pane.Position( 0 );

		g_AisTargetList_perspective = m_pAuiManager->SavePaneInfo( pane );
		pConfig->UpdateSettings();
	}

	pane.Caption( wxGetTranslation( _("AIS target list") ) );
	pane.Show();
	m_pAuiManager->AddPane( MyAISList, pane );
	m_pAuiManager->Update();
	topSizer->Show(true);
	MyAISList->Show(true);



}