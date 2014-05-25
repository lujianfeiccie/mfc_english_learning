// MyAudioCls.cpp : implementation file
//

#include "stdafx.h"
#include "MyAudioCls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAudioCls

CMyAudioCls::CMyAudioCls()
{
	dwDataLength = 0;
	dwRepetitions = 1;
	//allocate memory for wave header
	pWaveHdr1 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	pWaveHdr2 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));

	//allocate memory for save buffer
	pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));
}

CMyAudioCls::~CMyAudioCls()
{
}


BEGIN_MESSAGE_MAP(CMyAudioCls, CWnd)
	//{{AFX_MSG_MAP(CMyAudioCls)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyAudioCls message handlers

void CMyAudioCls::StartRecording(HWND hWnd)
{
	//alloc buffer memory
	pBuffer1 = (PBYTE)malloc(INP_BUFFER_SIZE);
	pBuffer2 = (PBYTE)malloc(INP_BUFFER_SIZE);
	if (!pBuffer1 || !pBuffer2)
	{
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

void CMyAudioCls::StopRecording()
{
	::waveInStop(m_hWaveIn);
	::waveInReset(m_hWaveIn);
	Sleep(500);
	::waveInClose(m_hWaveIn);
}

void CMyAudioCls::StartPlaying(HWND hWnd, BOOL bPlaying)
{
	
	if(bPlaying)
	{
		waveOutReset(m_hWaveOut);
	}

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

void CMyAudioCls::Pause()
{
	waveOutPause(m_hWaveOut);	
}

void CMyAudioCls::StopPlaying()
{
	waveOutReset(m_hWaveOut);
}

void CMyAudioCls::Restart()
{
	waveOutRestart(m_hWaveOut);
}

void CMyAudioCls::OnMM_WIM_OPEN()
{

}

void CMyAudioCls::OnMM_WIM_DATA(PWAVEHDR pWavHdr, BOOL bEnding)
{
	//Reallocate save buffer memory
	pNewBuffer = (PBYTE)realloc(pSaveBuffer, dwDataLength + pWavHdr->dwBytesRecorded);

	if (pNewBuffer == NULL)
	{
		waveInClose (m_hWaveIn) ;
		MessageBeep (MB_ICONEXCLAMATION) ;
		AfxMessageBox("erro memory");
		return ;
	}
	
	pSaveBuffer = pNewBuffer ;
	///////////////////////////////////////////////////////////////////////////////////
	CopyMemory( pSaveBuffer + dwDataLength, pWavHdr->lpData, pWavHdr->dwBytesRecorded );

	dwDataLength += pWavHdr->dwBytesRecorded;

	if(bEnding)
	{
		waveInClose(m_hWaveIn);
		return;
	}

	// Send out a new buffer
	waveInAddBuffer(m_hWaveIn, pWavHdr, sizeof(WAVEHDR));

}

void CMyAudioCls::OnMM_WIM_CLOSE()
{
	waveInUnprepareHeader(m_hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInUnprepareHeader(m_hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	free(pBuffer1);
	free(pBuffer2);
}

void CMyAudioCls::OnMM_WOM_OPEN()
{
	// Set up header
	
	pWaveHdr1->lpData          = (LPTSTR)pSaveBuffer ;
	pWaveHdr1->dwBufferLength  = dwDataLength ;
	pWaveHdr1->dwBytesRecorded = 0 ;
	pWaveHdr1->dwUser          = 0 ;
	pWaveHdr1->dwFlags         = WHDR_BEGINLOOP | WHDR_ENDLOOP ;
	pWaveHdr1->dwLoops         = dwRepetitions ;
	pWaveHdr1->lpNext          = NULL ;
	pWaveHdr1->reserved        = 0 ;
	
	// Prepare and write
	
	waveOutPrepareHeader (m_hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveOutWrite (m_hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
}

void CMyAudioCls::OnMM_WOM_DONE()
{
	waveOutUnprepareHeader (m_hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveOutClose (m_hWaveOut) ;
}

void CMyAudioCls::OnMM_WOM_CLOSE()
{

}

DWORD CMyAudioCls::GetDataLength()
{
	return dwDataLength;
}

void CMyAudioCls::SaveAudioToFile(char *filename)
{
/*	FILE *fp;
	if(!(fp=fopen(filename, "wb")))
	{
		MessageBox("fail to open file!");
		return ;
	}

	DWORD ret=fwrite((PBYTE)pSaveBuffer, dwDataLength*sizeof(BYTE), 
						dwDataLength*sizeof(BYTE),fp);
	if(ret==0)
	{
		MessageBox("fail to write file!");
		return ;
	}

	fclose(fp);
	*/
	char szFilters[] = "Wave files (*.wav)|*.wav|All files (*.*)|*.*||";
	CFileDialog fdlg(TRUE,"wav","*.wav", OFN_HIDEREADONLY, szFilters, this);
	
	if(fdlg.DoModal() == IDOK)
	{
		CString	filename = fdlg.GetPathName();
		CFile file;
		file.Open(filename, CFile::modeCreate|CFile::modeWrite, NULL);
		file.Write(pSaveBuffer, dwDataLength);
		file.Close();
	}
}
