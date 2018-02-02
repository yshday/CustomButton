#include "stdafx.h"
#include "PButton.h"
#include "lpng.h"

PButton::PButton()
{
	m_image = NULL;
	m_cursor = NULL;
	m_state = State::Normal;
}


PButton::~PButton()
{
	if (m_image)
	{
		DeleteObject(m_image);
		m_image = NULL;
	}
}


BEGIN_MESSAGE_MAP(PButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN() // Pressed
	ON_WM_LBUTTONUP()	// 
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()


void PButton::PreSubclassWindow()
{
	m_style = GetButtonStyle();
	if ((m_style & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX)
	{
		m_style = BS_CHECKBOX;
	}
	else if ((m_style & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON)
	{
		m_style = BS_RADIOBUTTON;
	}
	else
	{
		m_style = BS_PUSHBUTTON;
	}

	m_cursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}


BOOL PButton::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}


void PButton::DrawItem(LPDRAWITEMSTRUCT lpDraw)
{
	ASSERT(lpDraw);

	CRect dest = lpDraw->rcItem;
	CRect src(0, 0, m_width, m_height);

	switch (m_state)
	{
	case State::Normal:
	{

		break;
	}
	case State::Hovered:
	{
		FillSolidRect(lpDraw->hDC, dest, RGB(193, 193, 193));
		src.OffsetRect(m_width, 0);
		break;
	}
	case State::Pressed:
	{
		FillSolidRect(lpDraw->hDC, dest, RGB(78, 166, 234));
		src.OffsetRect(m_width * 2, 0);
		break;
	}
	case State::Disabled:
	{
		src.OffsetRect(m_width * 3, 0);
		break;
	}
	default:
	{

		break;
	}
	}

	TRACE(L"DrawItem - state : %d, l : %d, t : %d, r : %d, b : %d\r\n",
		m_state,
		src.left,
		src.top,
		src.right,
		src.bottom);


	if (m_image != NULL)
	{
		HDC hdc = CreateCompatibleDC(lpDraw->hDC);
		HBITMAP bitmap = (HBITMAP)SelectObject(hdc, m_image);

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 0xFF, AC_SRC_ALPHA };
		::GdiAlphaBlend(
			lpDraw->hDC,
			dest.left,
			dest.top,
			dest.Width(),
			dest.Height(),
			hdc,
			src.left,
			src.top,
			m_width,
			m_height,
			bf);
		::SelectObject(hdc, bitmap);
		::DeleteDC(hdc);
	}

}


void PButton::FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF color)
{
	COLORREF col = ::SetBkColor(hdc, color);
	::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	::SetBkColor(hdc, col);
}


void PButton::SetImage(const int id, const CString filter)
{
	m_image = LoadPng(MAKEINTRESOURCE(id), filter, AfxGetInstanceHandle(), TRUE);
}


LRESULT PButton::OnMouseLeave(WPARAM wp, LPARAM lp)
{
	//TRACE(L"OnMouseLeave\r\n");
	m_state = State::Normal;
	m_tracked = false;
	Invalidate();
	return 0;
}


LRESULT PButton::OnMouseHover(WPARAM wp, LPARAM lp)
{
	//TRACE(L"OnMouseHover\r\n");
	m_state = State::Hovered;

	Invalidate();
	return 0;
}


void PButton::OnLButtonUp(UINT flags, CPoint point)
{
	//TRACE(L"OnLButtonUp\r\n");
	m_state = State::Normal;

	Invalidate();
	CButton::OnLButtonUp(flags, point);
}


void PButton::OnLButtonDown(UINT flags, CPoint point)
{
	//TRACE(L"OnLButtonDown\r\n");
	m_state = State::Pressed;

	Invalidate();
	CButton::OnLButtonDown(flags, point);
}


void PButton::OnMouseMove(UINT flags, CPoint point)
{
	//TRACE(L"OnMouseMove\r\n");
	//m_state = State::Hovered;
	//
	//Invalidate();

	if (!m_tracked)
	{
		TRACKMOUSEEVENT t;
		t.cbSize = sizeof t;
		t.hwndTrack = m_hWnd;
		t.dwFlags = TME_LEAVE | TME_HOVER;
		t.dwHoverTime = 1;
		if (TrackMouseEvent(&t))
		{
			m_tracked = true;
		}
	}

	CButton::OnMouseMove(flags, point);
}


void PButton::OnLButtonDblClk(UINT flags, CPoint point)
{
	CButton::OnLButtonDblClk(flags, point);
}