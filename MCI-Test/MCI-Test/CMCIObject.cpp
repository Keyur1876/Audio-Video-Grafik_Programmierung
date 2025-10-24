#include "pch.h"
#include "CMCIObject.h"

CMCIObject::CMCIObject()
{
	m_op.dwCallback = 0;
	m_op.wDeviceID = 0;
	m_op.lpstrDeviceType = 0;
	m_op.lpstrElementName = 0;
	m_op.lpstrAlias = 0;
	m_Result = 0;
}

CMCIObject::~CMCIObject()
{ //Make sure that object is not in use
	if (m_op.wDeviceID != 0)
	Close();
}

bool CMCIObject::OpenAudioCD(LPCWSTR drive, BYTE &tracks)
{
	DWORD flag = 0;
	if (m_op.wDeviceID != 0) Close();

	m_op.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_CD_AUDIO; //dirty

	if(m_op.lpstrElementName == drive)
	{
		flag = MCI_OPEN_ELEMENT;
	}

	if((m_Result = mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE_ID | flag | MCI_WAIT | MCI_OPEN_TYPE , (DWORD_PTR)&m_op)) != 0)
	{
		MCIError();
		return false;
	}

	// wird noch erweitert ...........

	return true;
}

bool CMCIObject::OpenFile(LPCWSTR pszFileName)
{
	if (m_op.wDeviceID != 0) 
		Close();
	m_op.lpstrDeviceType = 0;
	m_op.lpstrElementName = pszFileName;
	if ((m_Result = mciSendCommand(0,
		MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&m_op)) != 0) {
		MCIError();
		return false;
	}
	// wird später hier erweitert
		return true;
}

void CMCIObject::Close()
{
	MCI_GENERIC_PARMS gp;

	if (m_op.wDeviceID != 0)
	{
		Stop();  //just in Case.
		//#ifndef _DEBUG

		if ((m_Result = mciSendCommandA(m_op.wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD_PTR)&gp)) != 0)
		{
			MCIError();
		}
		//#endif
		m_op.wDeviceID = 0;
	}
}


void CMCIObject::Play()
{
	MCI_PLAY_PARMS play;
	if (m_op.wDeviceID == 0) return; // not open
	
	if ((m_Result = mciSendCommandA(m_op.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&play)) != 0)
	{
		MCIError();
	}
}

void CMCIObject::Stop()
{
	if (m_op.wDeviceID == 0) return; // not open
	if ((m_Result = mciSendCommandA(m_op.wDeviceID, MCI_STOP, MCI_WAIT, 0)) != 0)
	{
		MCIError();
	}
}

void CMCIObject::Pause()
{
	if (m_op.wDeviceID == 0) return; // not open
	if ((m_Result = mciSendCommandA(m_op.wDeviceID, MCI_PAUSE, MCI_WAIT, 0)) != 0)
	{
		MCIError();
	}
}

/*
void CMCIOject::MCIError()
{
	char buf[512];
	buf[0] = '\0';
	mciGetErrorString(m_Result, (LPWSTR)buf, sizeof(buf));
	if (!strlen(buf))
		strcpy(buf, "Unknown error");
	AfxMessageBox((LPCWSTR)buf);
	m_op.wDeviceID = 0;
}
*/

void CMCIObject::MCIError()
{
	char buf[512] = { 0 };
	mciGetErrorStringA(m_Result, buf, sizeof(buf));

	if (!strlen(buf))
		strcpy_s(buf, sizeof(buf), "Unknown MCI Error");

	// Convert char → wchar_t
	wchar_t wbuf[512];
	MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, 512);

	AfxMessageBox(wbuf);
	m_op.wDeviceID = 0;
}

bool SetVideoPosition(HWND hwnd, CRect rect)
{

}