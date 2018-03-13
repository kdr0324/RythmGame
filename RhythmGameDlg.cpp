
// RhythmGameDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RhythmGame.h"
#include "RhythmGameDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PERFECT 0
#define GREAT 1
#define GOOD 2
#define MISS 3


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CRhythmGameDlg 대화 상자



CRhythmGameDlg::CRhythmGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRhythmGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRhythmGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_StartButton);
	DDX_Control(pDX, IDC_SONG, m_SongButton);
}

BEGIN_MESSAGE_MAP(CRhythmGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CRhythmGameDlg 메시지 처리기
int dwID;

BOOL CRhythmGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srand((unsigned)time(NULL));
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_mciOpen.lpstrElementName = L"Kalimba.mp3";
	m_mciOpen.lpstrDeviceType = L"mpegvideo";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&m_mciOpen);

	m_dwID = m_mciOpen.wDeviceID;
	mciSendCommand(m_dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)&m_mciPlay);

	initres();
	initgame();
	FileInputTest();

	SetTimer(0, 10, NULL);	//33

	HBITMAP hBit1, hBit2;
	hBit1 = m_ButtonImage.Detach();
	hBit2 = m_SongImage.Detach();
	//	m_StartButton.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_StartButton.m_bTransparent = TRUE;
	m_StartButton.m_bDrawFocus = FALSE;
	m_StartButton.SetImage(hBit1, TRUE, NULL);
	m_SongButton.m_bTransparent = TRUE;
	m_SongButton.m_bDrawFocus = FALSE;
	m_SongButton.SetImage(hBit2, TRUE, NULL);

	m_StartButton.SetWindowText(_T(""));
	m_SongButton.SetWindowText(_T(""));

	m_Hp.LoadBitmap(IDB_HP);
	m_Black.LoadBitmap(IDB_BKIMG);

	SetWindowPos(NULL, 0, 0, 1280, 818, SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
	CenterWindow(GetDesktopWindow());
	ShowWindow(SW_SHOW);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRhythmGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRhythmGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		PutBlackImg();
		PutBKImg();
		PutScore();
		PutHPImg();
		PutJudgement();
		PutResult();
		PutHPstate();
		GetScore();
		GetResult();
		PutNote();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRhythmGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CRhythmGameDlg::initres()
{
	m_Hpbar.Load(_T("res\\HP_inv.png"));
	m_Bkimg.Load(_T("res\\bkimg.png"));
	m_Scoreletter.Load(_T("res\\Score.png"));
	m_Scr[0].Load(_T("res\\0_char.png"));
	m_Scr[1].Load(_T("res\\1_char.png"));
	m_Scr[2].Load(_T("res\\2_char.png"));
	m_Scr[3].Load(_T("res\\3_char.png"));
	m_Scr[4].Load(_T("res\\4_char.png"));
	m_Scr[5].Load(_T("res\\5_char.png"));
	m_Scr[6].Load(_T("res\\6_char.png"));
	m_Scr[7].Load(_T("res\\7_char.png"));
	m_Scr[8].Load(_T("res\\8_char.png"));
	m_Scr[9].Load(_T("res\\9_char.png"));
	m_Hpstate.Load(_T("res\\HP_state.png"));
	m_Note[0].Load(_T("res\\note_up.png"));
	m_Note[1].Load(_T("res\\note_down.png"));
	m_Note[2].Load(_T("res\\note_left.png"));
	m_Note[3].Load(_T("res\\note_right.png"));
	m_Note[4].Load(_T("res\\9_char.png"));
	m_judgement.Load(_T("res\\note_center3.png"));
	m_Result.Load(_T("res\\Check.png"));
	m_Clear.Load(_T("res\\Clear.png"));
	m_ButtonImage.Load(_T("res\\Start.png"));
	m_SongImage.Load(_T("res\\Song_select.png"));
	m_Judge[0].Load(_T("res\\Perfect.png"));
	m_Judge[1].Load(_T("res\\Great.png"));
	m_Judge[2].Load(_T("res\\Good.png"));
	m_Judge[3].Load(_T("res\\Miss.png"));
	m_Combo.Load(_T("res\\Combo.png"));
	m_ComboNumber[0].Load(_T("res\\combo_0.png"));
	m_ComboNumber[1].Load(_T("res\\combo_1.png"));
	m_ComboNumber[2].Load(_T("res\\combo_2.png"));
	m_ComboNumber[3].Load(_T("res\\combo_3.png"));
	m_ComboNumber[4].Load(_T("res\\combo_4.png"));
	m_ComboNumber[5].Load(_T("res\\combo_5.png"));
	m_ComboNumber[6].Load(_T("res\\combo_6.png"));
	m_ComboNumber[7].Load(_T("res\\combo_7.png"));
	m_ComboNumber[8].Load(_T("res\\combo_8.png"));
	m_ComboNumber[9].Load(_T("res\\combo_9.png"));
}
void CRhythmGameDlg::initgame(){
	m_Score = 0;
	m_Life = 30;
	m_Perfect = 0;
	m_Great = 0;
	m_Good = 0;
	m_Miss = 0;
	m_tick = 0;
	m_ComboCount = 0;
	m_direction = 0;
	dif_x[0] = 0; dif_x[1] = -sqrt(2) / 2; dif_x[2] = -1; dif_x[3] = -sqrt(2) / 2;
	dif_x[4] = 0; dif_x[5] = sqrt(2) / 2; dif_x[6] = 1; dif_x[7] = sqrt(2) / 2;
	dif_y[0] = 1; dif_y[1] = sqrt(2) / 2; dif_y[2] = 0; dif_y[3] = -sqrt(2) / 2;
	dif_y[4] = -1; dif_y[5] = -sqrt(2) / 2; dif_y[6] = 0; dif_y[7] = sqrt(2) / 2;
}
void CRhythmGameDlg::PutBlackImg()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap* pOldBitmap = MemDC.SelectObject(&m_Black);
	dc.BitBlt(0, 0, 1280, 800, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}
void CRhythmGameDlg::PutJudgement()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_judgement.Draw(dc.m_hDC, Centerx, Centery, 65, 65);


}
void CRhythmGameDlg::PutNote()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	//m_Note[0].Draw(dc.m_hDC, Centerx + 300 + m_Score*dif_x[2], Centery + m_Score*dif_y[2], 65, 65);

	if (L_Note.empty() != TRUE && L_Note.front()->location <= 0){
		L_Note.pop_front();
		m_Miss++;
		m_ComboCount = 0;
		PutJudge(MISS);
		m_Life--;
	}

	std::list<CNote*>::iterator iter;
	for (iter = L_Note.begin(); iter != L_Note.end(); iter++){
		(*iter)->update_location(m_tick);
		int location = (*iter)->location;
		switch ((*iter)->direction){
		case 0:
			m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx, Centery + location, 65, 65);
			break;
		case 1:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx + location, Centery + location, 65, 65);
			break;
		case 2:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx + location, Centery, 65, 65);
			break;
		case 3:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx + location, Centery - location, 65, 65);
			break;
		case 4:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx, Centery - location, 65, 65);
			break;
		case 5:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx - location, Centery - location, 65, 65);
			break;
		case 6:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx - location, Centery, 65, 65);
			break;
		case 7:m_Note[(*iter)->shape].Draw(dc.m_hDC, Centerx - location, Centery + location, 65, 65);
			break;
		default:
			break;
		}
	}


	////m_Note[0].Draw(dc.m_hDC, 608+m_Score*15, 377, 65, 65);
	//m_Note[0].Draw(dc.m_hDC, Centerx + 300 + m_Score*dif_x[2], Centery + m_Score*dif_y[2], 65, 65);
	//m_Note[2].Draw(dc.m_hDC, Centerx - 300 + m_Score*dif_x[6], Centery + m_Score*dif_y[6], 65, 65);
	////m_Note[3].Draw(dc.m_hDC, Centerx,Centery+300, 65, 65);
	////m_Note[1].Draw(dc.m_hDC, Centerx,Centery-300,65, 65);
	//m_Note[0].Draw(dc.m_hDC, Centerx + 212 + m_Score*dif_x[3], Centery + 212 + m_Score*dif_y[3], 65, 65);
	//m_Note[2].Draw(dc.m_hDC, Centerx - 212 + m_Score*dif_x[7], Centery - 212 + m_Score*dif_y[7], 65, 65);
	////m_Note[3].Draw(dc.m_hDC, Centerx-212, Centery + 212, 65, 65);
	////m_Note[1].Draw(dc.m_hDC, Centerx+212, Centery - 212, 65, 65);
	////m_Clear.Draw(dc.m_hDC, 908, 377, 65, 65);

	/*
	908 409
	308 409
	640 677
	640 77
	*/
}
void CRhythmGameDlg::EraseNote()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	std::list<CNote*>::iterator iter;
	for (iter = L_Note.begin(); iter != L_Note.end(); iter++){
		int location = (*iter)->location;
		switch ((*iter)->direction){
		case 0:
			m_Clear.Draw(dc.m_hDC, Centerx, Centery + location, 65, 65);
			break;
		case 1:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery + location, 65, 65);
			break;
		case 2:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery, 65, 65);
			break;
		case 3:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery - location, 65, 65);
			break;
		case 4:m_Clear.Draw(dc.m_hDC, Centerx, Centery - location, 65, 65);
			break;
		case 5:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery - location, 65, 65);
			break;
		case 6:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery, 65, 65);
			break;
		case 7:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery + location, 65, 65);
			break;
		default:
			break;
		}
	}
}
void CRhythmGameDlg::PutBKImg()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_Bkimg.Draw(dc.m_hDC, 0, 0, 1280, 780);
}
void CRhythmGameDlg::PutHPImg()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_Hpbar.Draw(dc.m_hDC, 20, 50, 40, 601);
}
void CRhythmGameDlg::PutHPstate()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	if (m_Life > 30) m_Life = 30;
	if (m_Life < 0) m_Life = 0;
	m_Hpstate.Draw(dc.m_hDC, 20, 650 - 20 * m_Life, 40, 10);
}
void CRhythmGameDlg::PutCombo()
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	int c[3];

	for (int i = 0; i < 3; i++){
		c[i] = m_ComboCount / (int)pow(10.0, i) % (int)pow(10.0, 1);
	}
	m_Clear.Draw(dc.m_hDC, Centerx - 130, Centery - 200, 300, 90);
	m_Combo.Draw(dc.m_hDC, Centerx - 130, Centery - 200, 300, 90);
	for (int i = 0; i < 3; i++){
		m_Clear.Draw(dc.m_hDC, (Centerx - 70) + i * 60, Centery - 100, 60, 90);
		m_ComboNumber[c[2 - i]].Draw(dc.m_hDC, (Centerx - 70) + i * 60, Centery - 100, 60, 90);
	}

}
void CRhythmGameDlg::PutJudge(int judge)
{
	CClientDC dc(this);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	// 0 1 2 3
	// E G g M
	m_Clear.Draw(dc.m_hDC, Centerx - 80, Centery + 200, 200, 70);
	m_Judge[judge].Draw(dc.m_hDC, Centerx - 80, Centery + 200, 200, 70);
}
void CRhythmGameDlg::PutScore()
{
	CClientDC dc(this);
	CDC MemDC;
	m_Scoreletter.Draw(dc.m_hDC, 1050, 50, 180, 50);
}
void CRhythmGameDlg::PutResult(){
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_Result.Draw(dc.m_hDC, 1050, 150, 100, 105);

	m_Clear.Draw(dc.m_hDC, 1150, 150, 20, 30);
	m_Clear.Draw(dc.m_hDC, 1150, 175, 20, 30);
	m_Clear.Draw(dc.m_hDC, 1150, 200, 20, 30);
	m_Clear.Draw(dc.m_hDC, 1150, 225, 20, 30);

}
void CRhythmGameDlg::GetResult(){
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	int p[3], G[3], g[3], m[3];
	for (int i = 0; i < 3; i++){
		p[i] = m_Perfect / (int)pow(10.0, i) % (int)pow(10.0, 1);
		G[i] = m_Great / (int)pow(10.0, i) % (int)pow(10.0, 1);
		g[i] = m_Good / (int)pow(10.0, i) % (int)pow(10.0, 1);
		m[i] = m_Miss / (int)pow(10.0, i) % (int)pow(10.0, 1);
	}
	for (int i = 0; i < 3; i++){
		m_Scr[p[2 - i]].Draw(dc.m_hDC, 1150 + (i + 1) * 20, 150, 20, 30);
		m_Scr[G[2 - i]].Draw(dc.m_hDC, 1150 + (i + 1) * 20, 175, 20, 30);
		m_Scr[g[2 - i]].Draw(dc.m_hDC, 1150 + (i + 1) * 20, 200, 20, 30);
		m_Scr[m[2 - i]].Draw(dc.m_hDC, 1150 + (i + 1) * 20, 225, 20, 30);
	}
}
void CRhythmGameDlg::GetScore(){
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	int temp = 100000 / m_TotalNote;
	int tm1, tm2, tm3;
	tm1 = temp * m_Perfect * 1;
	tm2 = temp * m_Great * 0.7;
	tm3 = temp * m_Good * 0.3;
	m_Score = tm1 + tm2 + tm3;

	int d[6];

	for (int i = 0; i < 6; i++){
		d[i] = m_Score / (int)pow(10.0, i) % (int)pow(10.0, 1);
	}

	for (int i = 0; i < 6; i++){
		m_Scr[d[5 - i]].Draw(dc.m_hDC, 1050 + i * 30, 100, 30, 50);
	}
}
void CRhythmGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnTimer(nIDEvent);
	EraseNote();
	m_tick++;
	PutJudgement();
	AddNote();
	PutHPImg();
	PutHPstate();
	PutCombo();
	PutNote();
	GetScore();
	GetResult();
}
void CRhythmGameDlg::FileInputTest(){
	FILE *fp;
	char ch;
	int j = 0;
	CNote * nt;

	fp = fopen("Kalimba.txt", "rt");
	fscanf(fp, "%d", &m_TotalTick);
	fscanf(fp, "%d", &m_TotalNote);
	NoteList = new char[m_TotalTick];
	ch = fgetc(fp);
	for (int j = 0; j < m_TotalTick; j++){
		fscanf(fp, "%c", &ch);
		NoteList[j] = ch;
	}

	fclose(fp);
}

