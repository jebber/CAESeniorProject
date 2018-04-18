// Grayscale.cpp : implementation file
//

#include "stdafx.h"
#include "Grayscale.h"
#include "afxdialogex.h"
#include "Configuration.h"
#include "resource.h"


// Grayscale dialog

IMPLEMENT_DYNAMIC(Grayscale, CDialog)

Grayscale::Grayscale(CWnd* pParent, Configuration* myConfig)
	: CDialog(IDD_GRAYSCALE, pParent)
	, GrayscaleFullPattern(myConfig->get_full_pattern())
	, GrayscaleVertical(!myConfig->get_display_horizontal())
	, GrayscaleHorizontal(myConfig->get_display_horizontal())
{
	this->config = myConfig;
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
	ON_BN_CLICKED(IDC_GRAYSCALE_VERTICAL, &Grayscale::OnBnClickedGrayscaleVertical)
	ON_BN_CLICKED(IDC_GRAYSCALE_HORIZONTAL, &Grayscale::OnBnClickedGrayscaleHorizontal)
	ON_BN_CLICKED(IDC_GRAYSCALE_FULL_DISPLAY, &Grayscale::OnBnClickedGrayscaleFullDisplay)
END_MESSAGE_MAP()


// Grayscale message handlers


void Grayscale::OnBnClickedGrayscaleVertical()
{
	config->set_display_horizontal(false);
}


void Grayscale::OnBnClickedGrayscaleHorizontal()
{
	config->set_display_horizontal(true);
}


void Grayscale::OnBnClickedGrayscaleFullDisplay()
{
	if (config->get_full_pattern())
		config->set_full_pattern(false);
	else
		config->set_full_pattern(true);
}
