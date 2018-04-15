// ColorBars.cpp : implementation file
//

#include "stdafx.h"
#include "ColorBars.h"
#include "afxdialogex.h"
#include "resource.h"


// ColorBars dialog

IMPLEMENT_DYNAMIC(ColorBars, CDialog)

ColorBars::ColorBars(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_COLOR_BARS, pParent)
	, ColorBarsVertical(false)
	, ColorBarsHorizontal(false)
{

}

ColorBars::~ColorBars()
{
}

void ColorBars::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColorBars, CDialog)
END_MESSAGE_MAP()


// ColorBars message handlers
