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
#include "ChannelConfig.h"
#include "ResolutionPattern.h"
#include "AFS.h"
#include "Grayscale.h"
#include "ColorBars.h"
#include "FullWhite.h"

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

	vector<SOCKET> sockets;


	//Functions for sending coknfiguration file
	bool MainDialog::senddata(SOCKET sock, void *buf, int buflen);
	bool MainDialog::sendlong(SOCKET sock, long value);
	bool MainDialog::sendfile(SOCKET sock, FILE *f);

	void OnPaint();
	void DrawPreview(CPaintDC &dc);
	bool paint = false;
	bool runOnce = false;

	MainDialog(CWnd* pParent = NULL): CDialog(MainDialog::IDD, pParent)
		, ViewerDistance(_T("0"))
		, ScreenHFOV(_T("0"))
		, ScreenVFOV(_T("0"))
		, NumberOfChannels(_T("0"))
		, ScreenGeometry(_T("Flat"))
		, TestPattern(_T(""))
		, ChannelHFOV(_T("0"))
		, ChannelVFOV(_T("0"))
		, ChannelPosX(_T("0"))
		, ChannelPosY(_T("0"))
		, ChannelDistance(_T("0"))
		, ChannelIP(_T("0.0.0"))
		, ChannelResolutionX(_T("0"))
		, ChannelResolutionY(_T("0"))
		, ChannelSelect()
	{ }
	
	virtual ~MainDialog() {};
	// Dialog Data

	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) {
		CDialog::DoDataExchange(pDX); 
		DDX_Text(pDX, IDC_SCREEN_HFOV, ScreenHFOV);
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
	CString ViewerDistance;
	CString ScreenHFOV;
	CString ScreenVFOV;
	CString NumberOfChannels;
	CString ScreenGeometry;
	CString TestPattern;
	CString ChannelHFOV;
	CString ChannelVFOV;
	CString ChannelPosX;
	CString ChannelPosY;
	CString ChannelDistance;
	CString ChannelIP;
	CString ChannelResolutionX;
	CString ChannelResolutionY;
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
	ON_WM_PAINT()
END_MESSAGE_MAP()

class MyApp : public CWinApp
{
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
		ChannelConfig temp;
		myConfig->get_channels()->push_back(temp);
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
	NumberOfChannels = _T("1"); 

	CComboBox* m_pComboBox = (CComboBox*)GetDlgItem(IDC_TEST_PATTERN);
	m_pComboBox->SetCurSel(myConfig->get_test_pattern());

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

		CT2CA pszConvertedAnsiString(openDlg.GetPathName());
		string str(pszConvertedAnsiString);
		myConfig->set_name(str);

		inFile.close();
		NumberOfChannels.Format(_T("%d"), myConfig->get_num_channels());

		CComboBox* m_pComboBox = (CComboBox*)GetDlgItem(IDC_TEST_PATTERN);
		m_pComboBox->SetCurSel(myConfig->get_test_pattern());

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
		
		CT2CA pszConvertedAnsiString(saveDlg.GetPathName());
		string str(pszConvertedAnsiString);
		
		myConfig->set_name(str);
		outFile.open(str, std::ios::out);
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
	int oldNumber = _ttoi(NumberOfChannels);
	CString str;

	UpdateData(true);
	int newNumber = _ttoi(NumberOfChannels);
	resetChannels();
	
	if (oldNumber == 0) {
		for (int i = 0; i < newNumber; i++) {
			ChannelConfig *channel = new ChannelConfig();
			myConfig->get_channels()->push_back(*channel);
		}
	}
	else if (oldNumber > newNumber) {
		for (int i = myConfig->get_num_channels(); i < newNumber; i++) {
			ChannelConfig *channel = new ChannelConfig();
			myConfig->get_channels()->push_back(*channel);
		}
	}
	else {
		myConfig->get_channels()->resize(newNumber);
	}

	//setChannelGui(oldNumber);	//NEW		Still displaying old numbers if reducing the number of channels down!
	myConfig->set_num_channels(newNumber);	
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
	int temp;

	UpdateData(true);
	temp = myConfig->get_viewer_distance();
	ViewerDistance.Format(_T("%d"), temp);
	temp = myConfig->get_total_fov_h();
	ScreenHFOV.Format(_T("%d"), temp);
	temp = myConfig->get_total_fov_v();
	ScreenVFOV.Format(_T("%d"), temp);
	temp = myConfig->get_num_channels();
	NumberOfChannels.Format(_T("%d"), temp);

	UpdateData(false);
}


void MainDialog::setChannelGui(int sel)	
{
	UpdateData(true);

	ChannelHFOV.Format(_T("%d"), myConfig->get_channels()->at(sel).get_fov_h());
	ChannelVFOV.Format(_T("%d"), myConfig->get_channels()->at(sel).get_fov_v());
	ChannelPosX.Format(_T("%d"), myConfig->get_channels()->at(sel).get_location_h());
	ChannelPosY.Format(_T("%d"), myConfig->get_channels()->at(sel).get_location_v());
	ChannelDistance = _T("0");		//Still needs to be added to config file?
	ChannelResolutionX.Format(_T("%d"), myConfig->get_channels()->at(sel).get_resolution_h());
	ChannelResolutionY.Format(_T("%d"), myConfig->get_channels()->at(sel).get_resolution_v());

	CString temp;
	string temp2;
	temp2 = myConfig->get_channels()->at(sel).get_IPaddress();
	temp = temp2.c_str();
	ChannelIP = temp;

	UpdateData(false);
}


void MainDialog::resetChannels()
{
	CString str;
	
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_CHANNEL_SELECT);
	m_pComboBox->ResetContent();
	int numChannels = _ttoi(NumberOfChannels);
	for (int i = 1; i <= numChannels; i++)
	{
		str.Format(_T("%d"), i);
		m_pComboBox->AddString(str);
	}

	if (numChannels > 0)
	{
		m_pComboBox->SetCurSel(0);
		setChannelGui(0);
	}
}


