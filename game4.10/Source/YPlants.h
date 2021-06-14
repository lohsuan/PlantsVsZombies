#ifndef YPLANTS_H
#define YPLANTS_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include "gamelib.h"
#include "YSun.h"
#include "YZombies.h"

namespace game_framework {

	class YSunFlower
	{
	public:
		YSunFlower(int x, int y) {
			this->x = x + 8;
			this->y = y + 13;
			blood = 300;
			sun_make_time = 60 * 5;
			is_alive = true;
			YSun temp(this->x, this->y);
			sun = temp;
			sun.LoadBitmap();
		}
		~YSunFlower() {
		}
		void LoadBitmap() {
			char *filename[5] = { ".\\bitmaps\\SunFlower\\SunFlower_0.bmp",".\\bitmaps\\SunFlower\\SunFlower_1.bmp"
				, ".\\bitmaps\\SunFlower\\SunFlower_2.bmp"
				, ".\\bitmaps\\SunFlower\\SunFlower_4.bmp"
				,".\\bitmaps\\SunFlower\\SunFlower_7.bmp"
			};
			for (int i = 0; i < 5; i++)
				sun_flower_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		void OnMove() {
			if (sun_make_time > 0) {
				sun_make_time--;
			}
			else {
				sun.OnMove();
				sun.SetIsAlive(true);
			}
			sun_flower_animation.OnMove();
		}
		void OnShow() {
			if (IsAlive()) {
				sun_flower_animation.SetTopLeft(x, y);
				sun_flower_animation.OnShow();
			}
			if (sun_make_time > 0) {
				sun_make_time--;
			}
			else {
				sun.OnShow();
			}
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 13) {
				if (x > zx - 72 && x < zx - 48) {
					return true;
				}
			}
			return false;
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
		bool GetSunIsAlive() {
			return sun.IsAlive();
		}
		int GetSunX() {
			return sun.GetSunFlowerSunX();
		}
		int GetSunY() {
			return sun.GetSunFlowerSunY();
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		int  GetBlood() {
			return blood;
		}
		void initSun() {
			sun.SetIsAlive(false);
			sun_make_time = 60 * 7;
			YSun temp(this->x, this->y);
			sun = temp;
			sun.LoadBitmap();
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		int sun_make_time;
		CAnimation sun_flower_animation;
		YSun sun;
	};

	class YPeaShooterBullet {
	public:
		YPeaShooterBullet(int x, int y) {
			this->x = x + 30;
			this->y = y;
			is_alive = true;
		}

		void LoadBitmap()
		{
			peashooter_bullet.LoadBitmap(".\\bitmaps\\PeaShooter\\PeaNormal_0.bmp", RGB(255, 255, 255));
		}
		void OnMove()
		{
			x += 7;
			if (x > 800) {
				is_alive = false;
			};
		}

		void OnShow()
		{
			if (is_alive)
			{
				peashooter_bullet.SetTopLeft(x, y);
				peashooter_bullet.ShowBitmap();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}

		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}

	private:
		int x, y;
		bool is_alive;
		CMovingBitmap peashooter_bullet;
	};

	class YPeaShooter
	{
	public:
		YPeaShooter(int x, int y)
		{
			delay = 30;
			this->x = x + 20;
			this->y = y + 20;
			blood = 300;
			is_alive = true;
		}
		~YPeaShooter()
		{
		}
		void LoadBitmap()
		{
			char *filename[5] = { ".\\bitmaps\\PeaShooter\\PeaShooter_1.bmp", ".\\bitmaps\\PeaShooter\\PeaShooter_2.bmp", ".\\bitmaps\\PeaShooter\\PeaShooter_3.bmp", ".\\bitmaps\\PeaShooter\\PeaShooter_4.bmp", ".\\bitmaps\\PeaShooter\\PeaShooter_5.bmp" };
			for (int i = 0; i < 5; i++)
				peashooter_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		void OnMove()
		{
			peashooter_animation.OnMove();

			if (delay == 0) {
				fireBullet();
				delay = 80;
			}
			delay--;

			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnMove();
				else {
					bullets_vector.erase(bullets_vector.begin() + i);
				}
			}

		}
		void OnShow()
		{
			if (is_alive)
			{
				peashooter_animation.SetTopLeft(x, y);
				peashooter_animation.OnShow();
			}
			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnShow();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		void SetBlood(int attack_blood)
		{
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		int GetBlood()
		{
			return blood;
		}
		void fireBullet() {
			auto sp = make_shared<YPeaShooterBullet>(x, y);
			sp->LoadBitmap();
			bullets_vector.push_back(sp);
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		bool checkBulletCollideWithZombie(int zx, int mapy) {
			int by;
			if (!bullets_vector.empty()) {

				by = bullets_vector.at(0)->GetY() - 20;
			}
			if (!bullets_vector.empty() && bullets_vector.at(0)->GetY() - 20 == mapy) {
				int t = bullets_vector.at(0)->GetX();
				if (bullets_vector.at(0)->GetX() > zx + 20 && bullets_vector.at(0)->GetX() < zx + 80) {
					bullets_vector.at(0)->SetIsAlive(false);
					return true;
				}
			}
			return false;
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 60 && x < zx - 35) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		std::vector<shared_ptr<YPeaShooterBullet>> bullets_vector;
		CAnimation peashooter_animation;
		int delay;
	};

	class YWallNut
	{
	public:
		YWallNut(int x, int y)
		{
			this->x = x + 20;
			this->y = y + 20;
			blood = 600;
			is_alive = true;
		}
		~YWallNut()
		{
		}
		void LoadBitmap()
		{
			char *filename[4] = { ".\\bitmaps\\WallNut\\WallNut\\WallNut_0.bmp", ".\\bitmaps\\WallNut\\WallNut\\WallNut_2.bmp", ".\\bitmaps\\WallNut\\WallNut\\WallNut_3.bmp",
				".\\bitmaps\\WallNut\\WallNut\\WallNut_4.bmp" };
			for (int i = 0; i < 4; i++)
				wallnut_animation.AddBitmap(filename[i], RGB(255, 255, 255));
			char *filename1[4] = { ".\\bitmaps\\WallNut\\WallNut_cracked1\\WallNut_cracked1_0.bmp", ".\\bitmaps\\WallNut\\WallNut_cracked1\\WallNut_cracked1_2.bmp", ".\\bitmaps\\WallNut\\WallNut_cracked1\\WallNut_cracked1_3.bmp",
				".\\bitmaps\\WallNut\\WallNut_cracked1\\WallNut_cracked1_4.bmp"};
			for (int i = 0; i < 4; i++)
				wallnut_cracked1_animation.AddBitmap(filename1[i], RGB(255, 255, 255));
			char *filename2[4] = { ".\\bitmaps\\WallNut\\WallNut_cracked2\\WallNut_cracked2_0.bmp", ".\\bitmaps\\WallNut\\WallNut_cracked2\\WallNut_cracked2_2.bmp", ".\\bitmaps\\WallNut\\WallNut_cracked2\\WallNut_cracked2_3.bmp",
				".\\bitmaps\\WallNut\\WallNut_cracked2\\WallNut_cracked2_4.bmp" };
			for (int i = 0; i < 4; i++)
				wallnut_cracked2_animation.AddBitmap(filename2[i], RGB(255, 255, 255));
		}
		void OnMove()
		{
			if (blood > 400) {
				wallnut_animation.OnMove();
			}
			else if (blood > 200) {
				wallnut_cracked1_animation.OnMove();
			}
			else {
				wallnut_cracked2_animation.OnMove();
			}

		}
		void OnShow()
		{
			if (is_alive)
			{
				if (blood > 400) {
					wallnut_animation.SetTopLeft(x, y);
					wallnut_animation.OnShow();
				}
				else if (blood > 200) {
					wallnut_cracked1_animation.SetTopLeft(x, y);
					wallnut_cracked1_animation.OnShow();
				}
				else {
					wallnut_cracked2_animation.SetTopLeft(x, y);
					wallnut_cracked2_animation.OnShow();
				}
			}

		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		int GetBlood()
		{
			return blood;
		}

		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}

		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 60 && x < zx - 35) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		CAnimation wallnut_animation;
		CAnimation wallnut_cracked1_animation;
		CAnimation wallnut_cracked2_animation;
	};

	class YCherryBomb
	{
	public:
		YCherryBomb(int x, int y)
		{
			this->x = x;
			this->y = y;
			is_alive = true;
			bomb = false;
			counter = 65;

		}
		~YCherryBomb()
		{
		}
		void LoadBitmap()
		{
			char *filename[7] = { ".\\bitmaps\\CherryBomb\\CherryBomb_0.bmp", ".\\bitmaps\\CherryBomb\\CherryBomb_1.bmp", ".\\bitmaps\\CherryBomb\\CherryBomb_2.bmp",
				".\\bitmaps\\CherryBomb\\CherryBomb_3.bmp", ".\\bitmaps\\CherryBomb\\CherryBomb_4.bmp"
				, ".\\bitmaps\\CherryBomb\\Boom.bmp", ".\\bitmaps\\CherryBomb\\Boom.bmp" };
			for (int i = 0; i < 7; i++)
				cherrybomb_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		void OnMove()
		{

			if (counter == 22) {
				bomb = true;
			}
			else if (counter < 0) {
				is_alive = false;
			}
			cherrybomb_animation.OnMove();
			counter -= 1;

		}
		void OnShow()
		{
			if (!bomb)
			{
				cherrybomb_animation.SetTopLeft(x - 55, y - 40);
				cherrybomb_animation.OnShow();
			}
			else {
				cherrybomb_animation.SetTopLeft(x - 85, y - 64);
				cherrybomb_animation.OnShow();
			}

		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		bool Bomb() {
			return bomb;
		}

		bool checkNearbyZombies(int zx, int zy) {
			if (y - 160 < zy && zy < y + 120) {
				if (zx > x - 160 && zx < x + 120) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		CAnimation cherrybomb_animation;
		int counter;
		int bomb;
	};

	class YIceShooterBullet {
	public:
		YIceShooterBullet(int x, int y) {
			this->x = x + 30;
			this->y = y;
			is_alive = true;
		}

		void LoadBitmap()
		{
			iceshooter_bullet.LoadBitmap(".\\bitmaps\\IceShooter\\PeaIce_0.bmp", RGB(255, 255, 255));
		}
		void OnMove()
		{
			x += 7;
			if (x > 800) {
				is_alive = false;
			};
		}

		void OnShow()
		{
			if (is_alive)
			{
				iceshooter_bullet.SetTopLeft(x, y);
				iceshooter_bullet.ShowBitmap();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}

		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}

	private:
		int x, y;
		bool is_alive;
		CMovingBitmap iceshooter_bullet;
	};

	class YIceShooter
	{
	public:
		YIceShooter(int x, int y)
		{
			delay = 30;
			this->x = x + 20;
			this->y = y + 20;
			blood = 450;
			is_alive = true;
		}
		~YIceShooter()
		{
		}
		void LoadBitmap()
		{
			char *filename[5] = { ".\\bitmaps\\IceShooter\\SnowPea_1.bmp", ".\\bitmaps\\IceShooter\\SnowPea_2.bmp", ".\\bitmaps\\IceShooter\\SnowPea_3.bmp", ".\\bitmaps\\IceShooter\\SnowPea_4.bmp", ".\\bitmaps\\IceShooter\\SnowPea_5.bmp" };
			for (int i = 0; i < 5; i++)
				iceshooter_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		void OnMove()
		{
			iceshooter_animation.OnMove();

			if (delay == 0) {
				fireBullet();
				delay = 80;
			}
			delay--;

			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnMove();
				else {
					bullets_vector.erase(bullets_vector.begin() + i);
				}
			}

		}
		void OnShow()
		{
			if (is_alive)
			{
				iceshooter_animation.SetTopLeft(x, y);
				iceshooter_animation.OnShow();
			}
			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnShow();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		void SetBlood(int attack_blood)
		{
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		int GetBlood()
		{
			return blood;
		}
		void fireBullet() {
			auto sp = make_shared<YIceShooterBullet>(x, y);
			sp->LoadBitmap();
			bullets_vector.push_back(sp);
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		bool checkBulletCollideWithZombie(int zx, int mapy) {
			if (!bullets_vector.empty() && bullets_vector.at(0)->GetY() - 20 == mapy) {
				int t = bullets_vector.at(0)->GetX();
				if (bullets_vector.at(0)->GetX() > zx + 20 && bullets_vector.at(0)->GetX() < zx + 80) {
					bullets_vector.at(0)->SetIsAlive(false);
					return true;
				}
			}
			return false;
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 60 && x < zx - 35) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		std::vector<shared_ptr<YIceShooterBullet>> bullets_vector;
		CAnimation iceshooter_animation;
		int delay;
	};

	class YPotatoMine
	{
	public:
		YPotatoMine(int x, int y)
		{
			this->x = x + 10;
			this->y = y + 20;
			is_alive = true;
			bomb = 0;
			counter = 0;
			blood = 300;
			zombie_checked = false;
		}
		~YPotatoMine()
		{
		}
		void LoadBitmap()
		{
			char *filename[8] = { ".\\bitmaps\\PotatoMine\\PotatoMine_0.bmp",
				".\\bitmaps\\PotatoMine\\PotatoMine_1.bmp", ".\\bitmaps\\PotatoMine\\PotatoMine_2.bmp",
				".\\bitmaps\\PotatoMine\\PotatoMine_3.bmp", ".\\bitmaps\\PotatoMine\\PotatoMine_4.bmp",
				 ".\\bitmaps\\PotatoMine\\PotatoMine_5.bmp",".\\bitmaps\\PotatoMine\\PotatoMine_6.bmp"
				,".\\bitmaps\\PotatoMine\\PotatoMine_7.bmp" };
			for (int i = 0; i < 8; i++)
				potatomine_animation.AddBitmap(filename[i], RGB(255, 255, 255));

			char *filenamee[5] = { ".\\bitmaps\\PotatoMine\\PotatoMineExplode_0.bmp",
				".\\bitmaps\\PotatoMine\\PotatoMineExplode_0.bmp",".\\bitmaps\\PotatoMine\\PotatoMineExplode_0.bmp"
				,".\\bitmaps\\PotatoMine\\PotatoMineExplode_0.bmp" ,".\\bitmaps\\PotatoMine\\PotatoMineExplode_0.bmp" };
			for (int i = 0; i < 5; i++)
				potatomine_explode_animation.AddBitmap(filenamee[i], RGB(255, 255, 255));

			char *filenamei[2] = { ".\\bitmaps\\PotatoMine\\PotatoMineInit_0.bmp",
				".\\bitmaps\\PotatoMine\\PotatoMineInit_0.bmp" };
			for (int i = 0; i < 2; i++)
				potatomine_init_animation.AddBitmap(filenamei[i], RGB(255, 255, 255));


		}
		void OnMove()
		{
			if (counter < 700) {
				counter += 1;
				potatomine_init_animation.OnMove();
			}
			else if (bomb > 10) {
				is_alive = false;
			}
			else if (counter > 705 && zombie_checked) {
				counter += 1;
				bomb += 1;
				potatomine_explode_animation.OnMove();
			}
			else {
				counter += 1;
				potatomine_animation.OnMove();
			}


		}
		void SetZombieChecked() {
			zombie_checked = true;
		}

		void OnShow()
		{
			if (counter < 700) {
				potatomine_init_animation.SetTopLeft(x, y);
				potatomine_init_animation.OnShow();
			}
			else if (bomb) {
				potatomine_explode_animation.SetTopLeft(x, y);
				potatomine_explode_animation.OnShow();
			}
			else {
				potatomine_animation.SetTopLeft(x, y);
				potatomine_animation.OnShow();
			}
		}
		int GetBlood()
		{
			return blood;
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 75 && x < zx - 30) {
					return true;
				}
			}
			return false;
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		bool Bomb() {
			return bomb;
		}

		bool checkNearbyZombies(int zx, int zy) {
			if (y - 160 < zy && zy < y + 120) {
				if (x - 160 < zx && zx < x + 140) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		CAnimation potatomine_animation;
		CAnimation potatomine_explode_animation;
		CAnimation potatomine_init_animation;
		int blood;
		int counter;
		int bomb;
		bool zombie_checked;
	};

	class YSquash
	{
	public:
		YSquash(int x, int y)
		{
			this->x = x + 10;
			this->y = y + 20;
			is_alive = true;
			bomb = 0;
			counter = 0;
			blood = 300;
			zombie_checked = false;
		}
		~YSquash()
		{
		}
		void LoadBitmap()
		{
			char *filename[8] = { ".\\bitmaps\\Squash\\Squash_0.bmp",
				".\\bitmaps\\Squash\\Squash_1.bmp", ".\\bitmaps\\Squash\\Squash_2.bmp",
				".\\bitmaps\\Squash\\Squash_3.bmp", ".\\bitmaps\\Squash\\Squash_5.bmp"
				,".\\bitmaps\\Squash\\Squash_7.bmp", ".\\bitmaps\\Squash\\SquashAim_0.bmp"
				, ".\\bitmaps\\Squash\\SquashAim_0.bmp" };
			for (int i = 0; i < 8; i++)
				squash_animation.AddBitmap(filename[i], RGB(255, 255, 255));

			char *filenamee[5] = { ".\\bitmaps\\Squash\\SquashAttack_0.bmp",
				".\\bitmaps\\Squash\\SquashAttack_1.bmp",".\\bitmaps\\Squash\\SquashAttack_2.bmp"
				,".\\bitmaps\\Squash\\SquashAttack_3.bmp" ,".\\bitmaps\\Squash\\SquashAttack_3.bmp" };
			for (int i = 0; i < 5; i++)
				squash_attack_animation.AddBitmap(filenamee[i], RGB(255, 255, 255));

		}
		void OnMove()
		{
			if (zombie_checked) {
				counter += 1;
				bomb += 1;
				squash_attack_animation.OnMove();
				if (counter == 35) {
					is_alive = false;
				}
			}
			else {
				squash_animation.OnMove();
			}

		}
		void SetZombieChecked() {
			zombie_checked = true;
		}

		void OnShow()
		{
			if (zombie_checked) {
				squash_attack_animation.SetTopLeft(x - 10, y - 140);
				squash_attack_animation.OnShow();
			}
			else {
				squash_animation.SetTopLeft(x - 10, y - 140);
				squash_animation.OnShow();
			}
		}

		int GetBlood()
		{
			return blood;
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 75 && x < zx - 30) {
					return true;
				}
			}
			return false;
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		bool Bomb() {
			return bomb;
		}

		bool checkNearbyZombies(int zx, int zy) {
			if (y - 160 < zy && zy < y + 120) {
				if (x - 160 < zx && zx < x + 140) {
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		CAnimation squash_animation;
		CAnimation squash_attack_animation;
		int blood;
		int counter;
		int bomb;
		bool zombie_checked;
	};

	class YShooterBullet {
	public:
		YShooterBullet(int x, int y) {
			this->x = x + 30;
			this->y = y;
			is_alive = true;
		}

		void LoadBitmap()
		{
			shooter_bullet.LoadBitmap(".\\bitmaps\\Shroom\\BulletMushRoom_0.bmp", RGB(255, 255, 255));
		}
		void OnMove()
		{
			x += 6;
			if (x > 800) {
				is_alive = false;
			};
		}

		void OnShow()
		{
			if (is_alive)
			{
				shooter_bullet.SetTopLeft(x, y + 25);
				shooter_bullet.ShowBitmap();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}

		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}

	private:
		int x, y;
		bool is_alive;
		CMovingBitmap shooter_bullet;
	};

	class YShooter
	{
	public:
		YShooter(int x, int y)
		{
			delay = 30;
			this->x = x + 20;
			this->y = y + 20;
			blood = 450;
			is_alive = true;
			close = false;
		}
		~YShooter()
		{
		}
		void LoadBitmap()
		{
			char *filename[4] = { ".\\bitmaps\\Shroom\\PuffShroom_0.bmp", ".\\bitmaps\\Shroom\\PuffShroom_2.bmp", ".\\bitmaps\\Shroom\\PuffShroom_3.bmp", ".\\bitmaps\\Shroom\\PuffShroom_4.bmp" };
			for (int i = 0; i < 4; i++)
				shooter_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		void OnMove()
		{
			shooter_animation.OnMove();

			if (delay == 0) {
				fireBullet();
				delay = 80;
			}
			delay--;

			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnMove();
				else {
					bullets_vector.erase(bullets_vector.begin() + i);
				}
			}

		}
		void OnShow()
		{
			if (is_alive)
			{
				shooter_animation.SetTopLeft(x, y + 10);
				shooter_animation.OnShow();
			}
			for (size_t i = 0; i < bullets_vector.size(); i++) {
				if (bullets_vector.at(i)->IsAlive())
					bullets_vector.at(i)->OnShow();
			}
		}
		bool IsAlive()
		{
			return is_alive;
		}
		void SetIsAlive(bool alive)
		{
			is_alive = alive;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		void SetBlood(int attack_blood)
		{
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		int GetBlood()
		{
			return blood;
		}
		void fireBullet() {
			if (close) {
				auto sp = make_shared<YShooterBullet>(x, y);
				sp->LoadBitmap();
				bullets_vector.push_back(sp);
			}
		}
		bool isClose(int zx, int zy) {
			if (zy == y - 20) {
				if (x + 300 > zx && zx > x - 60) {
					return true;
				}
			}
			return false;
		}
		void SetClose(bool is_close)
		{
			close = is_close;
		}
		void LostBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		bool checkBulletCollideWithZombie(int zx, int mapy) {
			if (!bullets_vector.empty() && bullets_vector.at(0)->GetY() - 20 == mapy) {
				int t = bullets_vector.at(0)->GetX();
				if (bullets_vector.at(0)->GetX() > zx + 20 && bullets_vector.at(0)->GetX() < zx + 80) {
					bullets_vector.at(0)->SetIsAlive(false);
					return true;
				}
			}
			return false;
		}
		bool checkPlantCollideWithZombie(int zx, int zy) {
			if (zy == y - 20) {
				if (x > zx - 60 && x < zx - 35) { // zx - 35 > x > zx - 60
					return true;
				}
			}
			return false;
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		std::vector<shared_ptr<YShooterBullet>> bullets_vector;
		CAnimation shooter_animation;
		int delay;
		bool close;
	};

}

#endif

