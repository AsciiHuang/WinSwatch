// WinSwatchDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "WinSwatch.h"
#include "WinSwatchDlg.h"

#define TIMER_GETCOLOR_ID (4096)
#define TIMER_GETCOLOR_TIME (100)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSwatchDlg 對話方塊


CWinSwatchDlg::CWinSwatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinSwatchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_unMode = WS_MD_SCREEN;
	//m_dwR =  m_dwG = m_dwB = cr = crLast = 0;
	cr = crLast = 0;
	m_bSelectColor = false;
}

void CWinSwatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinSwatchDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SCREENMODE, &CWinSwatchDlg::OnBnClickedBtnScreenmode)
	ON_BN_CLICKED(IDC_BTN_SWATCHMODE, &CWinSwatchDlg::OnBnClickedBtnSwatchmode)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CWinSwatchDlg::OnBnClickedBtnAbout)
END_MESSAGE_MAP()


// CWinSwatchDlg 訊息處理常式

BOOL CWinSwatchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	LoadParam();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CWinSwatchDlg::LoadParam()
{
	// enum {WS_RC_CLIENT, WS_RC_TITLE, WS_RC_SCMODE, WS_RC_SWMODE, WS_RC_EXIT, WS_RC_COUNT};
	m_rc[WS_RC_CLIENT].SetRect(0, 0, 204, 262); // 視窗範圍
	m_rc[WS_RC_TITLE].SetRect(5, 5, 140, 17); // 標題
	m_rc[WS_RC_SWATCHBOARD].SetRect(6, 22, 198, 214); // RGB 色板
	m_rc[WS_RC_GRAND_VIEW].SetRect(6, 220, 198, 230); // 漸層畫框
	m_rc[WS_RC_ABOUT].SetRect(141, 4, 154, 17); // 關於 WinSwatch 按鍵
	m_rc[WS_RC_SCMODE].SetRect(156, 4, 169, 17); // 螢幕模式按鍵
	m_rc[WS_RC_SWMODE].SetRect(171, 4, 184, 17); // 調色盤模式按鍵
	m_rc[WS_RC_EXIT].SetRect(186, 4, 199, 17); // 離開按鍵
	m_rc[WS_RC_COLOR].SetRect(6, 236, 42, 256); // 顯示框
	m_rc[WS_RC_INFO].SetRect(50, 239, 196, 253); // 資訊框

	// Init DC, bmp
	CDC* pDC = GetDC();
	dcMem.CreateCompatibleDC(NULL);
	bmp.CreateCompatibleBitmap(pDC, m_rc[WS_RC_CLIENT].Width(), m_rc[WS_RC_CLIENT].Height());
	dcMem.SelectObject(&bmp);
	dcMem.SetBkMode(TRANSPARENT);
	ReleaseDC(pDC);
	
	// 圖片
	// enum {WS_IMG_CLIENT, WS_IMG_COUNT};
	//UINT unImg[] = {IDR_PNG_BACKGROUND};
	//for(int iIndex = WS_IMG_CLIENT; iIndex < WS_IMG_COUNT; iIndex ++)
	//{
	//	m_img[iIndex].LoadResource(FindResource(NULL, MAKEINTRESOURCE(unImg[iIndex]), _T("PNG")), CXIMAGE_FORMAT_PNG);
	//}
	m_bmpBackGround.LoadBitmap(IDB_BG_MAIN);

	m_btn[WS_BTN_ABOUT].Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, m_rc[WS_RC_ABOUT], this, IDC_BTN_ABOUT);
	m_btn[WS_BTN_SCMODE].Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, m_rc[WS_RC_SCMODE], this, IDC_BTN_SCREENMODE);
	m_btn[WS_BTN_SWMODE].Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, m_rc[WS_RC_SWMODE], this, IDC_BTN_SWATCHMODE);
	m_btn[WS_BTN_EXIT].Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, m_rc[WS_RC_EXIT], this, IDOK);

	m_btn[WS_BTN_ABOUT].LoadBitmaps(IDB_BTN_ABOUT, IDB_BTN_ABOUT, IDB_BTN_ABOUT, IDB_BTN_ABOUT);
	m_btn[WS_BTN_SCMODE].LoadBitmaps(IDB_BTN_SCMODE, IDB_BTN_SCMODE, IDB_BTN_SCMODE, IDB_BTN_SCMODE);
	m_btn[WS_BTN_SWMODE].LoadBitmaps(IDB_BTN_SWMODE, IDB_BTN_SWMODE, IDB_BTN_SWMODE, IDB_BTN_SWMODE);
	m_btn[WS_BTN_EXIT].LoadBitmaps(IDB_BTN_EXIT, IDB_BTN_EXIT, IDB_BTN_EXIT, IDB_BTN_EXIT);

	SetWindowPos(&(this->wndTopMost), 0, 0, m_rc[WS_RC_CLIENT].Width(), m_rc[WS_RC_CLIENT].Height(), SWP_NOMOVE);
	//ModifyStyleEx(NULL, WS_EX_TOPMOST);
	SetWindowTextW(_T("WinSwatch"));

	// Init Font
	m_logfontSet.lfHeight = 12;
	m_logfontSet.lfWidth = 0;
	m_logfontSet.lfEscapement = 0;
	m_logfontSet.lfOrientation = 0;
	m_logfontSet.lfWeight = FW_BLACK;
	m_logfontSet.lfItalic = 0;
	m_logfontSet.lfUnderline = 0;
	m_logfontSet.lfStrikeOut = 0;
	m_logfontSet.lfCharSet = DEFAULT_CHARSET;
	m_logfontSet.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logfontSet.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logfontSet.lfQuality = DEFAULT_QUALITY;
	m_logfontSet.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy(m_logfontSet.lfFaceName, _T("Arial")); // 標楷體
	m_fontSetTitle.CreateFontIndirect(&m_logfontSet);

	m_logfontSet.lfHeight = 14;
	m_fontSetColor.CreateFontIndirect(&m_logfontSet);
	
	SetTimer(TIMER_GETCOLOR_ID, TIMER_GETCOLOR_TIME, NULL);
}

