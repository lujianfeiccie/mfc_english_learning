// MyAudio.cpp: implementation of the CMyAudio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyAudio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyAudio::CMyAudio()
{
	//allocate memory for wave header
	pWaveHdr1 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	pWaveHdr2 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));

	//allocate memory for save buffer
	pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));
}

CMyAudio::~CMyAudio()
{

}

void CMyAudio::StartRecording(HWND hWnd)
{
	//alloc buffer memory
	pBuffer1 = (PBYTE)malloc(INP_BUFFER_SIZE);
	pBuffer2 = (PBYTE)malloc(INP_BUFFER_SIZE);
	if (!pBuffer1 || !pBuffer2) {
		if (pBuffer1) free(pBuffer1);
		if (pBuffer2) free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox("Memory erro!");
		return ;
	}

	//Open waveformat audio for input

	wavformex.wFormatTag = WAVE_FORMAT_PCM;
	wavformex.nChannels	 = 1;
	wavformex.nSamplesPerSec = HZ_NORMAL;
	wavformex.nAvgBytesPerSec= NORMAL_RATE;
	wavformex.nBlockAlign = 1;
	wavformex.wBitsPerSample = 8;
	wavformex.cbSize = 0;

	//Open the device for recording
	if(waveInOpen(&m_hWaveIn, WAVE_MAPPER, &wavformex, (DWORD)hWnd, NULL, CALLBACK_WINDOW))
	{
		free(pBuffer1);
		free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox("Audio can not be open!");
	}

	//为录音设备准备缓存//////////////////////////////////////
	pWaveHdr1->lpData =			(LPTSTR)pBuffer1;
	pWaveHdr1->dwBufferLength = INP_BUFFER_SIZE;
	pWaveHdr1->dwBytesRecorded= 0;
	pWaveHdr1->dwFlags =		0;
	pWaveHdr1->dwUser  =		0;
	pWaveHdr1->dwLoops =		1;
	pWaveHdr1->lpNext  =		NULL;
	pWaveHdr1->reserved=		0;

	waveInPrepareHeader(m_hWaveIn, pWaveHdr1, sizeof(WAVEHDR));

	pWaveHdr2->lpData=(LPTSTR)pBuffer2;
	pWaveHdr2->dwBufferLength=INP_BUFFER_SIZE;
	pWaveHdr2->dwBytesRecorded=0;
	pWaveHdr2->dwUser=0;
	pWaveHdr2->dwFlags=0;
	pWaveHdr2->dwLoops=1;
	pWaveHdr2->lpNext=NULL;
	pWaveHdr2->reserved=0;
	
	waveInPrepareHeader(m_hWaveIn,pWaveHdr2,sizeof(WAVEHDR));
	//缓存已准备好///////////////////////////////////////////////

	pSaveBuffer = (PBYTE)realloc (pSaveBuffer, 1) ;

	//给录音设备添加缓存
	waveInAddBuffer(m_hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInAddBuffer(m_hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	//开始录音//
	dwDataLength = 0;
	waveInStart(m_hWaveIn);
}

void CMyAudio::StopRecording()
{
	::waveInStop(m_hWaveIn);
	::waveInReset(m_hWaveIn);
	Sleep(500);
	::waveInClose(m_hWaveIn);
}

void CMyAudio::StartPlaying(HWND hWnd)
{
	
	//open waveform audio for output
	wavformex.wFormatTag		=	WAVE_FORMAT_PCM;
	wavformex.nChannels			=	1;
	wavformex.nSamplesPerSec	=	HZ_NORMAL;
	wavformex.nAvgBytesPerSec	=	NORMAL_RATE;
	wavformex.nBlockAlign		=	1;
	wavformex.wBitsPerSample	=	8;
	wavformex.cbSize			=	0;

	if(waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &wavformex, (DWORD)hWnd,
					NULL, CALLBACK_WINDOW))
	{
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox("Audio output erro");
	}
}

void CMyAudio::Pause()
{
	waveOutPause(m_hWaveOut);	
}

void CMyAudio::StopPlaying()
{
	waveOutReset(m_hWaveOut);
}

void CMyAudio::Restart()
{
	waveOutRestart(m_hWaveOut);
}
