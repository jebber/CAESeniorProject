#include "stdafx.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include "Configuration.h"
#include "Generator.h"
#include "ChannelConfig.h"
#include "ResolutionPattern.h"
#include "AFS.h"
#include "Grayscale.h"
#include "ColorBars.h"
#include "FullWhite.h"

Configuration *myConfig;

class MainDialog : public CDialog
{

public:
	CMenu MainMenu;
	std::ofstream outFile;
	std::ifstream inFile;
	
	MainDialog(CWnd* pParent = NULL): CDialog(MainDialog::IDD, pParent)
		, ViewerDistance(0)
		, ScreenHFOV(0)
		, ScreenVFOV(0)
		, NumberOfChannels(0)
		, ScreenGeometry(_T(""))
		, TestPattern(_T(""))
		, ChannelHFOV(0)
		, ChannelVFOV(0)
		, ChannelPosX(0)
		, ChannelPosY(0)
		, ChannelDistance(0)
		, ChannelIP(_T("TEST TEST"))
		, ChannelResolutionX(0)
		, ChannelResolutionY(0)
		, ChannelSelect(0)
	{ }
	
	virtual ~MainDialog() {};
	// Dialog Data

	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) {
		CDialog::DoDataExchange(pDX); DDX_Text(pDX, IDC_SCREEN_HFOV, ScreenHFOV);
		DDX_Text(pDX, IDC_VIEWER_DISTANCE, ViewerDistance);
		DDX_Text(pDX, IDC_SCREEN_VFOV, ScreenVFOV);
		DDX_Text(pDX, IDC_NUMBER_OF_CHANNELS, NumberOfChannels);
		DDX_CBString(pDX, IDC_SCREEN_GEOMETRY, ScreenGeometry);
		DDX_CBString(pDX, IDC_TEST_PATTERN, TestPattern);
		DDX_Text(pDX, IDC_CHANNEL_HFOV, ChannelHFOV);
		DDX_Text(pDX, IDC_CHANNEL_VFOV, ChannelVFOV);
		DDX_Text(pDX, IDC_CHANNEL_POSITION_X, ChannelPosX);
		DDX_Text(pDX, IDC_CHANNEL_POSITION_Y, ChannelPosY);
		DDX_Text(pDX, IDC_CHANNEL_DISTANCE, ChannelDistance);
		DDX_Text(pDX, IDC_CHANNEL_IP, ChannelIP);
		DDX_Text(pDX, IDC_CHANNEL_RESOLUTION_X, ChannelResolutionX);
		DDX_Text(pDX, IDC_CHANNEL_RESOLUTION_Y, ChannelResolutionY);
		DDX_CBIndex(pDX, IDC_CHANNEL_SELECT, ChannelSelect);
	}   // DDX/DDV support
	BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		return true;
	}
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	int ViewerDistance;
	int ScreenHFOV;
	int ScreenVFOV;
	int NumberOfChannels;
	CString ScreenGeometry;
	CString TestPattern;
	int ChannelHFOV;
	int ChannelVFOV;
	int ChannelPosX;
	int ChannelPosY;
	int ChannelDistance;
	CString ChannelIP;
	int ChannelResolutionX;
	int ChannelResolutionY;
	afx_msg void OnEnChangeChannelHfov();
	int ChannelSelect;
	afx_msg void OnEnChangeNumberOfChannels();
	afx_msg void OnCbnSelchangeChannelSelect();
	void setScreenGui();
	void setChannelGui(int sel);
	void resetChannels();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonEditTest();
	afx_msg void OnCbnSelchangeTestPattern();
	afx_msg void OnEnChangeViewerDistance();
	afx_msg void OnEnChangeScreenHfov();
	afx_msg void OnEnChangeScreenVfov();
	afx_msg void OnEnChangeChannelVfov();
	afx_msg void OnEnChangeChannelPositionX();
	afx_msg void OnEnChangeChannelPositionY();
	afx_msg void OnEnChangeChannelDistance();
	afx_msg void OnEnChangeChannelIp();
	afx_msg void OnEnChangeChannelResolutionX();
	afx_msg void OnEnChangeChannelResolutionY();
	int channelIndex;
	int testPatternIndex;
	afx_msg void OnBnClickedButtonRun();
};

