#ifndef MYGAME_H
#define MYGAME_H

#include <memory>
#include <vector>
#include "YSun.h"
#include "YCard.h"
#include "YPlants.h"
#include "YMap.h"
#include "YZombies.h"
#include "YCar.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_START,
		AUDIO_MAIN,
		AUDIO_MENUTOGAME,
		AUDIO_SUNPICK,
		AUDIO_PLANTS,
		AUDIO_CAR,
		AUDIO_START_NIGHT,
		AUDIO_BOMB,
		AUDIO_VICTORY
	};


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作

	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	mainmenu;		
		CMovingBitmap	loadtext;
		CMovingBitmap	adventure0;
		CMovingBitmap   all_level_done;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		friend class YZombies;

		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:

		const int		NUMBALLS;
		CMovingBitmap	background;
		CMovingBitmap	background_night;

		CMovingBitmap	chooser;
		YShovelCard		shovel_card;
		int				picX, picY;
		int				flag;
		YSun			sun;
		int				sun_amount;	
		bool			generateSunFlowerFlag;
		bool			generatePeaShooterFlag;
		bool			generateWallNutFlag;
		bool			generateCherryBombFlag;
		bool			generateIceShooterFlag;
		bool			generatePotatomineFlag;
		bool			generateShooterFlag;
		bool			generateSquashFlag;

		bool			shovelFlag;

		YSunFlowerCard   sun_flower_card;
		YPeaShooterCard  pea_shooter_card;
		YWallNutCard	 wallnut_card;
		YCherryBombCard  cherrybomb_card;
		YIceShooterCard      ice_shooter_card;
		YPotatomineCard		potatomine_card;
		YShooterCard  shooter_card;
		YSquashCard  squash_card;

		int sun_flower_card_delay_flag;
		int peashooter_card_delay_flag;
		int wallnut_card_delay_flag;
		int cherrybomb_card_delay_flag;
		int iceshooter_card_delay_flag;
		int potatomine_card_delay_flag;
		int shooter_card_delay_flag;
		int squash_card_delay_flag;


		std::vector<shared_ptr<YSunFlower>>	sunflower_vector;
		std::vector<shared_ptr<YPeaShooter>>	peashooter_vector;
		std::vector<shared_ptr<YWallNut>>	wallnut_vector;
		std::vector<shared_ptr<YCherryBomb>>	cherrybomb_vector;
		std::vector<shared_ptr<YIceShooter>>	iceshooter_vector;
		std::vector<shared_ptr<YPotatoMine>>	potatomine_vector;
		std::vector<shared_ptr<YShooter>>	shooter_vector;
		std::vector<shared_ptr<YSquash>>	squash_vector;

		std::vector<shared_ptr<YNormalZombie>>	normalzombie_vector;

		YMap			map;
		bool			animation_flag;

		YCar car0;
		YCar car1;
		YCar car2;
		YCar car3;
		YCar car4;
		bool car0_flag;
		bool car1_flag;
		bool car2_flag;
		bool car3_flag;
		bool car4_flag;
		bool car0_sound_flag;
		bool car1_sound_flag;
		bool car2_sound_flag;
		bool car3_sound_flag;
		bool car4_sound_flag;
		bool zombie_home_flag;
		bool zombie_fast_mode;

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnMove();	
		void OnShow();
	private:
		int counter;
		CMovingBitmap	loose;
		CMovingBitmap	loose_night;
		CMovingBitmap	newplant;
		CMovingBitmap	bucket;
		CMovingBitmap	cherrybomb;
		CMovingBitmap	conehead;
		CMovingBitmap	flag;
		CMovingBitmap	newspaper;
		CMovingBitmap	potatomine;
		CMovingBitmap	puff_shroom;
		CMovingBitmap	snowpea;
		CMovingBitmap	wallnut;
		CMovingBitmap	squash;
		CMovingBitmap	victory;

	};

}


#endif