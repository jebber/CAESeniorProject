// FullWhite.cpp : implementation file
//

#include "stdafx.h"
#include "FullWhite.h"
#include "afxdialogex.h"
#include "resource.h"


// FullWhite dialog

IMPLEMENT_DYNAMIC(FullWhite, CDialog)

FullWhite::FullWhite(CWnd* pParent, Configuration* config)
	: CDialog(IDD_FULL_WHITE, pParent)
	, FullWhiteOpacity(config->get_opacity())
{
	this->myConfig = config;
}

FullWhite::~FullWhite()
{
}

void FullWhite::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_FULL_WHITE_OPACITY, FullWhiteOpacity);
}


BEGIN_MESSAGE_MAP(FullWhite, CDialog)
	ON_CBN_SELCHANGE(IDC_FULL_WHITE_OPACITY, &FullWhite::OnCbnSelchangeFullWhiteOpacity)
END_MESSAGE_MAP()


// FullWhite message handlers


void FullWhite::OnCbnSelchangeFullWhiteOpacity()
{
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_FULL_WHITE_OPACITY);
	input = m_pComboBox->GetCurSel();
}
