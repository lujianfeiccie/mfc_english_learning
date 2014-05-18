
// EnglishLearningDlg.h : 头文件
//

#pragma once

#include "MCIClass.h"
#include "afxwin.h"
#include "afxcmn.h"
// CEnglishLearningDlg 对话框
class CEnglishLearningDlg : public CDialogEx,protected CMCIClass
{
// 构造
public:
	CEnglishLearningDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ENGLISHLEARNING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 进度条
	CSliderCtrl m_slider;
	// 播放时间
	CStatic m_static_time;
};
