// ChatEdit.cpp : implementation file
//

#include "stdafx.h"
#include "LANTalk.h"
#include "ChatEdit.h"


// CChatEdit

IMPLEMENT_DYNAMIC(CChatEdit, CEdit)

CChatEdit::CChatEdit()
{

}

CChatEdit::~CChatEdit()
{
}


BEGIN_MESSAGE_MAP(CChatEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChatEdit message handlers




void CChatEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	
}


BOOL CChatEdit::SetReadOnly(BOOL bReadOnly)
{
	CEdit::SetReadOnly(bReadOnly);
	//CRect rect;
	//GetClientRect(&rect);
	//InvalidateRect(&rect, 1);
	//UpdateWindow();
	return 0;
}


void CChatEdit::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CEdit::OnPaint() for painting messages
	//CRect rect;
	//GetClientRect(&rect);
	//CPaintDC pDC(this);
	//pDC.FillSolidRect(rect, RGB(255, 255, 255));
}
