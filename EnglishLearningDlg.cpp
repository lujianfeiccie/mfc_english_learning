
// EnglishLearningDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EnglishLearning.h"
#include "EnglishLearningDlg.h"
#include "afxdialogex.h"
#define TIME_DELAY 100
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnglishLearningDlg �Ի���




CEnglishLearningDlg::CEnglishLearningDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnglishLearningDlg::IDD, pParent),CMCIClass(m_hWnd)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bRecording=FALSE;
	bPlaying=FALSE;
	bPaused=FALSE;
	bEnding=FALSE;
	m_pAudio = new CMyAudioCls;
}

void CEnglishLearningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_STATIC_TIME, m_static_time);
	DDX_Control(pDX, IDC_EDIT_NO, m_edit_no);
	DDX_Control(pDX, IDC_EDIT_START, m_edit_starttime);
	DDX_Control(pDX, IDC_EDIT_END, m_edit_endtime);
}

BEGIN_MESSAGE_MAP(CEnglishLearningDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_STOP, &CEnglishLearningDlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CEnglishLearningDlg::OnBnClickedBtnPlay)
	ON_COMMAND(ID_MENU_OPEN,&CEnglishLearningDlg::OnMenuOpenFile)
	ON_BN_CLICKED(IDC_BTN_SAVE_CONFIG, &CEnglishLearningDlg::OnBnClickedBtnSaveConfig)
	ON_BN_CLICKED(IDC_BTN_READ_CONFIG, &CEnglishLearningDlg::OnBnClickedBtnReadConfig)
	ON_BN_CLICKED(IDC_BTN_SEEK, &CEnglishLearningDlg::OnBnClickedBtnSeek)
	ON_BN_CLICKED(IDC_BTN_START_RECORDING, &CEnglishLearningDlg::OnBnClickedBtnStartRecording)
	ON_BN_CLICKED(IDC_BTN_STOP_RECORDING, &CEnglishLearningDlg::OnBnClickedBtnStopRecording)
	ON_BN_CLICKED(IDC_BTN_STOP_PLAYING_RECORD, &CEnglishLearningDlg::OnBnClickedBtnStopPlayingRecord)
	ON_BN_CLICKED(IDC_BTN_PLAY_RECORD, &CEnglishLearningDlg::OnBnClickedBtnPlayRecord)
	ON_MESSAGE(MM_WIM_OPEN,OnMM_WIM_OPEN)
	ON_MESSAGE(MM_WIM_DATA,OnMM_WIM_DATA)
	ON_MESSAGE(MM_WIM_CLOSE,OnMM_WIM_CLOSE)
	ON_MESSAGE(MM_WOM_OPEN,OnMM_WOM_OPEN)
	ON_MESSAGE(MM_WOM_DONE,OnMM_WOM_DONE)
	ON_MESSAGE(MM_WOM_CLOSE,OnMM_WOM_CLOSE)
END_MESSAGE_MAP()


// CEnglishLearningDlg ��Ϣ�������

BOOL CEnglishLearningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEnglishLearningDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEnglishLearningDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void CEnglishLearningDlg::OnOk()//ɶҲ������OK��  
{  
}  
void CEnglishLearningDlg::OnCancel()//ͬ��  
{  
  
}  
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEnglishLearningDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEnglishLearningDlg::OnBnClickedBtnPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	Play();
}

void CEnglishLearningDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Stop();
}

void CEnglishLearningDlg::OnMenuOpenFile()
{
	CString strFilter;
	UpdateData(true);
	CFileDialog FileDlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		(LPCSTR)strFilter,this);
	if(FileDlg.DoModal() == IDOK)
	{
		CString strFileName = FileDlg.GetPathName();
		char szFileName[_MAX_PATH];
		GetShortPathName((LPCSTR)strFileName,szFileName,_MAX_PATH);
		char szExt[8];
		_splitpath((const char*)szFileName,NULL,NULL,NULL,szExt);

		MCIERROR  mciError = 0;
		if(!stricmp(szExt,".avi")){
			CString style;
			style.Format(" %u ",WS_CHILD);
			CStatic *pStatic=(CStatic*)GetDlgItem(IDC_STATIC_VIDEO);
			HWND h=pStatic->GetSafeHwnd(); 
			mciError = Open(szFileName,"MPEGVideo",style,h);
		}

		if(mciError == 0)
		{
			LONG length = GetLength();
			Util::LOG("LENGTH = %ld",length);
			m_slider.SetRange(0,length);
			SetTimeFormat("ms");
			SetTimer(1,TIME_DELAY,NULL);
		}

		CString s = FileDlg.GetFileName();
		SetWindowTextA(s);
	}
}
void CEnglishLearningDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString strMode = GetMode();
	if(! strMode.CompareNoCase("playing"))
	{
		Stop();
	}
	int nSPos = m_slider.GetPos();
	Seek(nSPos);
	if(!strMode.CompareNoCase("playing"))
	{
		Play();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CEnglishLearningDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==1)
	{
		char str[50];
		GetPosition(str);
		m_slider.SetPos(atoi(str));
		m_static_time.SetWindowTextA(str);
	}
	else if(nIDEvent==2)
	{
		CString tempstr;
		m_edit_endtime.GetWindowTextA(tempstr);
		int endtime = atoi(tempstr);
		if(m_slider.GetPos()>endtime)
		{
			Stop();
			KillTimer(2);
		}
	}
	CDialog::OnTimer(nIDEvent);
}
void CEnglishLearningDlg::OnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strMode = GetMode();
	if(! strMode.CompareNoCase("playing"))
	{
		Stop();
	}
	KillTimer(1);
	EndDialog(IDCANCEL);
	CDialog::OnClose();
}

