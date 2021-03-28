#ifndef YPLANTS_H
#define YPLANTS_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include "gamelib.h"
#include "YSun.h"

namespace game_framework {

	class YSunFlower
	{
	public:
		YSunFlower(int x, int y) {
			this->x = x;
			this->y = y;
			blood = 5;
			sun_make_time = 7;
			is_alive = true;
	
		}
		~YSunFlower() {

		}

		void LoadBitmap() {
			// try
			char *filename[8] = { ".\\bitmaps\\SunFlower_0.bmp",".\\bitmaps\\SunFlower_1.bmp"
				, ".\\bitmaps\\SunFlower_2.bmp",".\\bitmaps\\SunFlower_3.bmp"
				, ".\\bitmaps\\SunFlower_4.bmp",".\\bitmaps\\SunFlower_5.bmp"
				, ".\\bitmaps\\SunFlower_6.bmp",".\\bitmaps\\SunFlower_7.bmp"
			};
			for (int i = 0; i < 8; i++)
				sun_flower_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}

		void OnMove() {
			sun_flower_animation.OnMove();
		}

		void OnShow() {
			if (IsAlive()) {
				// try
				sun_flower_animation.SetTopLeft(x, y);
				sun_flower_animation.OnShow();
				//sun_flower_animation.ShowBitmap();
			}
		}
		bool IsAlive() {
			return is_alive;
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		int  GetX() {
			return x;
		}
		int  GetY() {
			return y;
		}
		void SetBlood(int attack_blood) {
			blood = blood - attack_blood;
		}
		int  GetBlood() {
			return blood;
		}
		/*void SetUp() {
			already_set_up = true;
		}*/

	private:
		int x, y;
		bool is_alive;
		int blood;
		int sun_make_time;

		// try
		CAnimation sun_flower_animation;
		//CMovingBitmap sun_flower_animation;

		//YSun	flower_sun;
	};

}

#endif