void CWinSwatchDlg::OnPaint()
{
	CPaintDC dc(this); // 繪製的裝置內容
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// Draw Background
		CDC dcClient;
		dcClient.CreateCompatibleDC(NULL);
		dcClient.SelectObject(&m_bmpBackGround);

		// DrawContent
		dcMem.BitBlt(0, 0, m_rc[WS_RC_CLIENT].Width(), m_rc[WS_RC_CLIENT].Height(), &dcClient, 0, 0, SRCCOPY);
		dcMem.SelectObject(&m_fontSetTitle);
		dcMem.SetTextColor(RGB(255, 255, 255));
		switch(m_unMode)
		{
			case WS_MD_SCREEN:
				dcMem.DrawText(_T("WinSwatch-Screen Mode"), m_rc[WS_RC_TITLE], DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
				DrawGradient(&dcMem, m_rc[WS_RC_GRAND_VIEW], cr, RGB(0, 0, 0), false);
				break;
			case WS_MD_SWATCH:
				dcMem.DrawText(_T("WinSwatch-Swatch Mode"), m_rc[WS_RC_TITLE], DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
				DrawGradient(&dcMem, m_rc[WS_RC_GRAND_VIEW], crSelect, RGB(0, 0, 0), false);
				break;
		}
		dcMem.SetTextColor(RGB(60, 60, 60));
		dcMem.FillSolidRect(m_rc[WS_RC_COLOR], cr);
		dcMem.SelectObject(&m_fontSetColor);
		dcMem.DrawText(m_strColorInfo, m_rc[WS_RC_INFO], DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
		dc.BitBlt(0, 0, m_rc[WS_RC_CLIENT].Width(), m_rc[WS_RC_CLIENT].Height(), &dcMem, 0, 0, SRCCOPY);
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CWinSwatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWinSwatchDlg::OnBnClickedBtnScreenmode()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_unMode = WS_MD_SCREEN;
	InvalidateRect(&m_rc[WS_RC_TITLE], FALSE);
	UpdateWindow();
}

void CWinSwatchDlg::OnBnClickedBtnSwatchmode()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_unMode = WS_MD_SWATCH;
	InvalidateRect(&m_rc[WS_RC_TITLE], FALSE);
	UpdateWindow();
}

void CWinSwatchDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼

	CRgn rgn;
	RECT rc[1+5] = 
	{
	  {0, 0, cx, cy}, /* 全部視窗區域 */
	  {0, 3, 1, cy - 3}, /* 左側第一行 */
	  {1, 1, 3, cy - 1}, /* 左側第二行 */
	  {3, 0, cx - 3, cy}, /* 中間區域 */
	  {cx - 3, 1, cx - 1, cy - 1}, /* 右側第二行 */
	  {cx - 1, 3, cx, cy - 3}, /* 右側第一行 */
	};
	CreateRgn(rgn, rc[0], 7, rc+1);
	SetWindowRgn((HRGN)rgn, TRUE);
	rgn.DeleteObject();

	Invalidate(); // 強制重繪
}

BOOL CWinSwatchDlg::CreateRgn(CRgn& rgn, RECT& rcBound, int nRectCount, RECT* paRect)
{
	//rgn must be a clean CRgn
	ASSERT(nRectCount>0);
	RGNDATA* p = (RGNDATA*)malloc(sizeof(RGNDATAHEADER) + sizeof(RECT) * nRectCount);
	p->rdh.dwSize = sizeof(RGNDATAHEADER);
	p->rdh.iType = RDH_RECTANGLES;
	p->rdh.nCount = nRectCount;
	p->rdh.rcBound = rcBound;
	p->rdh.nRgnSize = 0;
	memcpy(p->Buffer, paRect, sizeof(RECT) * nRectCount);
	BOOL bResult = rgn.CreateFromData(NULL, sizeof(RGNDATAHEADER) + sizeof(RECT) * nRectCount, p);
	free(p);
	return bResult;
}
LRESULT CWinSwatchDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if(WM_NCHITTEST == message)
	{
		//CPoint pt;
		//CRect rcTemp(m_rc[WS_RC_CLIENT]);
		//GetCursorPos(&pt);
		//ScreenToClient(&pt);
		//rcTemp.DeflateRect(m_rc[WS_RC_CLIENT].Width() - 16,
		//				   m_rc[WS_RC_CLIENT].Height() - 16, 0, 0);
		//return rcTemp.PtInRect(pt) ? HTBOTTOMRIGHT : HTCAPTION;
		
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		CRect rcTemp(0, 0, m_rc[WS_RC_CLIENT].right, 20);
		if(rcTemp.PtInRect(pt))
		{
			return HTCAPTION;
		}
	}
	else if(WM_DISPLAYCHANGE == message)
	{
		//DeleteDC (hdcScreen);
		//hdcScreen = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CWinSwatchDlg::GetColor()
{
	POINT pt;
	
	::DeleteDC(hdcScreen);
	hdcScreen = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

	::GetCursorPos(&pt);
	cr = GetPixel(hdcScreen, pt.x, pt.y);

	if (cr != crLast)
	{
		crLast = cr;
		//m_dwR = GetRValue(cr);
		//m_dwG = GetGValue(cr);
		//m_dwB = GetBValue(cr);
		m_strColorInfo.Format(_T("#%02x%02x%02x  r=%03d g=%03d b=%03d"), GetRValue(cr), GetGValue(cr), GetBValue(cr), GetRValue(cr), GetGValue(cr), GetBValue(cr));
		InvalidateRect(CRect(m_rc[WS_RC_COLOR].left, m_rc[WS_RC_GRAND_VIEW].top, m_rc[WS_RC_GRAND_VIEW].right, m_rc[WS_RC_COLOR].bottom), FALSE);
	}
}

void CWinSwatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(TIMER_GETCOLOR_ID == nIDEvent)
	{
		switch(m_unMode)
		{
			case WS_MD_SCREEN:
				GetColor();
				break;
			case WS_MD_SWATCH:
				if(m_bSelectColor)
				{
					CPoint pt;
					GetCursorPos(&pt);
					ScreenToClient(&pt);
					if(m_rc[WS_RC_SWATCHBOARD].PtInRect(pt) || m_rc[WS_RC_GRAND_VIEW].PtInRect(pt))
					{
						GetColor();
					}

					// Save Selected Color
					if(!m_rc[WS_RC_GRAND_VIEW].PtInRect(pt))
					{
						crSelect = cr;
					}
				}
				break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CWinSwatchDlg::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	KillTimer(TIMER_GETCOLOR_ID);
	::DeleteDC(hdcScreen);
	CDialog::OnOK();
}

// 畫出漸層色的函式
void CWinSwatchDlg::DrawGradient(CDC *pDC, CRect Rect, COLORREF Color1, COLORREF Color2, bool bDirection) 
{ 
	float blue1,blue2,green1,green2,red1,red2; 
	float blue_change,green_change,red_change; 

	blue1=GetBValue(Color1); 
	green1=GetGValue(Color1); 
	red1=GetRValue(Color1); 

	blue2=GetBValue(Color2); 
	green2=GetGValue(Color2); 
	red2=GetRValue(Color2); 

	int nDiv = 0; 
	if(bDirection)  
		nDiv = Rect.Height(); 
	else 
		nDiv = Rect.Width(); 

	blue_change=float(blue2-blue1)/float(nDiv-1); 
	green_change=float(green2-green1)/float(nDiv-1); 
	red_change=float(red2-red1)/float(nDiv-1); 

	for (int x=0; x<nDiv; ++x) { 
		CPen Pen, *pOldPen=NULL; 
		Pen.CreatePen(PS_SOLID,1,RGB(red1, green1, blue1)); 
		pOldPen=pDC->SelectObject(&Pen);
		if(bDirection) { 
			pDC->MoveTo(Rect.left,x+Rect.top); 
			pDC->LineTo(Rect.right,x+Rect.top); 
		} 
		else { 
			pDC->MoveTo(x+Rect.left,Rect.top); 
			pDC->LineTo(x+Rect.left,Rect.bottom); 
		} 
		pDC->SelectObject(pOldPen);

		blue1+=blue_change; 
		green1+=green_change; 
		red1+=red_change; 
	} 
}
void CWinSwatchDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_bSelectColor = TRUE;
	CDialog::OnLButtonDown(nFlags, point);
}

void CWinSwatchDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	m_bSelectColor = FALSE;
	CDialog::OnLButtonUp(nFlags, point);
}

void CWinSwatchDlg::OnBnClickedBtnAbout()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	MessageBox(_T("about me:\nhttp://ascii-iicsa.blogspot.com/\n\nemail:\nasciiss@gmail.com"));
}
