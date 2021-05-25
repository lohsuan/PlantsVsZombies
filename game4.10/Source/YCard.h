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

	class YPeaShooterCard
	{
	public:
		YPeaShooterCard() {
			x = 137;
			y = 11;
			is_alive = false;
			cost = 100;
		}
		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_peashooter_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_peashooter_die.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(137, 11);
			card_die.SetTopLeft(137, 11);
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

	class YWallNutCard
	{
	public:
		YWallNutCard() {
			x = 191;
			y = 11;
			is_alive = false;
			cost = 50;
		}

		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_wallnut_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_wallnut_die.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(x, y);
			card_die.SetTopLeft(x, y);
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

	class YCherryBombCard
	{
	public:
		YCherryBombCard() {
			x = 191 + 54;
			y = 11;
			is_alive = false;
			cost = 150;
		}
		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_cherrybomb_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_cherrybomb_die.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(x, y);
			card_die.SetTopLeft(x, y);
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

	class YIceShooterCard
	{
	public:
		YIceShooterCard() {
			x = 299;
			y = 11;
			is_alive = false;
			cost = 175;
		}
		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_snowpea_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_snowpea_die.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(x, y);
			card_die.SetTopLeft(x, y);
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

	class YPotatomineCard
	{
	public:
		YPotatomineCard() {
			x = 299 + 54;
			y = 11;
			is_alive = false;
			cost = 25;
		}
		bool IsAlive() {
			return is_alive;
		}
		void LoadBitmap() {
			card_alive.LoadBitmap("Bitmaps/cards/card_potatomine_alive.bmp");
			card_die.LoadBitmap("Bitmaps/cards/card_potatomine_die.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card_alive.SetTopLeft(x, y);
			card_die.SetTopLeft(x, y);
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

	class YShovelCard
	{
	public:
		YShovelCard() {
			x = 520;
			y = 0;
			is_alive = true;
			//cost = 0;
		}

		void LoadBitmap() {
			card.LoadBitmap("Bitmaps/Shovel.bmp");
			card_die.LoadBitmap("Bitmaps/Shovel1.bmp");
		}
		void OnMove() {

		}
		void OnShow() {
			card.SetTopLeft(520, 0);
			card_die.SetTopLeft(520, 0);
			if (is_alive == true) {
				card.ShowBitmap();
			}
			else {
				card_die.ShowBitmap();
			}
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		/*int GetSunCost() {
			return cost;
		}*/
		int GetX() {
			return x;
		}
		int GetY() {
			return y;
		}
	private:
		CMovingBitmap card;
		CMovingBitmap card_die;
		int  x, y;
		bool is_alive;
		//int	 cost;
	};

}

#endif