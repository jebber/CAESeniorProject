// Grayscale.cpp : implementation file
//

#include "stdafx.h"
#include "Grayscale.h"
#include "afxdialogex.h"
#include "resource.h"


// Grayscale dialog

IMPLEMENT_DYNAMIC(Grayscale, CDialog)

Grayscale::Grayscale(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GRAYSCALE, pParent)
	, GrayscaleFullPattern(FALSE)
	, GrayscaleVertical(false)
	, GrayscaleHorizontal(false)
{

}

Grayscale::~Grayscale()
{
}

void Grayscale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_GRAYSCALE_FULL_DISPLAY, GrayscaleFullPattern);
}


BEGIN_MESSAGE_MAP(Grayscale, CDialog)
END_MESSAGE_MAP()


// Grayscale message handlers
