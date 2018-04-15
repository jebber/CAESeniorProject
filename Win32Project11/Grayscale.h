#pragma once


// Grayscale dialog

class Grayscale : public CDialog
{
	DECLARE_DYNAMIC(Grayscale)

public:
	Grayscale(CWnd* pParent = NULL);   // standard constructor
	virtual ~Grayscale();

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
};
