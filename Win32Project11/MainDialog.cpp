#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include <winsock2.h>
#include <ws2tcpip.h>
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
#include "DisplayFrame.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define MAX_FILE_SIZE 1000

Configuration *myConfig;

class MainDialog : public CDialog
{

public:
	CMenu MainMenu;
	std::ofstream outFile;
	std::ifstream inFile;
	DisplayFrame* frm;

	bool MainDialog::senddata(SOCKET sock, void *buf, int buflen);
	bool MainDialog::sendlong(SOCKET sock, long value);
	bool MainDialog::sendfile(SOCKET sock, FILE *f);
	
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
	int opacityIndex;
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnFileSaveas();
	afx_msg void OnCbnSelchangeFullWhiteOpacity();
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
	ON_COMMAND(ID_FILE_SAVEAS, &MainDialog::OnFileSaveas)
	ON_CBN_SELCHANGE(IDC_FULL_WHITE_OPACITY, &MainDialog::OnCbnSelchangeFullWhiteOpacity)
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

void MainDialog::OnFileSaveas()
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
	ScreenHFOV = myConfig->get_total_fov_h();
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
	frm = new DisplayFrame (myConfig, 0);
	frm->ShowWindow(SW_SHOW);
	frm->UpdateWindow();
}


void MainDialog::OnBnClickedButtonRun()
{
	//OnFileSave();

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	struct addrinfo *result = NULL,
		*ptr = NULL,
		addr;

	ZeroMemory(&addr, sizeof(addr));
	addr.ai_family = AF_UNSPEC;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;


	// Resolve the server address and port
	getaddrinfo("127.0.0.1", DEFAULT_PORT, &addr, &result);

	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to channel
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	// Connect to server.
	int check = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (check == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		MessageBox(_T("Unable to connect to server!"));
		WSACleanup();
		return;
	}

	FILE *filehandle = fopen("testChannel.txt", "rb");
	if (filehandle != NULL)
	{
		sendfile(ConnectSocket, filehandle);
		fclose(filehandle);
	}


	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

}


void MainDialog::OnBnClickedButtonEditTest()
{
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_TEST_PATTERN);
	testPatternIndex = m_pComboBox->GetCurSel();

	/*CComboBox *m_pComboBox2 = (CComboBox *)GetDlgItem(IDC_FULL_WHITE_OPACITY);
	int opacityIndex = m_pComboBox2->GetCurSel();*/

	AFS dlg0;
	ResolutionPattern dlg1;
	ColorBars dlg2;
	FullWhite dlg3;
	Grayscale dlg4;

	/*CComboBox *m_pComboBox2 = (CComboBox *)dlg3.GetDlgItem(IDC_FULL_WHITE_OPACITY);
	opacityIndex = m_pComboBox2->GetCurSel();*/
	
	bool tempBool;
	

	switch (testPatternIndex)
	{
	case 8:
		dlg0.AFSazimuth = myConfig->get_azimuth();
		dlg0.AFSelevation = myConfig->get_elevation();
		dlg0.AFSrange = myConfig->get_range();
		if (dlg0.DoModal() == IDOK)
		{
			myConfig->set_azimuth(dlg0.AFSazimuth);
			myConfig->set_elevation(dlg0.AFSelevation);
			myConfig->set_range(dlg0.AFSrange);
		}
		break;
	case 4:
		dlg1.ResolutionAzimuth = myConfig->get_azimuth();
		dlg1.ResolutionElevation = myConfig->get_elevation();
		dlg1.ResolutionRange = myConfig->get_range();
		if (dlg1.DoModal() == IDOK)
		{
			myConfig->set_azimuth(dlg1.ResolutionAzimuth);
			myConfig->set_elevation(dlg1.ResolutionElevation);
			myConfig->set_range(dlg1.ResolutionRange);
		}
		break;
	case 2:
		tempBool = myConfig->get_display_horizontal();
		if (tempBool == true)
		{
			dlg2.ColorBarsHorizontal = true;
			dlg2.ColorBarsVertical = false;
		}
		else
		{
			dlg2.ColorBarsHorizontal = false;
			dlg2.ColorBarsVertical = true;
		}
		if (dlg2.DoModal() == IDOK)
		{
			myConfig->set_display_horizontal(dlg2.ColorBarsHorizontal);
		}
		break;
	case 5:
		
		if (dlg3.DoModal() == IDOK)
		{
			myConfig->set_opacity(opacityIndex);
		}
		break;
	case 0:
		tempBool = myConfig->get_display_horizontal();
		if (tempBool == true)
		{
			dlg4.GrayscaleHorizontal = true;
			dlg4.GrayscaleVertical = false;
		}
		else
		{
			dlg4.GrayscaleHorizontal = false;
			dlg4.GrayscaleVertical = true;
		}
		if (myConfig->get_full_pattern() == true)
			dlg4.GrayscaleFullPattern = true;
		else
			dlg4.GrayscaleFullPattern = false;
		if (dlg4.DoModal() == IDOK)
		{
			myConfig->set_display_horizontal(dlg4.GrayscaleHorizontal);
			myConfig->set_full_pattern(dlg4.GrayscaleFullPattern);
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
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_resolution_h(ChannelResolutionX);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelResolutionY()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_resolution_v(ChannelResolutionY);
	UpdateData(false);
}

bool MainDialog::senddata(SOCKET sock, void *buf, int buflen)
{
	char *pbuf = (char *)buf;

	while (buflen > 0)
	{
		int num = send(sock, pbuf, buflen, 0);
		if (num == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				// optional: use select() to check for timeout to fail the send
				continue;
			}
			return false;
		}

		pbuf += num;
		buflen -= num;
	}

	return true;
}

bool MainDialog::sendlong(SOCKET sock, long value)
{
	value = htonl(value);
	return senddata(sock, &value, sizeof(value));
}

bool MainDialog::sendfile(SOCKET sock, FILE *f)
{
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	rewind(f);
	if (filesize == EOF)
		return false;
	if (!sendlong(sock, filesize))
		return false;
	if (filesize > 0)
	{
		char buffer[1024];
		do
		{
			size_t num = min(filesize, sizeof(buffer));
			num = fread(buffer, 1, num, f);
			if (num < 1)
				return false;
			if (!senddata(sock, buffer, num))
				return false;
			filesize -= num;
		} while (filesize > 0);
	}
	return true;
}

void MainDialog::OnCbnSelchangeFullWhiteOpacity()
{
	FullWhite dlg;
	CComboBox *m_pComboBox = (CComboBox *)dlg.GetDlgItem(IDC_FULL_WHITE_OPACITY);
	opacityIndex = m_pComboBox->GetCurSel();
	//m_pComboBox->SetCurSel(myConfig->get_opacity());
}
