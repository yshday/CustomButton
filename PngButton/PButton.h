//
//  PButton.h
//  FlyingFile
//
//  Created by jiransoft on 2018. 1. 24..
//  Copyright (c) 2018³â Seung Hwan Yeo. All rights reserved.
//


#pragma once

#include "afxwin.h"

class PButton : public CButton
{
public:
	PButton();
	~PButton();

	enum class State : unsigned int
	{
		Normal,
		Hovered,
		Pressed,
		Disabled,
	};

	
	void SetSize(const int width, const int height) { m_width = width; m_height = height; }
	void SetImage(const int id, const CString filter);
	void FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF color);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDraw);
	virtual void PreSubclassWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnLButtonUp(UINT flags, CPoint point);
	afx_msg void OnLButtonDown(UINT flags, CPoint point);
	afx_msg void OnMouseMove(UINT flags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT flags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnMouseHover(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()

private:
	HBITMAP m_image;
	HCURSOR m_cursor;
	DWORD m_style;
	State m_state;
	int m_width = 0;
	int m_height = 0;
	bool m_tracked = false;


};

