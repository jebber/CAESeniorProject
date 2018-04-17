#ifndef DISPLAYFRAME_H
#define DISPLAYFRAME_H

#include "DisplayFrame.h"
#include "Configuration.h"
#include "ChannelConfig.h"

// Generator dialog

class DisplayFrame : public CFrameWnd
{

public:
	DisplayFrame(Configuration* config, int channel_index);   // standard constructor
	virtual ~DisplayFrame();
	void OnPaint();
	Bitmap* createBitmapPixels(HDC hdc, int total_pixels_h, int total_pixels_v);
	void createImage(CPaintDC & x);
	Bitmap* totalFOV_Image;
	std::vector<ChannelConfig>* channels;
	std::vector<Bitmap*> channel_images;



private:
	Configuration* config;
	ChannelConfig* channel;
	int channel_index;
	int totalFOV_width;
	int totalFOV_height;
	int test_pattern;

	DECLARE_MESSAGE_MAP()
};

#endif
