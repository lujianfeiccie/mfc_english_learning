
// EnglishLearningDlg.h : ͷ�ļ�
//

#pragma once

#include "MCIClass.h"
#include "afxwin.h"
#include "afxcmn.h"
// CEnglishLearningDlg �Ի���
class CEnglishLearningDlg : public CDialogEx,protected CMCIClass
{
// ����
public:
	CEnglishLearningDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ENGLISHLEARNING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOk();  
	virtual void OnCancel(); 

	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnMenuOpenFile();
	// ������
	CSliderCtrl m_slider;
	// ����ʱ��
	CStatic m_static_time;
};
