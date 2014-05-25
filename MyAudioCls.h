#if !defined(AFX_MYAUDIOCLS_H__522F7552_F9C6_4FCA_B299_2C6BE406402D__INCLUDED_)
#define AFX_MYAUDIOCLS_H__522F7552_F9C6_4FCA_B299_2C6BE406402D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyAudioCls.h : header file
//

#include "mmsystem.h"

#define INP_BUFFER_SIZE	16384
#define HZ_NORMAL	11025
#define NORMAL_RATE 11025
/////////////////////////////////////////////////////////////////////////////
// CMyAudioCls window

class CMyAudioCls : public CWnd
{
// Construction
public:
	CMyAudioCls();

// Attributes
public:
	void Restart();
	void StopPlaying();
	void Pause();
	void StartPlaying(HWND hWnd, BOOL bPlaying);
	void StopRecording();
	void StartRecording(HWND hWnd);
	HWAVEIN		m_hWaveIn;
	HWAVEOUT	m_hWaveOut;
	PBYTE		pBuffer1;
	PBYTE		pBuffer2;
	PBYTE		pSaveBuffer;
	PBYTE		pNewBuffer;
	PWAVEHDR	pWaveHdr1;
	PWAVEHDR	pWaveHdr2;
	DWORD		dwDataLength;
	DWORD		dwRepetitions;
	WAVEFORMATEX	wavformex;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAudioCls)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveAudioToFile(char* filename);
	DWORD GetDataLength();
	void OnMM_WOM_CLOSE();
	void OnMM_WOM_DONE();
	void OnMM_WOM_OPEN();
	void OnMM_WIM_CLOSE();
	void OnMM_WIM_DATA(PWAVEHDR pWavHdr, BOOL bEnding);
	void OnMM_WIM_OPEN();
	virtual ~CMyAudioCls();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyAudioCls)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAUDIOCLS_H__522F7552_F9C6_4FCA_B299_2C6BE406402D__INCLUDED_)
