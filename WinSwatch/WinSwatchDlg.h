// WinSwatchDlg.h : 標頭檔
//

#pragma once

#include "SingleClkBitmapBtn.h"

// CWinSwatchDlg 對話方塊
class CWinSwatchDlg : public CDialog
{
// 建構
public:
	CWinSwatchDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_WINSWATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CDC dcMem; // 長條型的畫布
	CBitmap bmp;

	LOGFONT m_logfontSet;
	CFont m_fontSetTitle;
	CFont m_fontSetColor;

	COLORREF cr, crLast, crSelect;
	HDC hdcScreen;

	//DWORD m_dwR, m_dwG, m_dwB;
	BOOL m_bSelectColor;
	CString m_strColorInfo;

	enum {WS_MD_SCREEN, WS_MD_SWATCH};
	UINT m_unMode;

	enum {WS_RC_CLIENT, WS_RC_TITLE, WS_RC_SWATCHBOARD, WS_RC_GRAND_VIEW, WS_RC_ABOUT, WS_RC_SCMODE, WS_RC_SWMODE, WS_RC_EXIT, WS_RC_COLOR, WS_RC_INFO, WS_RC_COUNT};
	CRect m_rc[WS_RC_COUNT];

	//enum {WS_IMG_CLIENT, WS_IMG_COUNT};
	//CxImage m_img[WS_IMG_COUNT];

	CBitmap m_bmpBackGround;

	enum {WS_BTN_ABOUT, WS_BTN_SCMODE, WS_BTN_SWMODE, WS_BTN_EXIT, WS_BTN_COUNT};
	CSingleClkBitmapBtn m_btn[WS_BTN_COUNT];

	// Method
	void LoadParam();
	BOOL CreateRgn(CRgn& rgn,RECT& rcBound, int nRectCount, RECT* paRect);
	void GetColor();
	void DrawGradient(CDC *pDC, CRect Rect, COLORREF Color1, COLORREF Color2, bool bDirection);

	afx_msg void OnBnClickedBtnScreenmode();
	afx_msg void OnBnClickedBtnSwatchmode();
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnOK();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnBnClickedBtnAbout();
};
