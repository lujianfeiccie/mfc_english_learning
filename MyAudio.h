// MyAudio.h: interface for the CMyAudio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYAUDIO_H__C2D7952F_8DF4_11D1_9316_00E04CA820F9__INCLUDED_)
#define AFX_MYAUDIO_H__C2D7952F_8DF4_11D1_9316_00E04CA820F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#pragma comment(lib,"winmm.lib")
#include "mmsystem.h"

#define  INP_BUFFER_SIZE 16384
#define	 HZ_POOR	8000
#define	 HZ_NORMAL	11025
#define  HZ_HIGH	22050
#define  LOW_RATE		8000
#define  NORMAL_RATE	11025
#define	 HIGH_RATE		22050

class CMyAudio 
{
public:
	CMyAudio();
	virtual ~CMyAudio();
public:
	void Restart();
	void StopPlaying();
	void Pause();
	void StartPlaying(HWND hWnd);
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

};

#endif // !defined(AFX_MYAUDIO_H__C2D7952F_8DF4_11D1_9316_00E04CA820F9__INCLUDED_)
