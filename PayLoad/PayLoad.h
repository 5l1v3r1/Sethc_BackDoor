
// PayLoad.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPayLoadApp:
// �йش����ʵ�֣������ PayLoad.cpp
//

class CPayLoadApp : public CWinAppEx
{
public:
	CPayLoadApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPayLoadApp theApp;