
// RhythmGameDlg.h : ��� ����
//

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include "afxwin.h"
#include "afxbutton.h"
#include "Note.h"
#pragma comment (lib,"winmm.lib")


// CRhythmGameDlg ��ȭ ����
class CRhythmGameDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CRhythmGameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RHYTHMGAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	//�Լ�
	void PutHPImg();	//ü�¹� ����
	void PutBKImg();
	void PutBlackImg();
	void PutScore();
	void initres();
	void initgame();
	void PutHPstate();
	void PutNote();
	void AddNote();
	void GetInput();
	void PutJudgement();
	void PutResult();
	void GetResult();
	void GetScore();
	void EraseNote();
	void EraseOneNote();
	void FileInputTest();
	void PutCombo();
	void PutJudge(int judge);
	// �����Դϴ�.
protected:
	HICON m_hIcon;

	//Bitmap
	CBitmap m_Hp;						// ü�¹�
	CBitmap m_Black;						// ���
	CImage m_Hpbar;
	CImage m_Bkimg;
	CImage m_Hpstate;
	CImage m_Scr[10];
	CImage m_Scoreletter;
	CImage m_Note[5];
	CImage m_judgement;
	CImage m_Result;
	CImage m_Clear;
	CImage m_Judge[4];
	CImage m_Combo;
	CImage m_ComboNumber[10];

	//
	int m_Score;	//���ھ�
	int m_Life;
	int m_Perfect;
	int m_Great;
	int m_Good;
	int m_Miss;
	int m_tick;
	int m_direction;
	int m_ComboCount;

	int m_TotalNote;
	int m_TotalTick;
	char * NoteList;

	double dif_x[8];
	double dif_y[8];
	//
	DWORD m_dwID;
	MCI_OPEN_PARMS m_mciOpen;
	MCI_PLAY_PARMS m_mciPlay;

	std::list<CNote *> L_Note;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CImage m_ButtonImage;
	CImage m_SongImage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CMFCButton m_StartButton;
	CMFCButton m_SongButton;
	//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
