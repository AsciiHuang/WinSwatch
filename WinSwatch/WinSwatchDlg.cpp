// WinSwatchDlg.cpp : ��@��
//

#include "stdafx.h"
#include "WinSwatch.h"
#include "WinSwatchDlg.h"

#define TIMER_GETCOLOR_ID (4096)
#define TIMER_GETCOLOR_TIME (100)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinSwatchDlg ��ܤ��


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


// CWinSwatchDlg �T���B�z�`��

BOOL CWinSwatchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	LoadParam();
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CWinSwatchDlg::LoadParam()
{
	// enum {WS_RC_CLIENT, WS_RC_TITLE, WS_RC_SCMODE, WS_RC_SWMODE, WS_RC_EXIT, WS_RC_COUNT};
	m_rc[WS_RC_CLIENT].SetRect(0, 0, 204, 262); // �����d��
	m_rc[WS_RC_TITLE].SetRect(5, 5, 140, 17); // ���D
	m_rc[WS_RC_SWATCHBOARD].SetRect(6, 22, 198, 214); // RGB ��O
	m_rc[WS_RC_GRAND_VIEW].SetRect(6, 220, 198, 230); // ���h�e��
	m_rc[WS_RC_ABOUT].SetRect(141, 4, 154, 17); // ���� WinSwatch ����
	m_rc[WS_RC_SCMODE].SetRect(156, 4, 169, 17); // �ù��Ҧ�����
	m_rc[WS_RC_SWMODE].SetRect(171, 4, 184, 17); // �զ�L�Ҧ�����
	m_rc[WS_RC_EXIT].SetRect(186, 4, 199, 17); // ���}����
	m_rc[WS_RC_COLOR].SetRect(6, 236, 42, 256); // ��ܮ�
	m_rc[WS_RC_INFO].SetRect(50, 239, 196, 253); // ��T��

	// Init DC, bmp
	CDC* pDC = GetDC();
	dcMem.CreateCompatibleDC(NULL);
	bmp.CreateCompatibleBitmap(pDC, m_rc[WS_RC_CLIENT].Width(), m_rc[WS_RC_CLIENT].Height());
	dcMem.SelectObject(&bmp);
	dcMem.SetBkMode(TRANSPARENT);
	ReleaseDC(pDC);
	
	// �Ϥ�
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
	_tcscpy(m_logfontSet.lfFaceName, _T("Arial")); // �з���
	m_fontSetTitle.CreateFontIndirect(&m_logfontSet);

	m_logfontSet.lfHeight = 14;
	m_fontSetColor.CreateFontIndirect(&m_logfontSet);
	
	SetTimer(TIMER_GETCOLOR_ID, TIMER_GETCOLOR_TIME, NULL);
}

void CWinSwatchDlg::OnPaint()
{
	CPaintDC dc(this); // ø�s���˸m���e
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
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

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CWinSwatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWinSwatchDlg::OnBnClickedBtnScreenmode()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_unMode = WS_MD_SCREEN;
	InvalidateRect(&m_rc[WS_RC_TITLE], FALSE);
	UpdateWindow();
}

void CWinSwatchDlg::OnBnClickedBtnSwatchmode()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_unMode = WS_MD_SWATCH;
	InvalidateRect(&m_rc[WS_RC_TITLE], FALSE);
	UpdateWindow();
}

void CWinSwatchDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �b���[�J�z���T���B�z�`���{���X

	CRgn rgn;
	RECT rc[1+5] = 
	{
	  {0, 0, cx, cy}, /* ���������ϰ� */
	  {0, 3, 1, cy - 3}, /* �����Ĥ@�� */
	  {1, 1, 3, cy - 1}, /* �����ĤG�� */
	  {3, 0, cx - 3, cy}, /* �����ϰ� */
	  {cx - 3, 1, cx - 1, cy - 1}, /* �k���ĤG�� */
	  {cx - 1, 3, cx, cy - 3}, /* �k���Ĥ@�� */
	};
	CreateRgn(rgn, rc[0], 7, rc+1);
	SetWindowRgn((HRGN)rgn, TRUE);
	rgn.DeleteObject();

	Invalidate(); // �j�ø
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
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
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
	// TODO: �b���[�J�S�w���{���X�M (��) �I�s�����O
	KillTimer(TIMER_GETCOLOR_ID);
	::DeleteDC(hdcScreen);
	CDialog::OnOK();
}

// �e�X���h�⪺�禡
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
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_bSelectColor = TRUE;
	CDialog::OnLButtonDown(nFlags, point);
}

void CWinSwatchDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	m_bSelectColor = FALSE;
	CDialog::OnLButtonUp(nFlags, point);
}

void CWinSwatchDlg::OnBnClickedBtnAbout()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	MessageBox(_T("about me:\nhttp://ascii-iicsa.blogspot.com/\n\nemail:\nasciiss@gmail.com"));
}
