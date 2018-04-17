#pragma once
#include "Configuration.h"

// Grayscale dialog

class Grayscale : public CDialog
{
	DECLARE_DYNAMIC(Grayscale)

public:
	Grayscale(CWnd* pParent, Configuration* myConfig);   // standard constructor
	virtual ~Grayscale();
	Configuration* config;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAYSCALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL GrayscaleFullPattern;
	bool GrayscaleVertical;
	bool GrayscaleHorizontal;
	afx_msg void OnBnClickedGrayscaleVertical();
	afx_msg void OnBnClickedGrayscaleHorizontal();
	afx_msg void OnBnClickedGrayscaleFullDisplay();
};
