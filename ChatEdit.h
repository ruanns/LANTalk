#pragma once


// CChatEdit

class CChatEdit : public CEdit
{
	DECLARE_DYNAMIC(CChatEdit)

public:
	CChatEdit();
	virtual ~CChatEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	BOOL SetReadOnly(BOOL bReadOnly = TRUE);
	afx_msg void OnPaint();
};


