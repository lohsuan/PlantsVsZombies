#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"
#include "YPlants.h"
#include "YSun.h"
#include "YSunFlower.h"

namespace game_framework {
	//////////////////////////////////////////////
	// YSunFlower: Plants class
	//////////////////////////////////////////////

	YSunFlower::YSunFlower(){
		blood = 5;
		sun_make_time = 7;
		already_set_up = flase;
	}
	YSunFlower::~YSunFlower() override {

	}
	YSunFlower::void LoadBitmap() override {
		char *filename[8] = { ".\\bitmaps\\SunFlower_0.bmp",".\\bitmaps\\SunFlower_1.bmp",".\\bitmaps\\SunFlower_2.bmp",".\\bitmaps\\SunFlower_3.bmp"
		, ".\\bitmaps\\SunFlower_4.bmp",".\\bitmaps\\SunFlower_5.bmp",".\\bitmaps\\SunFlower_6.bmp",".\\bitmaps\\SunFlower_7.bmp"
		};
		for (int i = 0; i < 8; i++)
			sunanimation.AddBitmap(filename[i], RGB(255, 255, 255));
	}
	YSunFlower::void OnMove() override {

	}
	YSunFlower::void OnShow() override {

	}
	YSunFlower::void SetBlood(int attack_blood){
		blood = blood - attack_blood;
	}
	YSunFlower::int  GetBlood(){
		return blood;
	}
	YSunFlower::void SetUp(){
		already_set_up = true;
	}
	
	// int blood;
	// int sun_make_time;
	// bool already_set_up;
}

