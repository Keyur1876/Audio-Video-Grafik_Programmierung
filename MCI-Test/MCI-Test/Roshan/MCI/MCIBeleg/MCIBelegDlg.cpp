
// MCIBelegDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "MCIBeleg.h"
#include "MCIBelegDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
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


// CMCIBelegDlg-Dialogfeld



CMCIBelegDlg::CMCIBelegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCIBELEG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCIBelegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCIBelegDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnVideo, &CMCIBelegDlg::OnBnClickedBtnvideo)
	ON_BN_CLICKED(IDC_BtnAudioMP3, &CMCIBelegDlg::OnBnClickedBtnaudiomp3)
	ON_BN_CLICKED(IDC_BtnAudioMIDI, &CMCIBelegDlg::OnBnClickedBtnaudiomidi)
	ON_BN_CLICKED(IDC_BtnAudioCD, &CMCIBelegDlg::OnBnClickedBtnaudiocd)
	ON_BN_CLICKED(IDC_BtnPause, &CMCIBelegDlg::OnBnClickedBtnpause)
	ON_LBN_SELCHANGE(IDC_LISTtime, &CMCIBelegDlg::OnLbnSelchangeListtime)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BtnStop, &CMCIBelegDlg::OnBnClickedBtnstop)
	ON_BN_CLICKED(IDC_BtnClose, &CMCIBelegDlg::OnBnClickedBtnclose)
	ON_BN_CLICKED(IDC_BtnExit, &CMCIBelegDlg::OnBnClickedBtnexit)
	ON_BN_CLICKED(IDC_BtnPlayPause2, &CMCIBelegDlg::OnBnClickedBtnplaypause2)
END_MESSAGE_MAP()


// CMCIBelegDlg-Meldungshandler

BOOL CMCIBelegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
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

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	SetTimer(1, 200, 0);
	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CMCIBelegDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMCIBelegDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMCIBelegDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMCIBelegDlg::OnBnClickedBtnvideo()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	CRect r;
	GetDlgItem(IDC_DESTIN)->GetWindowRect(r);
	ScreenToClient(r);
	mci.OpenFile(L"test.mpg");
	mci.SetVideoPosition(GetSafeHwnd(),
		CRect(r.left, r.top, r.Width(), r.Height()));
	mci.Play();
	//SetDlgItemText(IDC_BtnPlayPause2, L"Pause");

}


void CMCIBelegDlg::OnBnClickedBtnaudiomp3()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	mci.OpenFile(L"audio_castor.mp3");
	//mci.OpenFile(L"DerMicrosoftSound.wav"); //Test mit wav
	mci.Play();
	//SetDlgItemText(IDC_BtnPlayPause2, L"Pause"); //Idee: Ansatz um PlayPause auf einen Button zu reduizeren.
}


void CMCIBelegDlg::OnBnClickedBtnaudiomidi()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	mci.OpenFile(L"audio_canyon.mid");
	mci.Play();
	//SetDlgItemText(IDC_BtnPlayPause2, L"Pause");
}


void CMCIBelegDlg::OnBnClickedBtnaudiocd()
{
	((CListBox*)GetDlgItem(IDC_LISTtime))->ResetContent();
	BYTE tracks;
	mci.OpenAudioCD(0, tracks); // sucht und öffnet eine AudioCD
	// ein spezielles Laufwerk: mci.OpenAudioCD(L"e:",tracks);
	BYTE min, sek, frame;

	for (int i = 1; i <= tracks; i++) {
		mci.GetTrackLength(i, min, sek, frame);
		CString temp; // z.B.Eintrag in eine ListBox : -)
		temp.Format(L"[%02d] %02d:%02d", i, min, sek);
		((CListBox*)GetDlgItem(IDC_LISTtime))->AddString(temp);
	}

	//mci.TMSFSeek(2, 0, 0, 0); // zweiter Titel auf der Audio-CD
	mci.Play();
	//SetDlgItemText(IDC_BtnPlayPause2, L"Pause");
}


//Starte Abspielen
void CMCIBelegDlg::OnBnClickedBtnplaypause2()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	mci.Play();
	/*
	//void CMCIBelegDlg::OnBnClickedBtnPlay()
	if (mci.getPlayed()) {
		mci.Pause();
		SetDlgItemText(IDC_BtnPlayPause2, L"Play");
	}
	else {
		mci.Play();
		SetDlgItemText(IDC_BtnPlayPause2, L"Pause");
	}
	*/
}


//Pause Abspiel
void CMCIBelegDlg::OnBnClickedBtnpause()
{
	mci.Pause();
}


// Wechsel CDTrack 
void CMCIBelegDlg::OnLbnSelchangeListtime()
{
	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_LISTtime))->GetCurSel() + 1, 0, 0, 0);
	mci.Play();
}


void CMCIBelegDlg::OnTimer(UINT_PTR nIDEvent)
{
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

// Reset Abspielvorgang (Zurück an den Anfang)
void CMCIBelegDlg::OnBnClickedBtnstop()
{
	mci.Stop();
	//m_akt = s_akt = f_akt = 0;
	//mci.TMSFSeek(0, 0, 0, 0);
	//SetDlgItemText(IDC_BtnPlayPause, L"Play");
}


// Beendet aktuelles Medium
void CMCIBelegDlg::OnBnClickedBtnclose()
{
	((CListBox*)GetDlgItem(IDC_LISTtime))->ResetContent(); //Leer List -> nach neu Laden den noch Liste mit 204 Zeiten
	mci.Close();
}


// Verlässt Anwendung
void CMCIBelegDlg::OnBnClickedBtnexit()
{
	OnOK();
	CDialogEx::OnCancel();
}
