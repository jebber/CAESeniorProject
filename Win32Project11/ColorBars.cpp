// ColorBars.cpp : implementation file
//

#include "stdafx.h"
#include "ColorBars.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Configuration.h"


// ColorBars dialog

IMPLEMENT_DYNAMIC(ColorBars, CDialog)

ColorBars::ColorBars(CWnd* pParent /*=NULL*/, Configuration* config)
	: CDialog(IDD_COLOR_BARS, pParent)
	, ColorBarsVertical(false)
	, ColorBarsHorizontal(false)
{
	this->myConfig = config;
	/*if (config->get_display_horizontal()) {
		CButton *ptr = (CButton*)GetDlgItem(IDC_COLOR_BARS_HORIZONTAL);
		ptr->SetCheck(BST_CHECKED);
	}
	else {
		CButton *ptr = (CButton*)GetDlgItem(IDC_COLOR_BARS_VERTICAL);
		ptr->SetCheck(BST_CHECKED);
	}*/
		
}

ColorBars::~ColorBars()
{
}

void ColorBars::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColorBars, CDialog)
	ON_BN_CLICKED(IDC_COLOR_BARS_VERTICAL, &ColorBars::OnBnClickedColorBarsVertical)
	ON_BN_CLICKED(IDC_COLOR_BARS_HORIZONTAL, &ColorBars::OnBnClickedColorBarsHorizontal)
END_MESSAGE_MAP()


// ColorBars message handlers


void ColorBars::OnBnClickedColorBarsVertical()
{
	myConfig->set_display_horizontal(false);
}


void ColorBars::OnBnClickedColorBarsHorizontal()
{
	myConfig->set_display_horizontal(true);
}
