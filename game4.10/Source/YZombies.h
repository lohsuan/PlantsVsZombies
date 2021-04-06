#ifndef YZOMBIES_H
#define YZOMBIES_H

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include "gamelib.h"


namespace game_framework {
	class YNormalZombie {
	public:
		YNormalZombie() {
			srand((int)time(NULL));
			int i = rand() % 5;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[i];
			x = 1000;
			blood = 15;
			is_alive = true;

		}
		~YNormalZombie() {

		}

		void LoadBitmap() {
			// try
			char *filename[10] = {".\\bitmaps\\NormalZombie\\Zombie\\Zombie_0.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_1.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_2.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_3.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_4.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_5.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_6.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_7.bmp",".\\bitmaps\\NormalZombie\\Zombie\\Zombie_8.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_animation.AddBitmap(filename[i], RGB(255, 255, 255));

			char *filenamea[7] = {".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_0.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_2.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_4.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieAttack\\ZombieAttack_6.bmp"};
			for (int i = 0; i < 7; i++)
				zombie_attack_animation.AddBitmap(filenamea[i], RGB(255, 255, 255));

			char *filename[10] = {".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_0.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_1.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_2.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_3.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_4.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_5.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_6.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_7.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_8.bmp", ".\\bitmaps\\NormalZombie\\ZombieDie\\ZombieDie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_die_animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}

		void OnMove() {
			x += 1;
			zombie_animation.OnMove();
		}

		void OnShow() {
			if (blood<3){
				zombie_die_animation.SetTopLeft(x, y);
				zombie_die_animation.OnShow();
			}
			else if (IsAlive()) {
				// try
				zombie_animation.SetTopLeft(x, y);
				zombie_animation.OnShow();
				//zombie_animation.ShowBitmap();
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
			if (blood == 0) {
				is_alive = false;
			}
		}
		int  GetBlood() {
			return blood;
		}


	private:
		int x, y;
		bool is_alive;
		int blood;

		CAnimation zombie_animation;
		CAnimation zombie_attack_animation;
		CAnimation zombie_die_animation;
	};


}
#endif