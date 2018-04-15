// ResolutionPattern.cpp : implementation file
//

#include "stdafx.h"
#include "ResolutionPattern.h"
#include "afxdialogex.h"
#include "resource.h"


// ResolutionPattern dialog

IMPLEMENT_DYNAMIC(ResolutionPattern, CDialog)

ResolutionPattern::ResolutionPattern(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RESOLUTION_PATTERN, pParent)
	, ResolutionAzimuth(0)
	, ResolutionElevation(0)
	, ResolutionRange(0)
{

}

ResolutionPattern::~ResolutionPattern()
{
}

void ResolutionPattern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RESOLUTION_AZIMUTH, ResolutionAzimuth);
	DDX_Text(pDX, IDC_RESOLUTION_ELEVATION, ResolutionElevation);
	DDX_Text(pDX, IDC_RESOLUTION_RANGE, ResolutionRange);
}


BEGIN_MESSAGE_MAP(ResolutionPattern, CDialog)
END_MESSAGE_MAP()


// ResolutionPattern message handlers