void MainDialog::OnBnClickedButtonPreview()
{
	char sendbuf[10] = "stop";
	int buflength = 10;
	int numChannels = _ttoi(NumberOfChannels);
	
	for (int i = numChannels - 1; i > 0; i--) {
		
		//send stop message
		send(sockets.at(i), sendbuf, buflength, 0);

		// cleanup
		closesocket(sockets.at(i));
		sockets.pop_back();
	}

	WSACleanup();
}

void MainDialog::OnPaint() {
	CPaintDC dc(this);
	Graphics graphics(dc);

	if (paint) {

		this->DrawPreview(dc);
	}
}

void MainDialog::DrawPreview(CPaintDC &dc) {
	Graphics graphics(dc);

	Pen      pen(Color(255, 0, 0, 0));
	SolidBrush brush(Color(0, 100, 0, 0));
	Rect previewRect(15, 15, 400, 200);
	Region previewRegion(previewRect);

	graphics.FillRegion(&brush, &previewRegion);

	graphics.DrawRectangle(&pen, 30, 30, 800, 400);

}

void MainDialog::OnBnClickedButtonRun()
{
	float resx, resy, fovh, fovv;

	for (int i = 0; i < _ttoi(NumberOfChannels); i++) {
		resx = myConfig->get_channels()->at(i).get_resolution_h();
		resy = myConfig->get_channels()->at(i).get_resolution_v();
		fovh = myConfig->get_channels()->at(i).get_fov_h();
		fovv = myConfig->get_channels()->at(i).get_fov_v();
	
		if ((resx / resy) / (fovh / fovv) != 1 ) {
			MessageBox(_T("Channel resolution ratio does not match FOV ratio. May result in unexpected test patterns"));
			break;
		}
	}
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	struct addrinfo *result = NULL,
		*ptr = NULL,
		addr;

	ZeroMemory(&addr, sizeof(addr));
	addr.ai_family = AF_UNSPEC;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;
	int numChannels = _ttoi(NumberOfChannels);

	for (int i = 0; i < numChannels; i++) {
		//Resolve the server address and port
		string tmp = myConfig->get_channels()->at(i).get_IPaddress();
		const char* tmp2 = tmp.c_str();
		PCSTR tmp3 = (PCSTR)tmp2;

		getaddrinfo(tmp3, DEFAULT_PORT, &addr, &result);

		//delete ip;

		SOCKET ConnectSocket = INVALID_SOCKET;
		sockets.push_back(ConnectSocket);

		// Attempt to connect to the first address returned by
		// the call to getaddrinfo
		ptr = result;

		// Create a SOCKET for connecting to channel
		sockets.at(i) = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		// Connect to server.
		int check = connect(sockets.at(i), ptr->ai_addr, (int)ptr->ai_addrlen);
		if (check == SOCKET_ERROR) {
			closesocket(sockets.at(i));
			sockets.at(i) = INVALID_SOCKET;
		}

		freeaddrinfo(result);

		if (sockets.at(i) == INVALID_SOCKET) {
			MessageBox(_T("Unable to connect to server!"));
			WSACleanup();
			return;
		}
	}

	for (int i = 0; i < numChannels; i++) {
		ofstream out;
		out.open("temp.txt", std::ios::out);
		myConfig->output_config_file(out, i);
		out.close();

		FILE* filehandle = fopen("temp.txt", "rb");
		if (filehandle != NULL)
		{
			sendfile(sockets.at(i), filehandle);
			fclose(filehandle);
			remove("temp.txt");
		}
	}
}


