//--------------------------------------------------
//自己定义的AIS列表框
//----------------------hitwh wht 2015.10.12


#include <wx/panel.h>
#include <wx/checkbox.h>
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

class MyAISlistDialog: public wxPanel
{
public:
	MyAISlistDialog(wxWindow *parent,wxAuiManager *auimgr);
	void UpDataAISList(void);
	wxAuiManager      *m_pAuiManager;
	
};
enum AIS_DATA
{
	Lon = 0,
	Lat ,
	MMSI

};