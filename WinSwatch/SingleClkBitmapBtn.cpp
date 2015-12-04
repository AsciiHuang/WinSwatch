// SingleClkBitmapBtn.cpp : implementation file
//

#include "stdafx.h"
#include "SingleClkBitmapBtn.h"


// CSingleClkBitmapBtn

IMPLEMENT_DYNAMIC(CSingleClkBitmapBtn, CBitmapButton)
CSingleClkBitmapBtn::CSingleClkBitmapBtn()
{
	m_fSent=FALSE;
}

CSingleClkBitmapBtn::~CSingleClkBitmapBtn()
{
}


BEGIN_MESSAGE_MAP(CSingleClkBitmapBtn, CBitmapButton)
END_MESSAGE_MAP()



// CSingleClkBitmapBtn message handlers

LRESULT CSingleClkBitmapBtn::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch( message )
	{
		case WM_LBUTTONUP:
		{
			if( TRUE == m_fSent )
			{
				this->SendMessage( BM_SETSTATE, 0 );
				m_fSent = FALSE;

				CWnd* pParent = GetParent();
				if( NULL != pParent )
				{
					::SendMessage( pParent->m_hWnd, WM_COMMAND, (BN_CLICKED<<16) | this->GetDlgCtrlID(), (LPARAM)this->m_hWnd );
				}
			}

			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			this->SendMessage( BM_SETSTATE, 1 );
			m_fSent = TRUE;

			return 0;
		}
	}
	return CBitmapButton::DefWindowProc(message, wParam, lParam);
}

void CSingleClkBitmapBtn::SetToolTipText(CString strText,BOOL bActivate)
{
	if(strText.IsEmpty())
	{
		return;
	}
	InitToolTip();
	if(m_ToolTip.GetToolCount()==0)
	{
		CRect rect;
		GetClientRect(rect);
		m_ToolTip.AddTool(this,strText,rect,1);
	}
	m_ToolTip.UpdateTipText(strText,this,1);
	m_ToolTip.Activate(bActivate);
}

void CSingleClkBitmapBtn::InitToolTip(void)
{
	if(m_ToolTip.m_hWnd==NULL)
	{
		m_ToolTip.Create(this);
		m_ToolTip.Activate(FALSE);
	}
}

void CSingleClkBitmapBtn::SetToolTipAct(bool bActivate)
{
	if(m_ToolTip.GetToolCount()==0)
	{
		return;
	}
	m_ToolTip.Activate(bActivate);
}

BOOL CSingleClkBitmapBtn::PreTranslateMessage(MSG* pMsg)
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	return CBitmapButton::PreTranslateMessage(pMsg);
}