BEGIN_MESSAGE_MAP(MainDialog, CDialog)
	ON_COMMAND(ID_FILE_NEW, &MainDialog::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &MainDialog::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &MainDialog::OnFileSave)
	ON_EN_CHANGE(IDC_CHANNEL_HFOV, &MainDialog::OnEnChangeChannelHfov)
	ON_EN_CHANGE(IDC_NUMBER_OF_CHANNELS, &MainDialog::OnEnChangeNumberOfChannels)
	ON_CBN_SELCHANGE(IDC_CHANNEL_SELECT, &MainDialog::OnCbnSelchangeChannelSelect)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &MainDialog::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TEST, &MainDialog::OnBnClickedButtonEditTest)
	ON_CBN_SELCHANGE(IDC_TEST_PATTERN, &MainDialog::OnCbnSelchangeTestPattern)
	ON_EN_CHANGE(IDC_VIEWER_DISTANCE, &MainDialog::OnEnChangeViewerDistance)
	ON_EN_CHANGE(IDC_SCREEN_HFOV, &MainDialog::OnEnChangeScreenHfov)
	ON_EN_CHANGE(IDC_SCREEN_VFOV, &MainDialog::OnEnChangeScreenVfov)
	ON_EN_CHANGE(IDC_CHANNEL_VFOV, &MainDialog::OnEnChangeChannelVfov)
	ON_EN_CHANGE(IDC_CHANNEL_POSITION_X, &MainDialog::OnEnChangeChannelPositionX)
	ON_EN_CHANGE(IDC_CHANNEL_POSITION_Y, &MainDialog::OnEnChangeChannelPositionY)
	ON_EN_CHANGE(IDC_CHANNEL_DISTANCE, &MainDialog::OnEnChangeChannelDistance)
	ON_EN_CHANGE(IDC_CHANNEL_IP, &MainDialog::OnEnChangeChannelIp)
	ON_EN_CHANGE(IDC_CHANNEL_RESOLUTION_X, &MainDialog::OnEnChangeChannelResolutionX)
	ON_EN_CHANGE(IDC_CHANNEL_RESOLUTION_Y, &MainDialog::OnEnChangeChannelResolutionY)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &MainDialog::OnBnClickedButtonRun)
END_MESSAGE_MAP()

class MyApp : public CWinApp
{
	//MainDialog *wnd;
public:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	BOOL InitInstance()
	{
		CWinApp::InitInstance();
		MainDialog dlg;
		m_pMainWnd = &dlg;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		myConfig = new Configuration();
		INT_PTR nResponce = dlg.DoModal();
		return TRUE;
	}
};

MyApp theApp; 
MainDialog theDlg;

void MainDialog::OnFileNew()
{
	myConfig = new Configuration();
	myConfig->set_num_channels(1);
	ChannelConfig temp;
	myConfig->get_channels()->push_back(temp);
	NumberOfChannels = 1;

	resetChannels();
	setScreenGui();
	setChannelGui(0);	
}


void MainDialog::OnFileOpen()
{
	CFileDialog openDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("txt Files(*.txt)|*.txt||"), this);
	if (openDlg.DoModal() == IDOK) {
		inFile.open(openDlg.GetPathName(), std::ios::in);
		myConfig = new Configuration(inFile);
		inFile.close();

		NumberOfChannels = myConfig->get_num_channels();
		resetChannels();
		setScreenGui();
	}
}

void MainDialog::OnFileSave()
{
	if (myConfig == NULL) {
		MessageBox(_T("No Configuration to save"));
		return;
	}
	CFileDialog saveDlg(FALSE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("txt Files(*.txt)|*.txt||"), this);
	if (saveDlg.DoModal() == IDOK) {
		outFile.open(saveDlg.GetPathName(), std::ios::out);
		myConfig->output_config_file(outFile);
		outFile.close();
	}
}


void MainDialog::OnEnChangeNumberOfChannels()
{
	int oldNumber = NumberOfChannels;
	CString str;

	UpdateData(true);

	resetChannels();
	
	if (oldNumber == 0) {
		for (int i = 0; i < NumberOfChannels; i++) {
			ChannelConfig *channel = new ChannelConfig();
			myConfig->get_channels()->push_back(*channel);
		}
	}
	else if (oldNumber > NumberOfChannels) {
		for (int i = myConfig->get_num_channels(); i < NumberOfChannels; i++) {
			ChannelConfig *channel = new ChannelConfig();
			myConfig->get_channels()->push_back(*channel);
		}
	}
	else {
		myConfig->get_channels()->resize(NumberOfChannels);
	}

	//setChannelGui(oldNumber);	//NEW		Still displaying old numbers if reducing the number of channels down!
	myConfig->set_num_channels(NumberOfChannels);	
	UpdateData(false);
}


