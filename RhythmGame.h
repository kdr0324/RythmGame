
// RhythmGame.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRhythmGameApp:
// �� Ŭ������ ������ ���ؼ��� RhythmGame.cpp�� �����Ͻʽÿ�.
//

class CRhythmGameApp : public CWinApp
{
public:
	CRhythmGameApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRhythmGameApp theApp;