#pragma once
#include "Configuration.h"

// FullWhite dialog

class FullWhite : public CDialog
{
	DECLARE_DYNAMIC(FullWhite)

public:
	FullWhite(CWnd* pParent, Configuration* config);   // standard constructor
	virtual ~FullWhite();
	Configuration* myConfig;
	int input;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FULL_WHITE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int FullWhiteOpacity;
	afx_msg void OnCbnSelchangeFullWhiteOpacity();
};
