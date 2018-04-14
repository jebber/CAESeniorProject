#include "stdafx.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include "Configuration.h"
#include "Generator.h"
#include "ChannelConfig.h"

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
		, NumberOfChannels(5)
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
	afx_msg void OnBnClickedButtonApply();
};

BEGIN_MESSAGE_MAP(MainDialog, CDialog)
	ON_COMMAND(ID_FILE_NEW, &MainDialog::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &MainDialog::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &MainDialog::OnFileSave)
	ON_EN_CHANGE(IDC_CHANNEL_HFOV, &MainDialog::OnEnChangeChannelHfov)
	ON_EN_CHANGE(IDC_NUMBER_OF_CHANNELS, &MainDialog::OnEnChangeNumberOfChannels)
	ON_CBN_SELCHANGE(IDC_CHANNEL_SELECT, &MainDialog::OnCbnSelchangeChannelSelect)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &MainDialog::OnBnClickedButtonApply)
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
		//ScreenHFOV = 10;
		INT_PTR nResponce = dlg.DoModal();
		return TRUE;
	}
};

MyApp theApp; 
MainDialog theDlg;

void MainDialog::OnFileNew()
{
	myConfig = new Configuration();
	setScreenGui();
	//setChannelGui(0);			//Does creating a new config file intialize a channel? No?
}


void MainDialog::OnFileOpen()
{
	CFileDialog openDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("txt Files(*.txt)|*.txt||"), this);
	if (openDlg.DoModal() == IDOK) {
		inFile.open(openDlg.GetPathName(), std::ios::in);
		myConfig = new Configuration(inFile);
		inFile.close();
		setScreenGui();
		setChannelGui(0);		//Does creating a new config file intialize a channel? No?
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


void MainDialog::OnEnChangeChannelHfov()
{
	UpdateData(true);
	ScreenHFOV = ChannelHFOV;
	UpdateData(false);

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void MainDialog::OnEnChangeNumberOfChannels()
{
	/*
	UpdateData(true);
	for (int i = 0; i < NumberOfChannels; i++)
	{


	}


	UpdateData(false);	*/
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void MainDialog::OnCbnSelchangeChannelSelect()
{
	/*
	UpdateData(true);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_CHANNEL_SELECT);
	CString str;
	for (int i = 0; i < NumberOfChannels; i++)
	{
		str.Format(L"%d", i);
		pCombo->AddString(str);

	}

	pCombo->AddString(_T("TESTER"));
	UpdateData(false);
	// TODO: Add your control notification handler code here

	for (int i = 0; i < NumberOfChannels; i++)
	{


	}		*/
	setChannelGui(ChannelSelect);
}


void MainDialog::setScreenGui()
{
	UpdateData(true);
	ViewerDistance = myConfig->get_viewer_distance();
	ScreenHFOV = myConfig->get_viewer_distance();
	ScreenVFOV = myConfig->get_total_fov_v();
	//NumberOfChannels =			//Still needs to be added to config file?

	UpdateData(false);
}

void MainDialog::setChannelGui(int sel)	//Um, start at 0 or 1?
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


void MainDialog::OnBnClickedButtonApply()
{
	//setScreenGui();
}
