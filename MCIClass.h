#pragma once
#include <math.h>
#include <MMSystem.h>
class CMCIClass
{
protected:
	 //���ݳ�Ա����������������ڲ����ʣ�Ϊ�������������пɼ�
	 CString m_strMediumAlias; //�豸����
	 HWND m_hWndCallback;      //�ص����ھ��
	 BOOL m_bMediumOpen;	   //ý���Ƿ�򿪱��
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

