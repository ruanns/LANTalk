// IconButton.cpp : 实现文件
//

#include "stdafx.h"
#include "LANTalk.h"
#include "IconButton.h"


// CIconButton

IMPLEMENT_DYNAMIC(CIconButton, CButton)

CIconButton::CIconButton()
{
	m_size = 32;
}

CIconButton::~CIconButton()
{
}

void CIconButton::SetIcon(UINT nIcon, int size)
{
	m_hIcon = AfxGetApp()->LoadIcon(nIcon);
	m_size = size;
}


BEGIN_MESSAGE_MAP(CIconButton, CButton)
END_MESSAGE_MAP()



// CIconButton 消息处理程序




void CIconButton::DrawItem(LPDRAWITEMSTRUCT lpDIS/*lpDrawItemStruct*/)
{
	// TODO:  添加您的代码以绘制指定项
	CDC dc;
	dc.Attach(lpDIS->hDC);
	CRect rect = lpDIS->rcItem;
	//填充背景
	dc.FillSolidRect(rect, GetSysColor(COLOR_BTNFACE));
	//按下按钮状态，文字和图标稍稍偏移
	if (lpDIS->itemState & ODS_SELECTED) {
		rect.OffsetRect(1, 1);
	}
	//画图标
	int n = rect.Height();
	CRect rc = rect;
	rc.right = n;
	//rc.DeflateRect(n, n);
	::DrawIconEx(dc.GetSafeHdc(), rc.left, rc.top, m_hIcon, m_size, m_size, 0, 0, DI_NORMAL);
	//画焦点
	if (lpDIS->itemState & ODS_FOCUS) {
		rc.CopyRect(rect);
		rc.DeflateRect(2, 2);
		dc.DrawFocusRect(rc);
	}
	dc.Detach();
}
