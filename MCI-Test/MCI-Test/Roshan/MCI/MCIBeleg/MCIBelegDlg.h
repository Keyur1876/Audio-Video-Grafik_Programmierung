
// MCIBelegDlg.h: Headerdatei
//

#pragma once

#include "CMCIObject.h"

// CMCIBelegDlg-Dialogfeld
class CMCIBelegDlg : public CDialogEx
{
// Konstruktion
public:
	CMCIBelegDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCIBELEG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CMCIObject mci;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnvideo();
	afx_msg void OnBnClickedBtnaudiomp3();
	afx_msg void OnBnClickedBtnaudiomidi();
	afx_msg void OnBnClickedBtnaudiocd();
	afx_msg void OnBnClickedBtnpause();
	afx_msg void OnLbnSelchangeListtime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnstop();
	afx_msg void OnBnClickedBtnclose();
	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnBnClickedBtnplaypause2();
};
