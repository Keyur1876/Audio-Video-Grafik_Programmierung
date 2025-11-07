
// MCI-TestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MCI-Test.h"
#include "MCI-TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMCITestDlg dialog



CMCITestDlg::CMCITestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCITEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCITestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCITestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMCITestDlg::OnBnClickedVideo)
	ON_BN_CLICKED(IDC_BUTTON2, &CMCITestDlg::OnBnClickedAudioMp3)
	ON_BN_CLICKED(IDC_BUTTON3, &CMCITestDlg::OnBnClickedAudioMid)
	ON_BN_CLICKED(IDC_BUTTON5, &CMCITestDlg::OnBnClickedAudioCD)
	ON_BN_CLICKED(IDC_BUTTON8, &CMCITestDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON6, &CMCITestDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_BUTTON7, &CMCITestDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_BUTTON9, &CMCITestDlg::OnBnClickedExit)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMCITestDlg::OnLbnSelchangeList1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMCITestDlg message handlers

BOOL CMCITestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(1, 200, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCITestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMCITestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMCITestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMCITestDlg::OnBnClickedVideo()
{
	// TODO: Add your control notification handler code here

	CRect r;
	GetDlgItem(IDC_DESTIN)->GetWindowRect(r); //Ignore this Error
	ScreenToClient(r);
	mci.OpenFile(L"test.mpg");
	mci.SetVideoPosition(GetSafeHwnd(),
		CRect(r.left, r.top, r.Width(), r.Height()));
	mci.Play();
	//SetDlgItemText(IDC_BtnPlayPause2, L"Pause");
}


void CMCITestDlg::OnBnClickedAudioMp3()
{
	mci.OpenFile(L"test.mp3");

	mci.Play();
}


void CMCITestDlg::OnBnClickedAudioMid()
{
	mci.OpenFile(L"canyon.mid");
	mci.Play();
}


void CMCITestDlg::OnBnClickedAudioCD()
{
	BYTE tracks;
	mci.OpenAudioCD(L"D:", tracks); // set as 0 if there is only on CD drive avaliable

	BYTE min, sek, frame;
	((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();
	RedrawWindow();
	for (int i = 1; i <= tracks; i++) {
		mci.GetTrackLength(i, min, sek, frame);
		CString temp; // z.B.Eintrag in eine ListBox : -)
		temp.Format(L"[%02d] %02d:%02d", i, min, sek);
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(temp);
	}

	//mci.TMSFSeek(2, 0, 0, 0);
	mci.Play();
}

void CMCITestDlg::OnBnClickedClose()
{
	// TODO: Add your control notification handler code here
	mci.Close();
}

void CMCITestDlg::OnBnClickedPlay()
{
	// TODO: Add your control notification handler code here
	mci.Play();
}

void CMCITestDlg::OnBnClickedPause()
{
	// TODO: Add your control notification handler code here
	mci.Pause();
}

void CMCITestDlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here

}

void CMCITestDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_LIST1))->GetCurSel() + 1, 0, 0, 0);
	mci.Play();
	//mci.Pause();
}

void CMCITestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	// Abfrage des Abspielstands
	CString str;
	unsigned char t, m, s, f;
	mci.GetTMSFPosition(t, m, s, f);
	int akt = m * 60 + s;

	// Abfrage der Trackinformationen
	BYTE min, sek, frame;
	mci.GetTrackLength(t, min, sek, frame);
	int ges = min * 60 + sek;

	// Berechnen des Fortschritts
	int progress;
	if (ges > 0) {
		progress = 100 * akt / ges;
	}
	else {
		progress = 0;
	}

	str.Format(L"[%02d] %02d:%02d - %d%%", t, m, s, progress);
	SetDlgItemText(IDC_TIME, str);

	CDialogEx::OnTimer(nIDEvent);
}
