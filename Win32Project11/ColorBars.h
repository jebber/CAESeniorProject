#pragma once
#include "Configuration.h"

// ColorBars dialog

class ColorBars : public CDialog
{
	DECLARE_DYNAMIC(ColorBars)

public:
	ColorBars(CWnd* pParent, Configuration* config);   // standard constructor
	virtual ~ColorBars();
	Configuration* myConfig;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLOR_BARS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool ColorBarsVertical;
	bool ColorBarsHorizontal;
	afx_msg void OnBnClickedColorBarsVertical();
	afx_msg void OnBnClickedColorBarsHorizontal();
};
