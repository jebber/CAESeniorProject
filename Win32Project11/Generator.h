//#pragma once
#ifndef TOTALFOV_H
#define TOTALFOV_H

#include "Generator.h"
#include "Configuration.h"

// Generator dialog

class Generator : public CDialog
{
	DECLARE_DYNAMIC(Generator)

public:
	Generator(CWnd* pParent, BOOL display_type, Configuration* config);   // standard constructor
	virtual ~Generator();
	Bitmap* createBitmapPixels(HDC hdc, int totalFOV_width, int totalFOV_height);
	void OnPaint();
	void createImage(CPaintDC & x, BOOL display_type);
	Bitmap* totalFOV_Image;
	std::vector<ChannelConfig>* channels;
	std::vector<Bitmap*> channel_images;


private:
	Configuration* config;
	BOOL display_type;
	int totalFOV_width;
	int totalFOV_height;
	int test_pattern;


	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOTALFOV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#endif
