
// MCI-TestDlg.h : header file
//

#pragma once

#include "CMCIObject.h"

// CMCITestDlg dialog
class CMCITestDlg : public CDialogEx
{
// Construction
public:
	CMCITestDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCITEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CMCIObject mci;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVideo();
	afx_msg void OnBnClickedAudioMp3();
	afx_msg void OnBnClickedAudioMid();
	afx_msg void OnBnClickedAudioCD();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedExit();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