void MainDialog::OnBnClickedButtonEditTest()
{
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_TEST_PATTERN);
	testPatternIndex = m_pComboBox->GetCurSel();
	
	/*CComboBox *m_pComboBox2 = (CComboBox *)GetDlgItem(IDC_FULL_WHITE_OPACITY);
	int opacityIndex = m_pComboBox2->GetCurSel();*/

	AFS dlg0;
	ResolutionPattern dlg1;
	ColorBars dlg2(NULL, myConfig);
	FullWhite dlg3(NULL, myConfig);
	Grayscale dlg4(NULL, myConfig);

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
	case 2: //Color Bars
		if (dlg2.DoModal() == IDOK)
		{
		}
		break;
	case 5:
		
		if (dlg3.DoModal() == IDOK)
		{
			myConfig->set_opacity(dlg3.input);
		}
		break;
	case 0:
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
	CComboBox *m_pComboBox = (CComboBox *)GetDlgItem(IDC_TEST_PATTERN);
	testPatternIndex = m_pComboBox->GetCurSel();
	myConfig->set_test_pattern(testPatternIndex);
}


void MainDialog::OnEnChangeViewerDistance()
{
	UpdateData(true);
	myConfig->set_viewer_distance(_ttoi(ViewerDistance));
	UpdateData(false);
}


void MainDialog::OnEnChangeScreenHfov()
{
	UpdateData(true);
	myConfig->set_total_fov_h(_ttoi(ScreenHFOV));
	UpdateData(false);
}


void MainDialog::OnEnChangeScreenVfov()
{
	UpdateData(true);
	myConfig->set_total_fov_v(_ttoi(ScreenVFOV));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelHfov()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_fov_h(_ttoi(ChannelHFOV));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelVfov()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_fov_v(_ttoi(ChannelVFOV));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelPositionX()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_location_h(_ttoi(ChannelPosX));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelPositionY()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_location_v(_ttoi(ChannelPosY));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelDistance()
{

	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_distance_to_screen(_ttoi(ChannelDistance));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelIp()
{
	UpdateData(true);
	CT2CA pszConvertedAnsiString(ChannelIP);
	string strStd(pszConvertedAnsiString);
	myConfig->get_channels()->at(channelIndex).set_IPaddress(strStd);
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelResolutionX()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_resolution_h(_ttoi(ChannelResolutionX));
	UpdateData(false);
}


void MainDialog::OnEnChangeChannelResolutionY()
{
	UpdateData(true);
	myConfig->get_channels()->at(channelIndex).set_resolution_v(_ttoi(ChannelResolutionY));
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
