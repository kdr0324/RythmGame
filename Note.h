#pragma once

const double sqrtnum = 0.70710678;
const int Centerx = 608;
const int Centery = 357;

class CNote
{
public:
	CNote();
	CNote(int start_tick, int direction, int shape);
	~CNote();
	void CNote_Draw(CClientDC CDC, CImage img, int cur_tick);
	void CNote_Draw_Black(CClientDC CDC, CImage img);
	void update_location(int cur_tick);
	


	int m_start_tick;
	int direction;
	int location;
	int shape;
private:
};

