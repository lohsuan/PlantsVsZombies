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
		sunflowerflag = false;
	}
	YSun::YSun(int x, int y) {
		this->x = x;
		this->y = y;
		floor = y + 45;
		is_alive = false;
		sunflowerflag = true;
		rising = true;
		velocity = 10;
	}

	YSun &  YSun::operator= (const YSun & other) {
		if (this != &other) {
			this->x = other.x;
			this->y = other.y;
			this->floor = other.floor;
			this->is_alive = other.is_alive;
			this->sunflowerflag = other.sunflowerflag;
			this->velocity = other.velocity;
			this->rising = other.rising;
		}
		return *this;

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
		if (sunflowerflag) {
			if (rising) {			// 上升狀態
				if (velocity > 0) {
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
					velocity--;		// 受重力影響，下次的上升速度降低
					x += 1;
				}
				else {
					rising = false; // 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;	// 下降的初速(velocity)為1
					x += 1;
				}
			}
			else {				// 下降狀態
				if (y < floor - 1) {  // 當y座標還沒碰到地板
					y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
					velocity++;		// 受重力影響，下次的下降速度增加
					x += 1;
				}
			}
		}
		if (!sunflowerflag && GetY() > 0) {
			SetIsAlive(true);
		}
		if (!sunflowerflag && GetY() < GetFloor())
			y = y + 2;

		sunanimation.OnMove();
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

	int YSun::GetSunFlowerSunX() {
		return x;
	}
	int YSun::GetSunFlowerSunY() {
		return y;
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

}

