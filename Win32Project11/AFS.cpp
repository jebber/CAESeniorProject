// AFS.cpp : implementation file
//

#include "stdafx.h"
#include "AFS.h"
#include "afxdialogex.h"
#include "resource.h"


// AFS dialog

IMPLEMENT_DYNAMIC(AFS, CDialog)

AFS::AFS(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AFS, pParent)
	, AFSazimuth(0)
	, AFSelevation(0)
	, AFSrange(0)
	, AFSspeedOfRotation(0)
{

}

AFS::~AFS()
{
}

void AFS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AFS_AZIMUTH, AFSazimuth);
	DDX_Text(pDX, IDC_AFS_ELEVATION, AFSelevation);
	DDX_Text(pDX, IDC_AFS_RANGE, AFSrange);
	DDX_Text(pDX, IDC_AFS_SPEED_OF_ROTATION, AFSspeedOfRotation);
}


BEGIN_MESSAGE_MAP(AFS, CDialog)
END_MESSAGE_MAP()


// AFS message handlers
