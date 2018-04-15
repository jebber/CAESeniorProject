#pragma once


// ResolutionPattern dialog

class ResolutionPattern : public CDialog
{
	DECLARE_DYNAMIC(ResolutionPattern)

public:
	ResolutionPattern(CWnd* pParent = NULL);   // standard constructor
	virtual ~ResolutionPattern();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESOLUTION_PATTERN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int ResolutionAzimuth;
	int ResolutionElevation;
	int ResolutionRange;
};
