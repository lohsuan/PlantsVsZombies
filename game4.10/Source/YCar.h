#ifndef YCAR_H
#define YCAR_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
//#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"

namespace game_framework {
	class YCar {
	public:
		YCar(int i) {
			x = 50;
			int a[5] = { 85, 182, 290, 390, 484 };
			y = a[i];			// i: 0~4
			is_alive = true;
		}
		void LoadBitmap() {
			car.LoadBitmap("Bitmaps/car.bmp", RGB(255,255,255));

		}
		void OnMove() {
			if (x < 950)
				x = x + 2;
			else
				is_alive = false;
		}
		void OnShow() {
			car.SetTopLeft(x, y+20);
			car.ShowBitmap();
		}

		bool IsAlive() {
			return is_alive;
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}

		int GetX() {
			return x;
		}
		int GetY() {
			return y;
		}

	private:
		int x;
		int y;
		bool is_alive;
		CMovingBitmap car;
	};

}


#endif