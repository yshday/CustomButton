
// PngButtonDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "PButton.h"


// CPngButtonDlg ��ȭ ����
class CPngButtonDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPngButtonDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PNGBUTTON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	PButton m_btn;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
