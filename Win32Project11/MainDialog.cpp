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
	
	MainDialog(CWnd* pParent = NULL): CDialog(MainDialog::IDD, pParent) { }
	
	virtual ~MainDialog() {};
	// Dialog Data

	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }   // DDX/DDV support
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
};

BEGIN_MESSAGE_MAP(MainDialog, CDialog)
	ON_COMMAND(ID_FILE_NEW, &MainDialog::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &MainDialog::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &MainDialog::OnFileSave)
END_MESSAGE_MAP()

class MyApp : public CWinApp
{
	MainDialog *wnd;
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

void MainDialog::OnFileNew()
{
	myConfig = new Configuration();						//Clean up!
}


void MainDialog::OnFileOpen()
{
	CFileDialog openDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("txt Files(*.txt)|*.txt||"), this);
	if (openDlg.DoModal() == IDOK) {
		inFile.open(openDlg.GetPathName(), std::ios::in);
		myConfig = new Configuration(inFile);
		inFile.close();
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