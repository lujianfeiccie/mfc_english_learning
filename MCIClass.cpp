#include "StdAfx.h"
#include "MCIClass.h"


#define MAX_RETURN_LENGTH 1024

CMCIClass::CMCIClass(HWND hWnd)
{
	m_strMediumAlias = " ";
	m_hWndCallback = hWnd;
	m_bMediumOpen = FALSE;
}


CMCIClass::~CMCIClass()
{
	Stop();
	Close();
}

LONG CMCIClass::Open(LPCSTR strMediumName,LPCSTR strMediumType,LPCSTR strStyle,HWND hWnd)
{
	if(IsMediumOpen())
	{
		Stop();
		Close();
	}
	if(hWnd != NULL)
		m_hWndCallback = hWnd;

	CString strMedium = strMediumType;
	CString strCmd = "open ";
	m_strMediumAlias = strMediumType;
//	m_strMediumAlias += " _ALIAS ";

	strCmd += strMediumName;
	strCmd += " type ";
	strCmd += strMediumType;
	strCmd += " Alias ";
	strCmd += m_strMediumAlias;

	if(!strMedium.CompareNoCase("MPEGVideo"))
	{
		CString strHWnd;
		if(m_hWndCallback != NULL)
		{
			strHWnd.Format(" parent %u ",m_hWndCallback);
			strCmd += strHWnd;
		}

		strCmd += " style ";
		strCmd += strStyle;

		
	}
	//strCmd = "open G:\\friend1-01.avi type avivideo alias avi_video";
	LONG lRet = Execute(strCmd);

	if(lRet == 0)
		m_bMediumOpen = TRUE;

	
	return lRet;
}

LONG CMCIClass::Close()
{
	m_bMediumOpen = FALSE;
	CString strCmd = " close ";
	strCmd += m_strMediumAlias;

	return Execute(strCmd);
}

LONG CMCIClass::Play(LPCSTR strStyle,LPCSTR strFlag)
{
	CString strCmd = " play ";
	strCmd += m_strMediumAlias;
	strCmd += " ";
	CString strStyle0 = strStyle;
	if(!strStyle0.CompareNoCase("fullscreen")||
		!strStyle0.CompareNoCase("window"))
	{
	  CString strPut = "put ";
	  strPut += m_strMediumAlias;
	  strPut += " source destination ";
	  Execute(strPut);
	  strCmd += strStyle;
	  strCmd += " ";
	}
	CString s = strFlag;
	if(!s.IsEmpty())
	{
		strCmd += " ";
		strCmd += strFlag;
	}
	//strCmd = "play avivideo";
	return Execute(strCmd);
}

LONG CMCIClass::Pause()
{
	CString strCmd = " pause ";
	strCmd += m_strMediumAlias;
	return Execute(strCmd);
}

LONG CMCIClass::Resume()
{
	CString strCmd = " resume ";
	strCmd += m_strMediumAlias;

	return Execute(strCmd);
}
LONG CMCIClass::Stop()
{
	CString strCmd = "stop ";
	strCmd += m_strMediumAlias;
	
	return Execute(strCmd);
}

LONG CMCIClass::Seek(LONG lPos)
{
	CString strPos;
	if(lPos == 0L)
		strPos = " to start ";
	else if(lPos == -1L)
		strPos = " to end ";
	else 
		strPos.Format(" to %ld ",lPos);

	CString strCmd = " seek ";
	strCmd += m_strMediumAlias;
	strCmd += strPos;

	return Execute(strCmd);
}

LONG CMCIClass::Seek(LPCSTR strPos)
{
	CString strCmd = "seek ";
	strCmd += m_strMediumAlias;
	strCmd += " to ";
	strCmd += strPos;
	return Execute(strCmd);
}

LONG CMCIClass::SetTimeFormat(LPCSTR strTimeFormat)
{
	CString strCmd = "set ";
	strCmd += m_strMediumAlias;
	strCmd += " time format ";
	strCmd += strTimeFormat;

	return Execute(strCmd);
}

LONG CMCIClass::GetLength()
{
	CString strCmd = "status ";
	strCmd += m_strMediumAlias;
	strCmd += " length";

	CString strTimeFormat = GetTimeFormatA();
	SetTimeFormat("ms");

	char szReturn[MAX_RETURN_LENGTH];
	Execute(strCmd , szReturn);

	SetTimeFormat(strTimeFormat);
	return atol(szReturn);
}

CString CMCIClass::GetTimeFormat()
{
	CString strCmd = "status ";
	strCmd += m_strMediumAlias;
	strCmd += " time format";
	char szReturn[MAX_RETURN_LENGTH];
	Execute(szReturn);

	return CString(szReturn);
}

CString CMCIClass::GetMode()
{
	if(!IsMediumOpen())
		return CString("not open");

	CString strCmd ="status ";
	strCmd += m_strMediumAlias;
	strCmd += " mode ";

	char szReturn[MAX_RETURN_LENGTH];
	Execute(strCmd, szReturn);

	return CString(szReturn);
}

LONG CMCIClass::GetPosition(LPSTR strPos)
{
	CString strCmd = "status ";
	strCmd += m_strMediumAlias;
	strCmd += " position ";
	char szReturn[MAX_RETURN_LENGTH];
	Execute(strCmd,szReturn);
	lstrcpy(strPos,szReturn);

	return atol(szReturn);
}
LONG CMCIClass::GetStartPosition(LPSTR strPos)
{
	CString strCmd = "status ";
	strCmd += m_strMediumAlias;
	strCmd += " start position";

	char szReturn[MAX_RETURN_LENGTH];
	Execute(strCmd,szReturn);
	lstrcpy(strPos,szReturn);

	return atol(szReturn);
}

BOOL CMCIClass::IsMediumOpen()
{
	return m_bMediumOpen;
}

BOOL CMCIClass::IsMediumPresent()
{
	CString strCmd = "status ";
	strCmd += m_strMediumAlias;
	strCmd += " media present";

	char szReturn[MAX_RETURN_LENGTH];
	Execute(strCmd,szReturn);

	if(stricmp(szReturn,"true"))
		return FALSE;
	else 
		return TRUE;
}

LONG CMCIClass::Execute(LPCSTR strCmd, LPSTR lpstrReturn,BOOL bShowError)
{
	char szReturn[MAX_RETURN_LENGTH];
	MCIERROR mciError = mciSendString(strCmd,
		szReturn,
		sizeof(szReturn),
		m_hWndCallback);
	lstrcpy(lpstrReturn,szReturn);
	if(bShowError && mciError!=0)
	{
		mciGetErrorString(mciError,szReturn,sizeof(szReturn));
		MessageBox(m_hWndCallback,szReturn,"MCI Error", MB_OK|MB_ICONWARNING);
	}
	//Util::LOG("%s MCIERROR = %ld",strCmd,mciError);
	return mciError;
}

CString CMCIClass::GetMediumAlias()
{
	return m_strMediumAlias;
}
HWND CMCIClass::GetCallbackHWnd()
{
	return m_hWndCallback;
}