void CRhythmGameDlg::AddNote(){
	if (NoteList[m_tick] != '4'){
		L_Note.push_back(new CNote(m_tick, m_direction++ % 8, rand() % 4));
	}
}
BOOL CRhythmGameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN){
		CNote * Last_Note = L_Note.front();
		if (L_Note.empty() != TRUE){
			if (pMsg->wParam == VK_UP){
				if (Last_Note->shape == 0){
					if (Last_Note->location <= 10){
						EraseOneNote();
						L_Note.pop_front();
						m_Perfect++;
						m_ComboCount++;
						PutJudge(PERFECT);
						m_Life++;
					}
					else if (Last_Note->location <= 20){
						EraseOneNote();
						L_Note.pop_front();
						m_Great++;
						m_ComboCount++;
						PutJudge(GREAT);
						m_Life++;
					}
					else if (Last_Note->location <= 30){
						EraseOneNote();
						L_Note.pop_front();
						m_Good++;
						m_ComboCount++;
						PutJudge(GOOD);
						m_Life++;
					}
					else if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
					else{
					}
				}
				else{
					if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
				}
				PutCombo();
			}
			else if (pMsg->wParam == VK_DOWN){
				if (Last_Note->shape == 1){
					if (Last_Note->location <= 10){
						EraseOneNote();
						L_Note.pop_front();
						m_Perfect++;
						m_ComboCount++;
						PutJudge(PERFECT);
						m_Life++;
					}
					else if (Last_Note->location <= 20){
						EraseOneNote();
						L_Note.pop_front();
						m_Great++;
						m_ComboCount++;
						PutJudge(GREAT);
						m_Life++;
					}
					else if (Last_Note->location <= 30){
						EraseOneNote();
						L_Note.pop_front();
						m_Good++;
						m_ComboCount++;
						PutJudge(GOOD);
						m_Life++;
					}
					else if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
					else{
					}
				}
				else{
					if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
				}
				PutCombo();
			}
			else if (pMsg->wParam == VK_LEFT){
				if (Last_Note->shape == 2){
					if (Last_Note->location <= 10){
						EraseOneNote();
						L_Note.pop_front();
						m_Perfect++;
						m_ComboCount++;
						PutJudge(PERFECT);
						m_Life++;
					}
					else if (Last_Note->location <= 20){
						EraseOneNote();
						L_Note.pop_front();
						m_Great++;
						m_ComboCount++;
						PutJudge(GREAT);
						m_Life++;
					}
					else if (Last_Note->location <= 30){
						EraseOneNote();
						L_Note.pop_front();
						m_Good++;
						m_ComboCount++;
						PutJudge(GOOD);
						m_Life++;
					}
					else if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
					else{
					}
				}
				else{
					if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
				}
				PutCombo();
			}
			else if (pMsg->wParam == VK_RIGHT){
				if (Last_Note->shape == 3){
					if (Last_Note->location <= 10){
						EraseOneNote();
						L_Note.pop_front();
						m_Perfect++;
						m_ComboCount++;
						PutJudge(PERFECT);
						m_Life++;
					}
					else if (Last_Note->location <= 20){
						EraseOneNote();
						L_Note.pop_front();
						m_Great++;
						m_ComboCount++;
						PutJudge(GREAT);
						m_Life++;
					}
					else if (Last_Note->location <= 30){
						EraseOneNote();
						L_Note.pop_front();
						m_Good++;
						m_ComboCount++;
						PutJudge(GOOD);
						m_Life++;
					}
					else if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
					else{
					}
				}
				else{
					if (Last_Note->location <= 40){
						EraseOneNote();
						L_Note.pop_front();
						m_Miss++;
						m_ComboCount = 0;
						PutJudge(MISS);
						m_Life--;
					}
				}
				PutCombo();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CRhythmGameDlg::EraseOneNote()
{
	CClientDC dc(this);
	int location;

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CNote * Last_Note = L_Note.front();
	location = Last_Note->location;

	switch (Last_Note->direction){
	case 0:
		m_Clear.Draw(dc.m_hDC, Centerx, Centery + location, 65, 65);
		break;
	case 1:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery + location, 65, 65);
		break;
	case 2:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery, 65, 65);
		break;
	case 3:m_Clear.Draw(dc.m_hDC, Centerx + location, Centery - location, 65, 65);
		break;
	case 4:m_Clear.Draw(dc.m_hDC, Centerx, Centery - location, 65, 65);
		break;
	case 5:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery - location, 65, 65);
		break;
	case 6:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery, 65, 65);
		break;
	case 7:m_Clear.Draw(dc.m_hDC, Centerx - location, Centery + location, 65, 65);
		break;
	default:
		break;
	}
}