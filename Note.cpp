#include "stdafx.h"
#include "Note.h"


CNote::CNote(){

}
CNote::CNote(int start_tick, int direction, int shape){
	this->m_start_tick = start_tick;
	this->direction = direction;
	this->shape = shape;
	this->location = 300;
}
CNote::~CNote(){

}

//CClientDC dc(this);
//
//CDC MemDC;
//MemDC.CreateCompatibleDC(&dc);
////m_Note[0].Draw(dc.m_hDC, 608+m_Score*15, 377, 65, 65);
//
//m_Note[0].Draw(dc.m_hDC, Centerx + 300 + m_Score*dif_x[2], Centery + m_Score*dif_y[2], 65, 65);
//m_Note[2].Draw(dc.m_hDC, Centerx - 300 + m_Score*dif_x[6], Centery + m_Score*dif_y[6], 65, 65);
////m_Note[3].Draw(dc.m_hDC, Centerx,Centery+300, 65, 65);
////m_Note[1].Draw(dc.m_hDC, Centerx,Centery-300,65, 65);
//m_Note[0].Draw(dc.m_hDC, Centerx + 212 + m_Score*dif_x[3], Centery + 212 + m_Score*dif_y[3], 65, 65);
//m_Note[2].Draw(dc.m_hDC, Centerx - 212 + m_Score*dif_x[7], Centery - 212 + m_Score*dif_y[7], 65, 65);
////m_Note[3].Draw(dc.m_hDC, Centerx-212, Centery + 212, 65, 65);
////m_Note[1].Draw(dc.m_hDC, Centerx+212, Centery - 212, 65, 65);
void CNote::CNote_Draw(CClientDC dc, CImage img, int cur_tick){

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	update_location(cur_tick); //update tick
	switch (direction){
	case 0:
		img.Draw(dc.m_hDC, Centerx, Centery + location, 65, 65);
		break;
	case 1:img.Draw(dc.m_hDC, Centerx + location, Centery + location, 65, 65); 
		break;
	case 2:img.Draw(dc.m_hDC, Centerx + location, Centery, 65, 65); 
		break;
	case 3:img.Draw(dc.m_hDC, Centerx + location, Centery - location, 65, 65); 
		break;
	case 4:img.Draw(dc.m_hDC, Centerx, Centery - location, 65, 65); 
		break;
	case 5:img.Draw(dc.m_hDC, Centerx - location, Centery - location, 65, 65); 
		break;
	case 6:img.Draw(dc.m_hDC, Centerx - location, Centery, 65, 65); 
		break;
	case 7:img.Draw(dc.m_hDC, Centerx - location, Centery + location, 65, 65);
		break;
	default:
		break;


	}
}
void CNote::CNote_Draw_Black(CClientDC dc, CImage img){
	CDC  MemDC;
	MemDC.CreateCompatibleDC(&dc);

	switch (direction){
	case 0:
		img.Draw(dc.m_hDC, Centerx, Centery + location, 65, 65);
		break;
	case 1:img.Draw(dc.m_hDC, Centerx + location, Centery + location, 65, 65);
		break;
	case 2:img.Draw(dc.m_hDC, Centerx + location, Centery, 65, 65);
		break;
	case 3:img.Draw(dc.m_hDC, Centerx + location, Centery - location, 65, 65);
		break;
	case 4:img.Draw(dc.m_hDC, Centerx, Centery - location, 65, 65);
		break;
	case 5:img.Draw(dc.m_hDC, Centerx - location, Centery - location, 65, 65);
		break;
	case 6:img.Draw(dc.m_hDC, Centerx - location, Centery, 65, 65);
		break;
	case 7:img.Draw(dc.m_hDC, Centerx - location, Centery + location, 65, 65);
		break;
	default:
		break;
	}
}

void CNote::update_location(int cur_tick)
{
	
	location = 305 - ( cur_tick - m_start_tick)*5 ;
	if (direction % 2 == 1) 
		location = sqrtnum * location;
}


