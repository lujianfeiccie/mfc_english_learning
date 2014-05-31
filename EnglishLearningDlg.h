
// EnglishLearningDlg.h : 头文件
//

#pragma once

#include "MCIClass.h"
#include "MyAudioCls.h"
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 进度条
	CSliderCtrl m_slider;
	// 播放时间
	CStatic m_static_time;
	// 序号
	CEdit m_edit_no;
	// 开始播放时间
	CEdit m_edit_starttime;
	// 结束播放时间
	CEdit m_edit_endtime;
	//录音机
	CMyAudioCls* m_pAudio;
	BOOL bPlaying;
	BOOL bRecording;
	BOOL bEnding;
	BOOL bPaused;
	afx_msg void OnBnClickedBtnSaveConfig();

	afx_msg void OnBnClickedBtnReadConfig();
	afx_msg void OnBnClickedBtnSeek();
	afx_msg void OnBnClickedBtnStartRecording();
	afx_msg void OnBnClickedBtnStopRecording();
	afx_msg void OnBnClickedBtnStopPlayingRecord();
	afx_msg void OnBnClickedBtnPlayRecord();

	afx_msg LRESULT OnMM_WIM_OPEN(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WIM_DATA(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WIM_CLOSE(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_OPEN(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_DONE(UINT wParam, LONG lParam);
	afx_msg LRESULT OnMM_WOM_CLOSE(UINT wParam, LONG lParam);
	// 播放视频
	CButton m_btn_play;
	// 停止播放视频
	CButton m_btn_stop;
	// 开始录音
	CButton m_btn_start_record;
	// 停止录音
	CButton m_btn_stop_record;
	// 播放录音
	CButton m_btn_play_record;
	// 停止播放录音
	CButton m_btn_stop_play_record;
	afx_msg void OnDeltaposSpinNo(NMHDR *pNMHDR, LRESULT *pResult);
};