void MainDialog::OnCbnSelchangeChannelSelect()
{
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_CHANNEL_SELECT);
	channelIndex = m_pComboBox->GetCurSel();

	setChannelGui(channelIndex);
}


void MainDialog::setScreenGui()
{
	UpdateData(true);
	ViewerDistance = myConfig->get_viewer_distance();
	ScreenHFOV = myConfig->get_viewer_distance();
	ScreenVFOV = myConfig->get_total_fov_v();
	NumberOfChannels = myConfig->get_num_channels();	

	UpdateData(false);
}


void MainDialog::setChannelGui(int sel)	
{
	UpdateData(true);

	ChannelHFOV = myConfig->get_channels()->at(sel).get_fov_h();
	ChannelVFOV = myConfig->get_channels()->at(sel).get_fov_v();
	ChannelPosX = myConfig->get_channels()->at(sel).get_location_h();
	ChannelPosY = myConfig->get_channels()->at(sel).get_location_v();
	ChannelDistance = 0;		//Still needs to be added to config file?
	ChannelIP = _T("0.0.0");		//Still needs to be added to config file?
	ChannelResolutionX = myConfig->get_channels()->at(sel).get_resolution_h();
	ChannelResolutionY = myConfig->get_channels()->at(sel).get_resolution_v();

	UpdateData(false);
}


void MainDialog::resetChannels()
{
	CString str;
	
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_CHANNEL_SELECT);
	m_pComboBox->ResetContent();

	for (int i = 1; i <= NumberOfChannels; i++)
	{
		str.Format(_T("%d"), i);
		m_pComboBox->AddString(str);
	}
}


void MainDialog::OnBnClickedButtonPreview()
{
	//FILL WITH PREVIEW WINDOW
}


void MainDialog::OnBnClickedButtonRun()
{
	//Fill with running networking
}


void MainDialog::OnBnClickedButtonEditTest()
{
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_TEST_PATTERN);
	testPatternIndex = m_pComboBox->GetCurSel();

	AFS dlg0;
	ResolutionPattern dlg1;
	ColorBars dlg2;
	FullWhite dlg3;
	Grayscale dlg4;

	switch (testPatternIndex)
	{
	case 0:
		if (dlg0.DoModal() == IDOK)
		{

		}
		break;
	case 1:
		if (dlg1.DoModal() == IDOK)
		{

		}
		break;
	case 2:
		if (dlg2.DoModal() == IDOK)
		{

		}
		break;
	case 3:
		if (dlg3.DoModal() == IDOK)
		{

		}
		break;
	case 4:
		if (dlg4.DoModal() == IDOK)
		{

		}
		break;
	default:
		MessageBox(_T("There is nothing to edit with this test pattern."));
		break;
	}
}


void MainDialog::OnCbnSelchangeTestPattern()
{
	//Test pattern drop down box
}


void MainDialog::OnEnChangeViewerDistance()
{
	UpdateData(true);
	myConfig->set_viewer_distance(ViewerDistance);
	UpdateData(false);
}


void MainDialog::OnEnChangeScreenHfov()
{
	UpdateData(true);
	myConfig->set_total_fov_h(ScreenHFOV);
	UpdateData(false);
}


void MainDialog::OnEnChangeScreenVfov()
{
	UpdateData(true);
	myConfig->set_total_fov_v(ScreenVFOV);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelHfov()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_fov_h(ChannelHFOV);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelVfov()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_fov_v(ChannelVFOV);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelPositionX()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_location_h(ChannelPosX);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelPositionY()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_location_v(ChannelPosY);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelDistance()
{
	//NOT SETUP IN CONFIG
	UpdateData(true);
	//myConfig->get_channels()->at(channelIndex).
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelIp()
{
	//NOT SETUP IN CONFIG
	UpdateData(true);
	//myConfig->get_channels()->at(channelIndex).
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelResolutionX()
{
	//NOT SETUP IN CONFIG
	UpdateData(true);
	//myConfig->get_channels()->at(channelIndex).
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelResolutionY()
{
	//NOT SETUP IN CONFIG
	UpdateData(true);
	//myConfig->get_channels()->at(channelIndex).
	UpdateData(false);
}


