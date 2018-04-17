#include "stdafx.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include "DisplayFrame.h"
#include "Configuration.h"
#include "ChannelConfig.h"


DisplayFrame::DisplayFrame(Configuration* config, int channel_index)
{
	this->channel_index = channel_index;
	this->config = config;

	totalFOV_width = config->get_total_fov_h();
	totalFOV_height = config->get_total_fov_v();
	test_pattern = config->get_test_pattern();
	channel = &config->get_channels()->at(channel_index);
	Create(0, NULL, WS_POPUP, CRect(0, 0, channel->get_resolution_h(), channel->get_resolution_v()));
	
}

DisplayFrame::~DisplayFrame() {}

Bitmap* DisplayFrame::createBitmapPixels(HDC hdc, int total_pixels_h, int total_pixels_v)
{
	Bitmap* bitmap = new Bitmap(total_pixels_h, total_pixels_v, 2498570);
	return bitmap;
}

void DisplayFrame::OnPaint()
{
	CPaintDC dc(this);
	createImage(dc);
}

void DisplayFrame::createImage(CPaintDC & x)
{
	
	int resX =  (config->get_total_fov_h() * channel->get_resolution_h()) / channel->get_fov_h();
	int resY = (config->get_total_fov_v() * channel->get_resolution_v()) / channel->get_fov_v();
	
	int pixelsPerDegreeX = resX / config->get_total_fov_h();
	int pixelsPerDegreeY = resY / config->get_total_fov_v();
	
	//pixel location of center of channel 
	int channel_loc_hPixels = pixelsPerDegreeX * channel->get_location_h();
	int channel_loc_vPixels = pixelsPerDegreeY * channel->get_location_v();

	int blockSizeX = pixelsPerDegreeX * 5;
	int blockSizeY = pixelsPerDegreeY * 5;

	int numLinesX = resX / pixelsPerDegreeX;
	int numLinesY = resY / pixelsPerDegreeY;

	int i = 0;
	int j = 0;
	int ni = 1;
	int nj = 1;
	
	//FFFFIIIIIIXXXXX
	int opacity = 100;

	ARGB white0 = Color::MakeARGB(0, 255, 255, 255);
	ARGB white11 = Color::MakeARGB(28, 255, 255, 255);
	ARGB white22 = Color::MakeARGB(56, 255, 255, 255);
	ARGB white33 = Color::MakeARGB(84, 255, 255, 255);
	ARGB white44 = Color::MakeARGB(112, 255, 255, 255);
	ARGB white55 = Color::MakeARGB(140, 255, 255, 255);
	ARGB white66 = Color::MakeARGB(168, 255, 255, 255);
	ARGB white77 = Color::MakeARGB(196, 255, 255, 255);
	ARGB white88 = Color::MakeARGB(224, 255, 255, 255);
	ARGB white100 = Color::MakeARGB(255, 255, 255, 255);
	ARGB white = Color::MakeARGB(255, 255, 255, 255);
	ARGB black = Color::MakeARGB(255, 0, 0, 0);
	ARGB green = Color::MakeARGB(255, 0, 255, 0);

	bool display_horizontal = config->get_display_horizontal();

	totalFOV_Image = createBitmapPixels(x, resX, resY);
	
	Color pixelColor(255, 0, 0, 0);    //default of black
	Graphics graphics(x);
	Bitmap* channel_image;

	switch (test_pattern) {

	/*****************************
	/		GRAYSCALE 
	******************************/
	case 0:
		
		/*****************************
		HORIZONTAL
		*****************************/
		if (display_horizontal)
		{
			int stripeSize = resY / 10;

			//1st stripe - white
			for (int i = 0; i < stripeSize; i++)
			{
				ARGB argb = Color::MakeARGB(0, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 1st stripe for
			} //end 1st stripe for

			  //2nd stripe
			for (int i = stripeSize; i < stripeSize * 2; i++)
			{
				ARGB argb = Color::MakeARGB(28, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 2nd stripe for
			} //end 2nd stripe for

			  //3rd stripe
			for (int i = stripeSize * 2; i < stripeSize * 3; i++)
			{
				ARGB argb = Color::MakeARGB(56, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 3rd stripe for 
			} //end 3rd stripe for 

			  //4th stripe
			for (int i = stripeSize * 3; i < stripeSize * 4; i++)
			{
				ARGB argb = Color::MakeARGB(84, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 4th stripe for 
			} //end 4th stripe for 

			  //5th stripe
			for (int i = stripeSize * 4; i < stripeSize * 5; i++)
			{
				ARGB argb = Color::MakeARGB(112, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 5th stripe for
			} //end 5th stripe for

			  //6th stripe
			for (int i = stripeSize * 5; i < stripeSize * 6; i++)
			{
				ARGB argb = Color::MakeARGB(140, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 6th stripe for 
			} //end 6th stripe for 

			  //7th stripe
			for (int i = stripeSize * 6; i < stripeSize * 7; i++)
			{
				ARGB argb = Color::MakeARGB(168, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 7th stripe for 
			} //end 7th stripe for 

			  //8th stripe
			for (int i = stripeSize * 7; i < stripeSize * 8; i++)
			{
				ARGB argb = Color::MakeARGB(196, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 8th stripe for 
			} //end 8th stripe for 

			  //9th stripe
			for (int i = stripeSize * 8; i < stripeSize * 9; i++)
			{
				ARGB argb = Color::MakeARGB(224, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //9th stripe for 
			} //end 9th stripe for 

			  //10th stripe - black
			for (int i = stripeSize * 9; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(255, 0, 0, 0);
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 10th stripe for 
			} //end 10th stripe for 
		} //end horizontal orientation

		  /******************************
		  VERTICAL
		  ********************************/
		else
		{
			int stripeSize = resX / 10;

			//1st stripe - white
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(0, 0, 0, 0);
				for (int j = 0; j < stripeSize; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 1st stripe for
			} //end 1st stripe for

			  //2nd stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(28, 0, 0, 0);
				for (int j = stripeSize; j < stripeSize * 2; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 2nd stripe for
			} //end 2nd stripe for

			  //3rd stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(56, 0, 0, 0);
				for (int j = stripeSize * 2; j < stripeSize * 3; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 3rd stripe for 
			} //end 3rd stripe for 

			  //4th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(84, 0, 0, 0);
				for (int j = stripeSize * 3; j < stripeSize * 4; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 4th stripe for 
			} //end 4th stripe for 

			  //5th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(112, 0, 0, 0);
				for (int j = stripeSize * 4; j < stripeSize * 5; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 5th stripe for
			} //end 5th stripe for

			  //6th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(140, 0, 0, 0);
				for (int j = stripeSize * 5; j < stripeSize * 6; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 6th stripe for 
			} //end 6th stripe for 

			  //7th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(168, 0, 0, 0);
				for (int j = stripeSize * 6; j < stripeSize * 7; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 7th stripe for 
			} //end 7th stripe for 

			  //8th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(196, 0, 0, 0);
				for (int j = stripeSize * 7; j < stripeSize * 8; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 8th stripe for 
			} //end 8th stripe for 

			  //9th stripe
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(224, 0, 0, 0);
				for (int j = stripeSize * 8; j < stripeSize * 9; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //9th stripe for 
			} //end 9th stripe for 

			  //10th stripe - black
			for (int i = 0; i < resY; i++)
			{
				ARGB argb = Color::MakeARGB(255, 0, 0, 0);
				for (int j = stripeSize * 9; j < resX; j++)
				{
					pixelColor.SetValue(argb);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				} //end 10th stripe for 
			} //end 10th stripe for 
		} //end vertical orientation
		
		//clone channel bitmap from total FOV image
		channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
		graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);

		break;

		/*****************************
		/		Checkerboard 
		******************************/
		case 1:

			for (j = 0; j < resY; j += blockSizeY)
			{
				for (i = 0; i < resX; i += blockSizeX)
				{
					if ((nj % 2 != 0) && (ni % 2 != 0))
					{
						for (int l = j; l < j + blockSizeY; l++)
						{
							for (int k = i; k < i + blockSizeX; k++)
							{
								pixelColor.SetValue(black);
								totalFOV_Image->SetPixel(k, l, pixelColor);
							}
						}
						ni++;
					}
					else if ((nj % 2 == 0) && (ni % 2 == 0))
					{
						for (int l = j; l < j + blockSizeY; l++)
						{
							for (int k = i; k < i + blockSizeX; k++)
							{
								pixelColor.SetValue(black);
								totalFOV_Image->SetPixel(k, l, pixelColor);
							}
						}
						ni++;
					}
					else
					{
						for (int l = j; l < j + blockSizeY; l++)
						{
							for (int k = i; k < i + blockSizeX; k++)
							{
								pixelColor.SetValue(white);
								totalFOV_Image->SetPixel(k, l, pixelColor);
							}
						}
						ni++;
					}

				}
				nj++;

			} //end for

			channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
			graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);
			
			break;
		
		/*****************************
		/		Color Bars
		******************************/
		case 2:
			if (!display_horizontal)
			{
				int stripeSize = resX / 8;

				//White - 100% R,G,B
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 255, 255);
					for (int j = 0; j < stripeSize; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Yellow - 100 % R, G 0 % B
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 255, 0);
					for (int j = stripeSize; j < stripeSize * 2; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//Cyan - 100 % G, B 0 % R
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 255, 255);
					for (int j = stripeSize * 2; j < stripeSize * 3; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//Green - 100 % G  0 % R, B
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 255, 0);
					for (int j = stripeSize * 3; j < stripeSize * 4; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Magenta - 100 % R, B 0 % G
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 0, 255);
					for (int j = stripeSize * 4; j < stripeSize * 5; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Red - 100 % R  0 % B, G
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 0, 0);
					for (int j = stripeSize * 5; j < stripeSize * 6; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Blue - 100 % B 0 % R, G
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 0, 255);
					for (int j = stripeSize * 6; j < stripeSize * 7; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Black - 0 % RGB
				for (int i = 0; i < resY; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 0, 0);
					for (int j = stripeSize * 7; j < stripeSize * 8; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
			} //end horizontal

			else
			{
				int stripeSize = resY / 8;

				//White - 100% R,G,B
				for (int i = 0; i < stripeSize; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 255, 255);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Yellow - 100 % R, G 0 % B
				for (int i = stripeSize; i < stripeSize * 2; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 255, 0);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//Cyan - 100 % G, B 0 % R
				for (int i = stripeSize * 2; i < stripeSize * 3; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 255, 255);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//Green - 100 % G  0 % R, B
				for (int i = stripeSize * 3; i < stripeSize * 4; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 255, 0);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Magenta - 100 % R, B 0 % G
				for (int i = stripeSize * 4; i < stripeSize * 5; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 0, 255);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Red - 100 % R  0 % B, G
				for (int i = stripeSize * 5; i < stripeSize * 6; i++)
				{
					ARGB argb = Color::MakeARGB(255, 255, 0, 0);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Blue - 100 % B 0 % R, G
				for (int i = stripeSize * 6; i < stripeSize * 7; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 0, 255);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
				//Black - 0 % RGB
				for (int i = stripeSize * 7; i < stripeSize * 8; i++)
				{
					ARGB argb = Color::MakeARGB(255, 0, 0, 0);
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(argb);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
			} //end horizontal

			channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
			graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);

			break;

		/*****************************
		/		1-Degree Grid
		******************************/
		case 3:
			//total fov image black
			for (int i = 0; i < resY; i++)
			{
				for (int j = 0; j < resX; j++)
				{
					pixelColor.SetValue(black);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				}
			}

			//lines 1 degree apart
			//vertical lines
			for (int i = 0; i < resY; i++)
			{
				for (int j = 0; j < resX; j += pixelsPerDegreeX)
				{
					pixelColor.SetValue(white);
					totalFOV_Image->SetPixel(j, i, pixelColor);
				}
			}

			//horizontal lines
			for (int i = 0; i < resY; i += pixelsPerDegreeY)
			{
				for (int j = 0; j < resX; j++)
				{
					if (i == resY / 2)
					{
						pixelColor.SetValue(green);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
					else
					{
						pixelColor.SetValue(white);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}
			}
			
			channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
			graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);

			break;

		/*****************************
		/		Resolution
		******************************/
		case 4:

			//int vBarStartY = resY * 0.1;
			//int vBarHeight = resY * 0.4;
			//int numBars = 0;
			//int hBarStartX = resX * 0.3;
			//int hBarEndX = resX - hBarStartX;
			//int vBarWidth = (hBarEndX - hBarStartX) / 10;
			//int vBarStartX = hBarStartX;
			//int hBarWidth = hBarEndX - hBarStartX;
			//int hBarEndY = resY - vBarStartY;
			//int hBarStartY = vBarStartY + vBarHeight + vBarWidth;
			//int hBarHeight = (hBarEndY - vBarStartY) / 20;



			////black background
			//for (int i = 0; i < resY; i++)
			//{
			//	for (int j = 0; j < resX; j++)
			//	{
			//		pixelColor.SetValue(black);
			//		totalFOV_Image->SetPixel(j, i, pixelColor);
			//	}
			//}

			////convert degrees to pixels
			//int pixelsPerDegreeX = resX / 180;
			//int pixelsPerDegreeY = resY / 180;

			//int range_adjustment = 40; //degrees to left or right, neg if left, pos if right
			//int range_adjustment_pixels = pixelsPerDegreeX * abs(range_adjustment);

			//int elevation_adjustment = -20; //degrees up or down, pos if up, neg if down
			//int elevation_adjustment_pixels = pixelsPerDegreeY * abs(elevation_adjustment);

			////move image to left
			//if (range_adjustment < 0 && elevation_adjustment == 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			if (j > vBarStartY && j < vBarStartY + vBarHeight)
			//			{
			//				//bar 1
			//				if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + vBarWidth - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + hBarWidth - range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY && j < hBarStartY + hBarHeight)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 && j < hBarStartY + hBarHeight * 3)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 && j < hBarStartY + hBarHeight * 5)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 && j < hBarStartY + hBarHeight * 7)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 && j < hBarStartY + hBarHeight * 9)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//} //end adjust to left

			//  //move image left and up
			//if (range_adjustment < 0 && elevation_adjustment > 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill in black
			//			if (j > vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			if (j > vBarStartY - elevation_adjustment_pixels && j < vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + vBarWidth - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight - elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + hBarWidth - range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY - elevation_adjustment_pixels && j < hBarStartY + hBarHeight - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//}

			////move image left and down
			//if (range_adjustment < 0 && elevation_adjustment < 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill black
			//			if (j < vBarStartY + elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			if (j > vBarStartY + elevation_adjustment_pixels && j < vBarStartY + vBarHeight + elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + vBarWidth - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 - range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 - range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight + elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX - range_adjustment_pixels && i < hBarStartX + hBarWidth - range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY + elevation_adjustment_pixels && j < hBarStartY + hBarHeight + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//}

			////move image to right
			//if (range_adjustment > 0 && elevation_adjustment == 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			if (j > vBarStartY && j < vBarStartY + vBarHeight)
			//			{
			//				//bar 1
			//				if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + vBarWidth + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + hBarWidth + range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY && j < hBarStartY + hBarHeight)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 && j < hBarStartY + hBarHeight * 3)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 && j < hBarStartY + hBarHeight * 5)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 && j < hBarStartY + hBarHeight * 7)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 && j < hBarStartY + hBarHeight * 9)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//}

			////move image right and up
			//if (range_adjustment > 0 && elevation_adjustment > 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill in black
			//			if (j > vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			if (j > vBarStartY - elevation_adjustment_pixels && j < vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + vBarWidth + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight - elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + hBarWidth + range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY - elevation_adjustment_pixels && j < hBarStartY + hBarHeight - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//}

			////move image right and down
			//if (range_adjustment > 0 && elevation_adjustment < 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill black
			//			if (j < vBarStartY + elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			if (j > vBarStartY + elevation_adjustment_pixels && j < vBarStartY + vBarHeight + elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + vBarWidth + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 3 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 5 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 7 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 + range_adjustment_pixels && i < hBarStartX + vBarWidth * 9 + range_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight + elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{
			//			if (i > hBarStartX + range_adjustment_pixels && i < hBarStartX + hBarWidth + range_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (j > hBarStartY + elevation_adjustment_pixels && j < hBarStartY + hBarHeight + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//}

			////move image up
			//if (elevation_adjustment > 0 && range_adjustment == 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill in black
			//			if (j > vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			//draw bars
			//			if (j > vBarStartY - elevation_adjustment_pixels  && j < vBarStartY + vBarHeight - elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX && i < hBarStartX + vBarWidth)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (i > hBarStartX + vBarWidth * 2 && i < hBarStartX + vBarWidth * 3)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (i > hBarStartX + vBarWidth * 4 && i < hBarStartX + vBarWidth * 5)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (i > hBarStartX + vBarWidth * 6 && i < hBarStartX + vBarWidth * 7)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (i > hBarStartX + vBarWidth * 8 && i < hBarStartX + vBarWidth * 9)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars

			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight - elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{

			//			//draw bars
			//			if (i > hBarStartX && i < hBarStartX + hBarWidth)
			//			{
			//				//bar 1
			//				if (j > hBarStartY - elevation_adjustment_pixels  && j < hBarStartY + hBarHeight - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 - elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 - elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//} //end move up

			//  //move image down
			//if (elevation_adjustment < 0 && range_adjustment == 0)
			//{
			//	//vertical white bars
			//	for (int i = 0; i < resX; i++)
			//	{
			//		for (int j = 0; j < resY; j++)
			//		{
			//			//fill black
			//			if (j < vBarStartY + elevation_adjustment_pixels)
			//			{
			//				pixelColor.SetValue(black);
			//				totalFOV_Image->SetPixel(i, j, pixelColor);
			//			}

			//			//draw bars
			//			if (j > vBarStartY + elevation_adjustment_pixels && j < vBarStartY + vBarHeight + elevation_adjustment_pixels)
			//			{
			//				//bar 1
			//				if (i > hBarStartX && i < hBarStartX + vBarWidth)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				else if (i > hBarStartX + vBarWidth * 2 && i < hBarStartX + vBarWidth * 3)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				else if (i > hBarStartX + vBarWidth * 4 && i < hBarStartX + vBarWidth * 5)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				else if (i > hBarStartX + vBarWidth * 6 && i < hBarStartX + vBarWidth * 7)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				else if (i > hBarStartX + vBarWidth * 8 && i < hBarStartX + vBarWidth * 9)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				else
			//				{
			//					pixelColor.SetValue(black);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end vertical white bars


			//	  //fill black
			//	for (int k = vBarStartY + vBarHeight + elevation_adjustment_pixels; k < resY; k++)
			//	{
			//		for (int n = 0; n < resX; n++)
			//		{
			//			pixelColor.SetValue(black);
			//			totalFOV_Image->SetPixel(n, k, pixelColor);
			//		}
			//	}

			//	//horizontal white bars
			//	for (int j = 0; j < resY; j++)
			//	{
			//		for (int i = 0; i < resX; i++)
			//		{

			//			//draw bars
			//			if (i > hBarStartX && i < hBarStartX + hBarWidth)
			//			{
			//				//bar 1
			//				if (j > hBarStartY + elevation_adjustment_pixels  && j < hBarStartY + hBarHeight + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 2
			//				if (j > hBarStartY + hBarHeight * 2 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 3 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 3
			//				if (j > hBarStartY + hBarHeight * 4 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 5 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 4
			//				if (j > hBarStartY + hBarHeight * 6 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 7 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}

			//				//bar 5
			//				if (j > hBarStartY + hBarHeight * 8 + elevation_adjustment_pixels && j < hBarStartY + hBarHeight * 9 + elevation_adjustment_pixels)
			//				{
			//					pixelColor.SetValue(white);
			//					totalFOV_Image->SetPixel(i, j, pixelColor);
			//				}
			//			} //end outer if					
			//		} //end for
			//	} //end horizontal white bars
			//} //end move down

			//channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
			//graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);
			//
			//break;

			/*****************************
			/		Flat White
			******************************/
			case 5:
				if (opacity == 0)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white0);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 1)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white11);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 2)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white22);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 3)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white33);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 4)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white44);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 5)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white55);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 6)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white66);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 7)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white77);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 8)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white88);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}
				else if (opacity == 9)
				{
					for (i = 0; i < resY; i++)
					{
						for (j = 0; j < resX; j++)
						{
							pixelColor.SetValue(white100);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}

				channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
				graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);

				break;
			/*****************************
			/		5-Degree grid
			******************************/
			case 6:
				//total fov image black
				for (int i = 0; i < resY; i++)
				{
					for (int j = 0; j < resX; j++)
					{
						pixelColor.SetValue(black);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//lines 5 degree apart
				//vertical lines
				for (int i = 0; i < resY; i++)
				{
					for (int j = 0; j < resX; j += pixelsPerDegreeY * 5)
					{
						pixelColor.SetValue(white);
						totalFOV_Image->SetPixel(j, i, pixelColor);
					}
				}

				//horizontal lines
				for (int i = 0; i < resY; i += pixelsPerDegreeX * 5)
				{
					for (int j = 0; j < resX; j++)
					{
						if (i == resY / 2)
						{
							pixelColor.SetValue(green);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
						else
						{
							pixelColor.SetValue(white);
							totalFOV_Image->SetPixel(j, i, pixelColor);
						}
					}
				}

				channel_image = totalFOV_Image->Clone(channel_loc_hPixels, channel_loc_vPixels, channel->get_resolution_h(), channel->get_resolution_v(), 2498570);
				graphics.DrawImage(channel_image, channel_loc_hPixels, channel_loc_vPixels);

				break;
			/*****************************
			/		Resolution H 
			******************************/
			case 7:

				break;
			/*****************************
			/		AFS 205 Smear
			******************************/
			case 8:

				break;




	}

}

BEGIN_MESSAGE_MAP(DisplayFrame, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()