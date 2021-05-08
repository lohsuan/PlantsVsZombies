#ifndef YZOMBIES_H
#define YZOMBIES_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include "gamelib.h"
#include "YPlants.h"
#include "YMap.h"

namespace game_framework {
	class YNormalZombie {
	public:
		//friend class CGameStateRun;
		//friend class YSunFlower;
		//friend class YPeaShooter;

		YNormalZombie() {
			srand((int)time(NULL));
			int i = rand() % 5;		// 0~4
			Map_Y_Location = i;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[i] -30;
			x = 900;
			blood = 10;
			is_alive = true;
			zombie_die_delay_time = 230;
		}
		YNormalZombie(int x, int my) {
			//srand((int)time(NULL));
			//int i = rand() % 5;		// 0~4
			Map_Y_Location = my;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[my] - 30;
			this->x = x;
			blood = 10;
			is_alive = true;
			zombie_die_delay_time = 115;
		}
		~YNormalZombie() {

		}

		void LoadBitmap() {

			char *filename[10] = {".\\bitmaps\\NormalZombie\\Zombie\\Zombie_0.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_1.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_2.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_3.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_4.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_5.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_6.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_7.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_8.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_animation.AddBitmap(filename[i], RGB(255, 255, 255));

			char *filenamea[7] = {".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_0.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_2.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_4.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_6.bmp"};
			for (int i = 0; i < 7; i++)
				zombie_attack_animation.AddBitmap(filenamea[i], RGB(255, 255, 255));

			char *filenamed[12] = {".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_0.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_2.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_4.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_6.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_7.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_8.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_9.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_10.bmp",
			".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_11.bmp" };
			for (int i = 0; i < 12; i++)
				zombie_die_animation.AddBitmap(filenamed[i], RGB(255, 255, 255));

			char *filenamedh[12] = { ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_0.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_2.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_4.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_6.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_7.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_8.bmp",
				".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_9.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_10.bmp",
			".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieHead_11.bmp" };
			for (int i = 0; i < 12; i++)
				zombie_die_animation_head.AddBitmap(filenamedh[i], RGB(255, 255, 255));
		}

		void OnMove(std::string mode) {

		
			if (mode == "attack") {
				zombie_attack_animation.OnMove();
			}
			else if (mode == "walk") {
				if (delay % 2 == 0) {
					x -= 1;
					zombie_animation.OnMove();
					delay = 0;
				}
			}
			else if(mode == "die" ){
				zombie_die_animation.OnMove();
				zombie_die_animation_head.OnMove();
			}
			delay++;
		}

		void OnShow(std::string mode) {
			if (mode == "attack") {
				zombie_attack_animation.SetTopLeft(x, y);
				zombie_attack_animation.OnShow();
			}
			else if (mode == "walk") {
				zombie_animation.SetTopLeft(x, y);
				zombie_animation.OnShow();
			}
			else if (mode == "die") {
				if (zombie_die_delay_time > 0) {
					zombie_die_animation.SetTopLeft(x, y);
					zombie_die_animation.OnShow();
					zombie_die_animation_head.SetTopLeft(x+50, y);
					zombie_die_animation_head.OnShow();
					zombie_die_delay_time--;
				}
				else {
					x = 1000;
				}
			}
			
		}
		

		bool IsAlive() {
			return is_alive;
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		void  SetX(int x) {
			this->x = x;
		}
		void  SetY(int y) {
			this->y = y;
		}
		int  GetX() {
			return int(x);
		}
		int  GetY() {
			return int(y);
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
		int GetMapYLocation() {
			return Map_Y_Location;
		}

		int GetAttackPower() {
			return attack_power;
		}

	private:
		int x, y;
		bool is_alive;
		int blood;
		int Map_Y_Location;
		CAnimation zombie_animation;
		CAnimation zombie_attack_animation;
		CAnimation zombie_die_animation;
		CAnimation zombie_die_animation_head;
		int zombie_die_delay_time = 200;
		int attack_power = 1;
		int delay = 0;
	};


}
#endif