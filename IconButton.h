#pragma once


// CIconButton

class CIconButton : public CButton
{
	DECLARE_DYNAMIC(CIconButton)

public:
	CIconButton();
	virtual ~CIconButton();
	void SetIcon(UINT nIcon, int size = 32);
private:
	HICON m_hIcon;
	int m_size;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


