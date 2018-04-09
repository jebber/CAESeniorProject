// Generator.cpp : implementation file
//

#include "stdafx.h"
#include "Generator.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ChannelConfig.h"
#include "Configuration.h"

// Generator dialog

IMPLEMENT_DYNAMIC(Generator, CDialog)

Generator::Generator(CWnd* pParent /*=NULL*/, BOOL display_type, Configuration* config)
	: CDialog(IDD_FOV_DISPLAY, pParent)
{
	this->display_type = display_type;
	this->config = config;

	totalFOV_width = config->get_total_fov_h();
	totalFOV_height = config->get_total_fov_v();
	test_pattern = config->get_test_pattern();
	channels = config->get_channels();
}

Generator::~Generator()
{
}

Bitmap* Generator::createBitmapPixels(HDC hdc, int totalFOV_width, int totalFOV_height)
{
	Bitmap* bitmap = new Bitmap(totalFOV_width, totalFOV_height, 2498570);
	return bitmap;
}

void Generator::OnPaint()
{
	CPaintDC dc(this);
	createImage(dc, this->display_type);
}

void Generator::createImage(CPaintDC & x, BOOL display_type)
{
	totalFOV_Image = createBitmapPixels(x, totalFOV_width, totalFOV_height);

	switch (test_pattern) {
	case 1: //GrayScale

		Color pixelColor(255, 0, 0, 0);	//default of black

		int i = 0;
		int j = 0;
		int stripeSize = totalFOV_height / 10;
		//1st stripe - white
		for (int i = 0; i < stripeSize; i++)
		{
			ARGB argb = Color::MakeARGB(0, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 1st stripe for
		} //end 1st stripe for

		  //2nd stripe
		for (int i = stripeSize; i < stripeSize * 2; i++)
		{
			ARGB argb = Color::MakeARGB(28, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 2nd stripe for
		} //end 2nd stripe for

		  //3rd stripe
		for (int i = stripeSize * 2; i < stripeSize * 3; i++)
		{
			ARGB argb = Color::MakeARGB(56, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 3rd stripe for 
		} //end 3rd stripe for 

		  //4th stripe
		for (int i = stripeSize * 3; i < stripeSize * 4; i++)
		{
			ARGB argb = Color::MakeARGB(84, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 4th stripe for 
		} //end 4th stripe for 

		  //5th stripe
		for (int i = stripeSize * 4; i < stripeSize * 5; i++)
		{
			ARGB argb = Color::MakeARGB(112, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 5th stripe for
		} //end 5th stripe for

		  //6th stripe
		for (int i = stripeSize * 5; i < stripeSize * 6; i++)
		{
			ARGB argb = Color::MakeARGB(140, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 6th stripe for 
		} //end 6th stripe for 

		  //7th stripe
		for (int i = stripeSize * 6; i < stripeSize * 7; i++)
		{
			ARGB argb = Color::MakeARGB(168, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 7th stripe for 
		} //end 7th stripe for 

		  //8th stripe
		for (int i = stripeSize * 7; i < stripeSize * 8; i++)
		{
			ARGB argb = Color::MakeARGB(196, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 8th stripe for 
		} //end 8th stripe for 

		  //9th stripe
		for (int i = stripeSize * 8; i < stripeSize * 9; i++)
		{
			ARGB argb = Color::MakeARGB(224, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //9th stripe for 
		} //end 9th stripe for 

		  //10th stripe - black
		for (int i = stripeSize * 9; i < totalFOV_height; i++)
		{
			ARGB argb = Color::MakeARGB(255, 0, 0, 0);
			for (int j = 0; j < totalFOV_width; j++)
			{
				pixelColor.SetValue(argb);
				totalFOV_Image->SetPixel(j, i, pixelColor);
			} //end 10th stripe for 
		} //end 10th stripe for 

		Graphics graphics(x);
		if (display_type) {
			//display totalFOV image
			graphics.DrawImage(&*totalFOV_Image, 0, 0);
		}
		else {
			//display channels

			//convert degrees to pixels
			int pixelsPerDegreeX = totalFOV_width / 180;
			int pixelsPerDegreeY = totalFOV_height / 180;

			//Loop through ChannelConfig vector, create and display bitmaps for each channel
			for (std::vector<ChannelConfig>::iterator it = channels->begin(); it != channels->end(); it++) {

				//pixel location of center of channel
				int channel_loc_hPixels = pixelsPerDegreeX * it->get_location_h();
				int channel_loc_vPixels = pixelsPerDegreeY * it->get_location_v();

				//pixel location of top left corner of channel
				int channel_TopLeftCornerX = channel_loc_hPixels - it->get_fov_h() / 2;
				int channel_TopLeftCornerY = channel_loc_vPixels - it->get_fov_v() / 2;

				Bitmap* bmp = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, it->get_fov_h(), it->get_fov_v(), 2498570);

				graphics.DrawImage(bmp, channel_loc_hPixels, channel_loc_vPixels);

			}
		}
		break;

	}

}



void Generator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(Generator, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Generator message handlers
