#pragma once


// CSingleClkBitmapBtn

class CSingleClkBitmapBtn : public CBitmapButton
{
	DECLARE_DYNAMIC(CSingleClkBitmapBtn)

private:
	BOOL m_fSent;
	CToolTipCtrl m_ToolTip; 
public:
	CSingleClkBitmapBtn();
	virtual ~CSingleClkBitmapBtn();

protected:
	DECLARE_MESSAGE_MAP()
private:
	void InitToolTip(void);
public:
	void SetToolTipText(CString strText,BOOL bActivate);
	void SetToolTipAct(bool bActivate);
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


