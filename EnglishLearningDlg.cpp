
// EnglishLearningDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnglishLearning.h"
#include "EnglishLearningDlg.h"
#include "afxdialogex.h"
#define TIME_DELAY 100
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CEnglishLearningDlg 对话框




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


// CEnglishLearningDlg 消息处理程序

BOOL CEnglishLearningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEnglishLearningDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void CEnglishLearningDlg::OnOk()//啥也不做就OK了  
{  
}  
void CEnglishLearningDlg::OnCancel()//同上  
{  
  
}  
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEnglishLearningDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEnglishLearningDlg::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码	
	Play();
}

void CEnglishLearningDlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	Record record ;
	CString tempstr;
	m_edit_no.GetWindowTextA(tempstr);
	record.no = atoi(tempstr);

	m_edit_starttime.GetWindowTextA(tempstr);
	record.starttime = atoi(tempstr);

	m_edit_endtime.GetWindowTextA(tempstr);
	record.endtime = atoi(tempstr);

	Config::WriteConfig(&record);

	MessageBox("保存成功","提示");
}


void CEnglishLearningDlg::OnBnClickedBtnReadConfig()
{
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码
	
	CString tempstr;
	m_edit_starttime.GetWindowTextA(tempstr);
	Seek(tempstr);
	Play();
	SetTimer(2,TIME_DELAY,NULL);
}


void CEnglishLearningDlg::OnBnClickedBtnStartRecording()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pAudio->StartRecording(this->m_hWnd);
	bRecording = TRUE;
	bEnding = FALSE;
}


void CEnglishLearningDlg::OnBnClickedBtnStopRecording()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!bPlaying)
	{
		return;
	}

	bEnding = TRUE;
	m_pAudio->StopPlaying();
}


void CEnglishLearningDlg::OnBnClickedBtnStopPlayingRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!bPlaying)
	{
		return;
	}

	bEnding = TRUE;
	m_pAudio->StopPlaying();
}


void CEnglishLearningDlg::OnBnClickedBtnPlayRecord()
{
	// TODO: 在此添加控件通知处理程序代码
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