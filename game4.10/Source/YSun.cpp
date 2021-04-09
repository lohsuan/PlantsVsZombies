#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"
#include "YSun.h"

namespace game_framework {
	///////////////////////////////////////////////////////////////
	// YSun: Sun class
	///////////////////////////////////////////////////////////////

	YSun::YSun() {
		srand((int)time(NULL));
		x = (rand() % 650) + 100;		// 100~750
		y = -150;
		floor = (rand() % 250) + 250;	//250~500
		is_alive = true;
	}

	void YSun::OnLButtonDown(UINT nFlags, CPoint point) {
		if (point.x > x - 5 && point.y - 5 > y && point.x < x + 80 && point.y < y + 80) {
			is_alive = false;

		}
	}

	bool YSun::IsAlive() {
		return is_alive;
	}

	void YSun::LoadBitmap() {
		char *filename[8] = { ".\\bitmaps\\Sun\\sun0.bmp",".\\bitmaps\\Sun\\sun1.bmp",".\\bitmaps\\Sun\\sun2.bmp",".\\bitmaps\\Sun\\sun3.bmp"
		, ".\\bitmaps\\Sun\\sun4.bmp",".\\bitmaps\\Sun\\sun5.bmp",".\\bitmaps\\Sun\\sun6.bmp",".\\bitmaps\\Sun\\sun7.bmp"
		};
		
		for (int i = 0; i < 8; i++)
			sunanimation.AddBitmap(filename[i], RGB(255, 255, 255));
	}

	void YSun::OnMove() {
		/*if (!is_alive)
			return;*/
		if (GetY() > 0) {
			SetIsAlive(true);
		}
		if (GetY() < GetFloor())
			y = y + 2;

		sunanimation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}

	void YSun::OnShow() {
		if (IsAlive()) {
			sunanimation.SetTopLeft(x, y);
			sunanimation.OnShow();
		}
	}

	void YSun::SetIsAlive(bool alive) {
		is_alive = alive;
	}

	void YSun::SetY(int y) {
		srand((int)time(NULL));
		x = (rand() % 550) + 200;		// 200~750
		this->y = y;
		floor = (rand() % 250) + 250;	//250~500
	}

	int YSun::GetX() {
		return x;
	}

	int YSun::GetY() {
		return y;
	}

	int	YSun::GetFloor() {
		return floor;
	}
	//CMovingBitmap sun;			// �y����
	//int x, y;					// ��ߪ��y��
	//bool is_alive;
}

