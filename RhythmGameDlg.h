
// RhythmGameDlg.h : 헤더 파일
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


// CRhythmGameDlg 대화 상자
class CRhythmGameDlg : public CDialogEx
{
	// 생성입니다.
public:
	CRhythmGameDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RHYTHMGAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	//함수
	void PutHPImg();	//체력바 생성
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
	// 구현입니다.
protected:
	HICON m_hIcon;

	//Bitmap
	CBitmap m_Hp;						// 체력바
	CBitmap m_Black;						// 배경
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
	int m_Score;	//스코어
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

	// 생성된 메시지 맵 함수
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
