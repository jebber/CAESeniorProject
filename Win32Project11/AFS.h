#pragma once


// AFS dialog

class AFS : public CDialog
{
	DECLARE_DYNAMIC(AFS)

public:
	AFS(CWnd* pParent = NULL);   // standard constructor
	virtual ~AFS();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int AFSazimuth;
	int AFSelevation;
	int AFSrange;
	int AFSspeedOfRotation;
};
