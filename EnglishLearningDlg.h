
// EnglishLearningDlg.h : ͷ�ļ�
//

#pragma once

#include "MCIClass.h"
#include "MyAudioCls.h"
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ������
	CSliderCtrl m_slider;
	// ����ʱ��
	CStatic m_static_time;
	// ���
	CEdit m_edit_no;
	// ��ʼ����ʱ��
	CEdit m_edit_starttime;
	// ��������ʱ��
	CEdit m_edit_endtime;
	//¼����
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
	// ������Ƶ
	CButton m_btn_play;
	// ֹͣ������Ƶ
	CButton m_btn_stop;
	// ��ʼ¼��
	CButton m_btn_start_record;
	// ֹͣ¼��
	CButton m_btn_stop_record;
	// ����¼��
	CButton m_btn_play_record;
	// ֹͣ����¼��
	CButton m_btn_stop_play_record;
	afx_msg void OnDeltaposSpinNo(NMHDR *pNMHDR, LRESULT *pResult);
};
