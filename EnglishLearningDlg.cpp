
// EnglishLearningDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EnglishLearning.h"
#include "EnglishLearningDlg.h"
#include "afxdialogex.h"

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
}

void CEnglishLearningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_STATIC_TIME, m_static_time);
}

BEGIN_MESSAGE_MAP(CEnglishLearningDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_STOP, &CEnglishLearningDlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CEnglishLearningDlg::OnBnClickedBtnPlay)
	ON_COMMAND(ID_MENU_OPEN,&CEnglishLearningDlg::OnMenuOpenFile)
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
			SetTimer(1,500,NULL);
		}

		CString s = FileDlg.GetFileName();
		SetWindowTextA(s);
	}
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
	CDialog::OnTimer(nIDEvent);
}
void CEnglishLearningDlg::OnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	Stop();
	EndDialog(IDCANCEL);
	CDialog::OnClose();
}