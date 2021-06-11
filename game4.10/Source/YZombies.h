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
			zombie_die_delay_time = 115;
		}
		YNormalZombie(int x, int my) {
			Map_Y_Location = my;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[my] - 30;
			this->x = x;
			blood = 10;
			is_alive = true;
			bomb_flag = false;
			zombie_die_delay_time = 115;
			zombie_bomb_die_delay_time = 180;

		}
		YNormalZombie(int x, int my, std::string style) {
			Map_Y_Location = my;		// 0~4
			int a[5] = { 78, 182, 270, 368, 464 };
			y = a[my] - 30;
			this->x = x;
			blood = 10;
			is_alive = true;
			bomb_flag = false;
			zombie_die_delay_time = 115;
			zombie_bomb_die_delay_time = 180;
			zombie_style = style;
			if (zombie_style == "conehead") {
				blood = 20;
			}
			if (zombie_style == "bucket") {
				blood = 30;
			}
			if (zombie_style == "newspaper") {
				blood = 20;
			}
		}
		~YNormalZombie() {

		}

		void LoadBitmap() {
			char *filenameni[10] = { ".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_0.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_1.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_2.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_3.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_4.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_5.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_6.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_7.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_8.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombie\\NewspaperZombie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_news_animation.AddBitmap(filenameni[i], RGB(255, 255, 255));

			char *filenamen[8] = { ".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_0.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_2.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_4.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_6.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieAttack\\NewspaperZombieAttack_7.bmp" };
			for (int i = 0; i < 8; i++)
				zombie_news_attack_animation.AddBitmap(filenamen[i], RGB(255, 255, 255));
			
			char *filenamena[11] = { ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_0.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_1.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_2.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_3.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_4.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_5.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_6.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_7.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_8.bmp",
							".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_9.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieDie\\NewspaperZombieDie_10.bmp" };
			for (int i = 0; i < 11; i++)
				zombie_news_die_animation.AddBitmap(filenamena[i], RGB(255, 255, 255));

			char *filenamene[10] = { ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_0.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_1.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_2.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_3.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_4.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_5.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_6.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_7.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_8.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaper\\NewspaperZombieNoPaper_9.bmp" };
			for (int i = 0; i < 10; i++)
				zombie_nonews_animation.AddBitmap(filenamene[i], RGB(255, 255, 255));

			char *filenameno[7] = { ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_0.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_1.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_2.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_3.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_4.bmp",
						".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_5.bmp", ".\\bitmaps\\NormalZombie\\NewspaperZombieNoPaperAttack\\NewspaperZombieNoPaperAttack_6.bmp"};
			for (int i = 0; i < 7; i++)
				zombie_nonews_attack_animation.AddBitmap(filenameno[i], RGB(255, 255, 255));

			char *filenameb[10] = { ".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_0.bmp",
					".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_1.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_2.bmp",
					".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_3.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_4.bmp",
					".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_5.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_6.bmp",
					".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_7.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_8.bmp",
					".\\bitmaps\\NormalZombie\\BucketheadZombie\\BucketheadZombie_9.bmp" };
			for (int i = 0; i < 10; i++)
				zombie_bucket_animation.AddBitmap(filenameb[i], RGB(255, 255, 255));

			char *filenameba[11] = { ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_0.bmp",
				".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_2.bmp",
				".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_4.bmp",
				".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_6.bmp",
				".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_7.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_8.bmp",
				".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_9.bmp", ".\\bitmaps\\NormalZombie\\BucketheadZombieAttack\\BucketheadZombieAttack_10.bmp" };
			for (int i = 0; i < 11; i++)
				zombie_bucket_attack_animation.AddBitmap(filenameba[i], RGB(255, 255, 255));

			char *filenamec[10] = { ".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_0.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_1.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_2.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_3.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_4.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_5.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_6.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_7.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_8.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombie\\ConeheadZombie_9.bmp" };
			for (int i = 0; i < 10; i++)
				zombie_conehead_animation.AddBitmap(filenamec[i], RGB(255, 255, 255));

			char *filenameca[11] = { ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_0.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_2.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_4.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_6.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_7.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_8.bmp",
				".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_9.bmp", ".\\bitmaps\\NormalZombie\\ConeheadZombieAttack\\ConeheadZombieAttack_10.bmp" };
			for (int i = 0; i < 11; i++)
				zombie_conehead_attack_animation.AddBitmap(filenameca[i], RGB(255, 255, 255));

			char *filenamef[10] = {".\\bitmaps\\NormalZombie\\Zombie\\Zombie_0.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_1.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_2.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_3.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_4.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_5.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_6.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_7.bmp", ".\\bitmaps\\NormalZombie\\Zombie\\Zombie_8.bmp",
				".\\bitmaps\\NormalZombie\\Zombie\\Zombie_9.bmp"};
			for (int i = 0; i < 10; i++)
				zombie_animation.AddBitmap(filenamef[i], RGB(255, 255, 255));

			char *filenamefa[10] = { ".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_0.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_1.bmp", ".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_2.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_3.bmp", ".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_4.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_5.bmp", ".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_6.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_7.bmp", ".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_8.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombie\\FlagZombie_9.bmp" };
			for (int i = 0; i < 10; i++)
				zombie_flag_animation.AddBitmap(filenamefa[i], RGB(255, 255, 255));

			char *filename[10] = { ".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_0.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_1.bmp", ".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_2.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_3.bmp", ".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_4.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_5.bmp", ".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_6.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_7.bmp", ".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_8.bmp",
				".\\bitmaps\\NormalZombie\\FlagZombieAttack\\FlagZombieAttack_9.bmp" };
			for (int i = 0; i < 10; i++)
				zombie_flag_attack_animation.AddBitmap(filename[i], RGB(255, 255, 255));


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

			char *filenamedb[19] = { ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_0.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_1.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_2.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_3.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_4.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_5.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_6.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_7.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_8.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_9.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_10.bmp",
			".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_11.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_12.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_14.bmp",
				".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_15.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_16.bmp",
			".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_17.bmp", ".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_18.bmp",
			".\\bitmaps\\NormalZombie\\BoomDie\\BoomDie_19.bmp" };
			for (int i = 0; i < 19; i++)
				zombie_die_animation_bomb.AddBitmap(filenamedb[i], RGB(255, 255, 255));
		}

		void OnMove(std::string mode) {
			if (bomb_flag) {
				mode = "bomb";
			}
			if (mode == "attack") {
				if (zombie_style == "flag") {
					zombie_flag_attack_animation.OnMove();
				}
				else if (zombie_style == "conehead" && blood > 10) {
					zombie_conehead_attack_animation.OnMove();
				}
				else if (zombie_style == "bucket" && blood > 10) {
					zombie_bucket_attack_animation.OnMove();
				}
				else if (zombie_style == "newspaper" && blood > 10) {
					zombie_news_attack_animation.OnMove();
				}
				else if (zombie_style == "newspaper" && blood <= 10) {
					zombie_nonews_attack_animation.OnMove();
				}
				else {
					zombie_attack_animation.OnMove();
				}
			}
			else if (mode == "walk") {
				if (delay % 2 == 0) {
					x -= 1;
					if (zombie_style == "flag") {
						zombie_flag_animation.OnMove();
					}
					else if (zombie_style == "conehead" && blood > 10) {
						zombie_conehead_animation.OnMove();
					}
					else if (zombie_style == "bucket" && blood > 10) {
						zombie_bucket_animation.OnMove();
					}
					else if (zombie_style == "newspaper" && blood > 10) {
						zombie_news_animation.OnMove();
					}
					else if (zombie_style == "newspaper" && blood <= 10) {
						zombie_nonews_animation.OnMove();
						x -= 3;
					}
					else {
						zombie_animation.OnMove();
					}
					delay = 0;
				}
			}
			else if (mode == "die") {
				if (zombie_style == "newspaper") {
					zombie_news_die_animation.OnMove();
					zombie_die_animation_head.OnMove();
				}
				else {
					zombie_die_animation.OnMove();
					zombie_die_animation_head.OnMove();
				}
			}
			else if (mode == "bomb") {
				zombie_die_animation_bomb.OnMove();
			}
			delay++;
		}

		void OnMove(std::string mode, bool fast_mode) {
			if (bomb_flag) {
				mode = "bomb";
			}
			if (mode == "attack") {
				if (zombie_style == "flag") {
					zombie_flag_attack_animation.OnMove();
				}
				else if (zombie_style == "conehead" && blood > 10) {
					zombie_conehead_attack_animation.OnMove();
				}
				else if (zombie_style == "bucket" && blood > 10) {
					zombie_bucket_attack_animation.OnMove();
				}
				else if (zombie_style == "newspaper" && blood > 10) {
					zombie_news_attack_animation.OnMove();
				}
				else if (zombie_style == "newspaper" && blood <= 10) {
					zombie_nonews_attack_animation.OnMove();
				}
				else {
					zombie_attack_animation.OnMove();
				}
			}
			else if (mode == "walk") {
				if (delay % 1 == 0) {
					x -= 5;
					if (zombie_style == "flag") {
						zombie_flag_animation.OnMove();
					}
					else if (zombie_style == "conehead" && blood > 10) {
						zombie_conehead_animation.OnMove();
					}
					else if (zombie_style == "bucket" && blood > 10) {
						zombie_bucket_animation.OnMove();
					}
					else if (zombie_style == "newspaper" && blood > 10) {
						zombie_news_animation.OnMove();
					}
					else if (zombie_style == "newspaper" && blood <= 10) {
						zombie_nonews_animation.OnMove();
						x -= 1;
					}
					else {
						zombie_animation.OnMove();
					}
				}
			}
			else if (mode == "die") {
				if (zombie_style == "newspaper") {
					zombie_news_die_animation.OnMove();
					zombie_die_animation_head.OnMove();
				}
				else {
					zombie_die_animation.OnMove();
					zombie_die_animation_head.OnMove();
				}
			}
			else if (mode == "bomb") {
				zombie_die_animation_bomb.OnMove();
			}
			delay++;
		}

		void OnShow(std::string mode) {
			if (bomb_flag) {
				mode = "bomb";
			}
			if (mode == "attack") {
				if (zombie_style == "flag") {
					zombie_flag_attack_animation.SetTopLeft(x, y);
					zombie_flag_attack_animation.OnShow();
				}
				else if (zombie_style == "conehead" && blood > 10) {
					zombie_conehead_attack_animation.SetTopLeft(x, y);
					zombie_conehead_attack_animation.OnShow();
				}
				else if (zombie_style == "bucket" && blood > 10) {
					zombie_bucket_attack_animation.SetTopLeft(x, y);
					zombie_bucket_attack_animation.OnShow();
				}
				else if (zombie_style == "newspaper" && blood > 10) {
					zombie_news_attack_animation.SetTopLeft(x, y);
					zombie_news_attack_animation.OnShow();
				}
				else if (zombie_style == "newspaper" && blood <= 10) {
					zombie_nonews_attack_animation.SetTopLeft(x, y);
					zombie_nonews_attack_animation.OnShow();
				}
				else {
					zombie_attack_animation.SetTopLeft(x, y);
					zombie_attack_animation.OnShow();
				}
			}
			else if (mode == "walk") {
				if (zombie_style == "flag") {
					zombie_flag_animation.SetTopLeft(x, y);
					zombie_flag_animation.OnShow();
				}
				else if (zombie_style == "conehead" && blood > 10) {
					zombie_conehead_animation.SetTopLeft(x, y);
					zombie_conehead_animation.OnShow();
				}
				else if (zombie_style == "bucket" && blood > 10) {
					zombie_bucket_animation.SetTopLeft(x, y);
					zombie_bucket_animation.OnShow();
				}
				else if (zombie_style == "newspaper" && blood > 10) {
					zombie_news_animation.SetTopLeft(x, y);
					zombie_news_animation.OnShow();
				}
				else if (zombie_style == "newspaper" && blood <= 10) {
					zombie_nonews_animation.SetTopLeft(x, y);
					zombie_nonews_animation.OnShow();
				}
				else {
					zombie_animation.SetTopLeft(x, y);
					zombie_animation.OnShow();
				}

			}
			else if (mode == "die") {
				if (zombie_die_delay_time > 0) {
					if (zombie_style == "newspaper") {
						zombie_news_die_animation.SetTopLeft(x, y);
						zombie_news_die_animation.OnShow();
						zombie_die_animation_head.SetTopLeft(x + 50, y);
						zombie_die_animation_head.OnShow();
						zombie_die_delay_time--;
					}
					else {
						zombie_die_animation.SetTopLeft(x, y);
						zombie_die_animation.OnShow();
						zombie_die_animation_head.SetTopLeft(x + 50, y);
						zombie_die_animation_head.OnShow();
						zombie_die_delay_time--;
					}
				}
				else {
					x = 1000;
				}
			}
			else if (mode == "bomb") {
				if (zombie_bomb_die_delay_time > 0) {
					zombie_die_animation_bomb.SetTopLeft(x, y);
					zombie_die_animation_bomb.OnShow();
					zombie_bomb_die_delay_time--;
				}
				else {
					is_alive = false;
					x = 1000;
				}
			}
			
		}

		void SetBombFlag() {
			bomb_flag = true;
		}

		bool IsAlive() {
			return is_alive;
		}
		void SetIsAlive(bool alive) {
			is_alive = alive;
		}
		void freezen() {
			x += 2;
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
		CAnimation zombie_die_animation_bomb;
		CAnimation zombie_flag_animation;
		CAnimation zombie_flag_attack_animation;
		CAnimation zombie_conehead_animation;
		CAnimation zombie_conehead_attack_animation;
		CAnimation zombie_bucket_animation;
		CAnimation zombie_bucket_attack_animation;
		CAnimation zombie_news_animation;
		CAnimation zombie_news_attack_animation;
		CAnimation zombie_news_die_animation;
		CAnimation zombie_nonews_animation;
		CAnimation zombie_nonews_attack_animation;

		int zombie_bomb_die_delay_time;
		int zombie_die_delay_time;
		int attack_power = 1;
		int delay = 0;
		bool bomb_flag;
		std::string zombie_style;
	};


}
#endif