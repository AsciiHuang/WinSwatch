// WinSwatch.cpp : 定義應用程式的類別行為。
//

#include "stdafx.h"
#include "WinSwatch.h"
#include "WinSwatchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSwatchApp

BEGIN_MESSAGE_MAP(CWinSwatchApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWinSwatchApp 建構

CWinSwatchApp::CWinSwatchApp()
{
	// TODO: 在此加入建構程式碼，
	// 將所有重要的初始設定加入 InitInstance 中
}


// 僅有的一個 CWinSwatchApp 物件

CWinSwatchApp theApp;


// CWinSwatchApp 初始設定

BOOL CWinSwatchApp::InitInstance()
{
	CWinApp::InitInstance();

	// 標準初始設定
	// 如果您不使用這些功能並且想減少
	// 最後完成的可執行檔大小，您可以
	// 從下列程式碼移除不需要的初始化常式，
	// 變更儲存設定值的登錄機碼
	// TODO: 您應該適度修改此字串
	// (例如，公司名稱或組織名稱)
	SetRegistryKey(_T("本機 AppWizard 所產生的應用程式"));

	CWinSwatchDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置於使用 [確定] 來停止使用對話方塊時
		// 處理的程式碼
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置於使用 [取消] 來停止使用對話方塊時
		// 處理的程式碼
	}

	// 因為已經關閉對話方塊，傳回 FALSE，所以我們會結束應用程式，
	// 而非提示開始應用程式的訊息。
	return FALSE;
}
