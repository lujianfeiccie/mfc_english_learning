
// EnglishLearning.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEnglishLearningApp:
// �йش����ʵ�֣������ EnglishLearning.cpp
//

class CEnglishLearningApp : public CWinApp
{
public:
	CEnglishLearningApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEnglishLearningApp theApp;