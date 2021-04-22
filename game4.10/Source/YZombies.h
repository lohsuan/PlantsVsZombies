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
		friend class CGameStateRun;
		//friend class YSunFlower;
		//friend class YPeaShooter;

		YNormalZombie() {
			srand((int)time(NULL));
			int i = rand() % 5;		// 0~4
			//Map_Y_Location = i;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[i] -30;
			x = 900;
			blood = 15;
			is_alive = true;
			//LoadBitmap();
		}
		//YNormalZombie(int x, int my) {
		//	//srand((int)time(NULL));
		//	//int i = rand() % 5;		// 0~4
		//	Map_Y_Location = my;		// 0~4
		//	int a[5] = { 78, 182, 270, 368, 464 };
		//	y = a[my] - 30;
		//	this->x = x;
		//	blood = 15;
		//	is_alive = true;
		//}
		~YNormalZombie() {

		}

		void LoadBitmap() {
			// try
			char *filename[10] = {".\\bitmaps\\NormalZombie\\Zombie\\Zombie_0.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_1.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_2.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_3.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_4.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_5.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_6.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_7.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_8.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_animation.AddBitmap(filename[i], RGB(255, 255, 255));

		//	char *filename[10] = { ".\\bitmaps\\Sun\\sun0.bmp",".\\bitmaps\\Sun\\sun1.bmp",".\\bitmaps\\Sun\\sun2.bmp",".\\bitmaps\\Sun\\sun3.bmp"
		//, ".\\bitmaps\\Sun\\sun4.bmp",".\\bitmaps\\Sun\\sun5.bmp",".\\bitmaps\\Sun\\sun6.bmp",".\\bitmaps\\Sun\\sun7.bmp" };
		//	for (int i = 0; i < 8; i++)
		//		zombie_animation.AddBitmap(filename[i], RGB(255, 255, 255));


			char *filenamea[7] = {".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_0.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_2.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_4.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_6.bmp"};
			for (int i = 0; i < 7; i++)
				zombie_attack_animation.AddBitmap(filenamea[i], RGB(255, 255, 255));

			char *filenamed[10] = {".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_0.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_2.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_4.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_6.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_7.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_8.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_die_animation.AddBitmap(filenamed[i], RGB(255, 255, 255));
		}

		void OnMove(std::string mode) {
			static int delay;
		
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
			else if(mode == "die"){
				if (delay % 2 == 0) {
					zombie_die_animation.OnMove();
					delay = 0;
				}
			}
			delay++;
		}

		void OnShow(std::string mode) {
			static int disappear_time = 300;
			
			//question
			if (mode == "attack") {
				zombie_attack_animation.SetTopLeft(x, y);
				zombie_attack_animation.OnShow();
			}
			else if (mode == "walk") {
				// try
				zombie_animation.SetTopLeft(x, y);
				zombie_animation.OnShow();
			}
			else if (mode == "die") {
				if (disappear_time > 0) {
					zombie_die_animation.SetTopLeft(x, y);
					zombie_die_animation.OnShow();
					disappear_time--;
				}				
			}
			
		}
		
		void attack() {

		}

		bool IsAlive() {
			return is_alive;
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		//void  SetX(int x) {
		//	this->x = x;
		//}
		int  GetX() {
			return int(x);
		}
		int  GetY() {
			return int(y);
		}
		void SetBlood(int attack_blood) {
			blood = blood - attack_blood;
			if (blood == 0) {
				is_alive = false;
			}
		}
		int  GetBlood() {
			return blood;
		}
		//int GetMapYLocation() {
		//	return Map_Y_Location;
		//}

	private:
		int x, y;
		bool is_alive;
		int blood;
		//int Map_Y_Location;
		CAnimation zombie_animation;
		CAnimation zombie_attack_animation;
		CAnimation zombie_die_animation;
	};


}
#endif