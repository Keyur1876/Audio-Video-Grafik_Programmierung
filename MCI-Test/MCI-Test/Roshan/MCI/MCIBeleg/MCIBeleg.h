
// MCIBeleg.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CMCIBelegApp:
// Siehe MCIBeleg.cpp für die Implementierung dieser Klasse
//

class CMCIBelegApp : public CWinApp
{
public:
	CMCIBelegApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMCIBelegApp theApp;
