#pragma once


// FullWhite dialog

class FullWhite : public CDialog
{
	DECLARE_DYNAMIC(FullWhite)

public:
	FullWhite(CWnd* pParent = NULL);   // standard constructor
	virtual ~FullWhite();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FULL_WHITE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int FullWhiteOpacity;
};
