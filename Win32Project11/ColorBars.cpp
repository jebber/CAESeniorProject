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
	, ColorBarsVertical(!config->get_display_horizontal())
	, ColorBarsHorizontal(config->get_display_horizontal())
{
	this->myConfig = config;
}

ColorBars::~ColorBars()
{
}

void ColorBars::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, VerticalControl);
	DDX_Control(pDX, IDOK, HorizontalControl);
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

void ColorBars::setButtons() {
	if (this->myConfig->get_display_horizontal()) {
		CButton *ptr = (CButton*)this->GetDlgItem(IDC_COLOR_BARS_HORIZONTAL);
		ptr->SetCheck(BST_CHECKED);
	}
	else {
		CButton *ptr = (CButton*)this->GetDlgItem(IDC_COLOR_BARS_VERTICAL);
		ptr->SetCheck(BST_CHECKED);
	}
}