void CEnglishLearningDlg::OnBnClickedBtnSaveConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Record record ;
	CString tempstr;
	m_edit_no.GetWindowTextA(tempstr);
	record.no = atoi(tempstr);

	m_edit_starttime.GetWindowTextA(tempstr);
	record.starttime = atoi(tempstr);

	m_edit_endtime.GetWindowTextA(tempstr);
	record.endtime = atoi(tempstr);

	Config::WriteConfig(&record);

	MessageBox("����ɹ�","��ʾ");
}


void CEnglishLearningDlg::OnBnClickedBtnReadConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	Record record ;
	CString tempstr;
	m_edit_no.GetWindowTextA(tempstr);
	record.no = atoi(tempstr);
	
	Config::ReadConfig(&record);
	tempstr.Format("%d",record.starttime);
	m_edit_starttime.SetWindowTextA(tempstr);

	tempstr.Format("%d",record.endtime);
	m_edit_endtime.SetWindowTextA(tempstr);
}


void CEnglishLearningDlg::OnBnClickedBtnSeek()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString tempstr;
	m_edit_starttime.GetWindowTextA(tempstr);
	Seek(tempstr);
	Play();
	SetTimer(2,TIME_DELAY,NULL);
}


void CEnglishLearningDlg::OnBnClickedBtnStartRecording()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pAudio->StartRecording(this->m_hWnd);
	bRecording = TRUE;
	bEnding = FALSE;
}


void CEnglishLearningDlg::OnBnClickedBtnStopRecording()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!bPlaying)
	{
		return;
	}

	bEnding = TRUE;
	m_pAudio->StopPlaying();
}


void CEnglishLearningDlg::OnBnClickedBtnStopPlayingRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!bPlaying)
	{
		return;
	}

	bEnding = TRUE;
	m_pAudio->StopPlaying();
}


void CEnglishLearningDlg::OnBnClickedBtnPlayRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: Add your control notification handler code here
	if(bRecording)
	{
		m_pAudio->StopRecording();
	}

	m_pAudio->StartPlaying(this->m_hWnd, bPlaying);
}



LRESULT CEnglishLearningDlg::OnMM_WIM_OPEN(UINT wParam, LONG lParam)
{
	bRecording = TRUE;
	m_pAudio->OnMM_WIM_OPEN();
	return 0;
}

LRESULT CEnglishLearningDlg::OnMM_WIM_DATA(UINT wParam, LONG lParam)
{
	m_pAudio->OnMM_WIM_DATA((PWAVEHDR)lParam, bEnding);
	return 0;
}

LRESULT CEnglishLearningDlg::OnMM_WIM_CLOSE(UINT wParam, LONG lParam)
{
	if(m_pAudio->GetDataLength()==0)
	{
		return 0;
	}

	m_pAudio->OnMM_WIM_CLOSE();

	bRecording = FALSE;
	return 0;
}

LRESULT CEnglishLearningDlg::OnMM_WOM_OPEN(UINT wParam, LONG lParam)
{
	m_pAudio->OnMM_WOM_OPEN();
	bPlaying = TRUE;
	bEnding = FALSE;
	return 0;
}

LRESULT CEnglishLearningDlg::OnMM_WOM_DONE(UINT wParam, LONG lParam)
{
	m_pAudio->OnMM_WOM_DONE();

	bPaused = FALSE;
	bPlaying = FALSE;
	return 0;
}

LRESULT CEnglishLearningDlg::OnMM_WOM_CLOSE(UINT wParam, LONG lParam)
{
	m_pAudio->OnMM_WOM_CLOSE();

	bPaused = FALSE;
	bPlaying = FALSE;
	return 0;
}