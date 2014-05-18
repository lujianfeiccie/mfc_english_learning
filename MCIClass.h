#pragma once
#include <math.h>
#include <MMSystem.h>
class CMCIClass
{
protected:
	 //数据成员，仅用于描述类的内部性质，为了在其派生类中可见
	 CString m_strMediumAlias; //设备别名
	 HWND m_hWndCallback;      //回调窗口句柄
	 BOOL m_bMediumOpen;	   //媒体是否打开标记
public:
	CMCIClass(HWND hWnd = NULL);	
	virtual ~CMCIClass();
	LONG Open(LPCSTR strMedium,LPCSTR strMediumType,LPCSTR strStyle = "",HWND hWnd = NULL);
	LONG Close();
	LONG Play(LPCSTR strStyle = "",LPCSTR strFlag = "");
	LONG Pause();
	LONG Resume();
	LONG Stop();
	LONG Seek(LONG lPos);
	LONG Seek(LPCSTR strPos);
	LONG SetTimeFormat(LPCSTR strTimeFormat = "ms");
	LONG GetLength();
	CString GetTimeFormat();
	CString GetMode();
	LONG GetPosition(LPSTR strPos);
	LONG GetStartPosition(LPSTR strPos);
	BOOL IsMediumOpen();
	BOOL IsMediumPresent();

	LONG Execute(LPCSTR strCmd, LPSTR lpstrReturn = NULL,BOOL bShowError = FALSE);
	CString GetMediumAlias();
	HWND GetCallbackHWnd();
};

