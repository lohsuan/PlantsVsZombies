#ifndef YCARD_H
#define YCARD_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
//#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"

namespace game_framework {

	class YSunFlowerCard
	{
	public:
		YSunFlowerCard() {
			x = 83;
			y = 11;
			is_alive = false;
			cost = 50;
		}
		//void OnLButtonDown(UINT nFlags, CPoint point) {
		//	if (point.x > x  && point.y > y && point.x < x + 65 && point.y < y + 90) {
		//		is_alive = false;
		//	}
		//}
		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_sunflower_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_sunflower_die.bmp");

		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(83, 11);
			card_die.SetTopLeft(83, 11);
			if (is_alive == true) {
				card_alive.ShowBitmap();
			}
			else {
				card_die.ShowBitmap();
			}
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		int GetSunCost() {
			return cost;
		}
		int GetX() {
			return x;
		}
		int GetY() {
			return y;
		}
	private:
		CMovingBitmap card_alive;
		CMovingBitmap card_die;

		int  x, y;
		bool is_alive;
		int	 cost;
	};
}

#endif