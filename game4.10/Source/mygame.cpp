#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <string>	// to_string
#include <sstream>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "YMap.h"

namespace game_framework {

	int CGameState::victoryflag = 0;
	int CGameState::level = 1;
	bool CGameState::night_mode = false;
	bool CGameState::all_victory_flag = false;

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{

		ShowInitProgress(0);

		mainmenu.LoadBitmap("Bitmaps/MainMenu.bmp");
		adventure0.LoadBitmap("Bitmaps/Adventure0.bmp", RGB(255, 255, 255));
		all_level_done.LoadBitmap("Bitmaps/vic_done.bmp", RGB(0, 0, 0));

		CAudio::Instance()->Load(AUDIO_MAIN, "sounds\\mainmenu.mp3");
		CAudio::Instance()->Play(AUDIO_MAIN, true);

		CAudio::Instance()->Load(AUDIO_MENUTOGAME, "sounds\\menutogame.mp3");
		CAudio::Instance()->Load(AUDIO_SUNPICK, "sounds\\sun_pick.mp3");
		CAudio::Instance()->Load(AUDIO_PLANTS, "sounds\\plants_sound.mp3");
		CAudio::Instance()->Load(AUDIO_CAR, "sounds\\car.mp3");

	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_L = 76;
		//const char KEY_SPACE = ' ';
		//if (nChar == KEY_SPACE)
		//	GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		if (nChar == KEY_ESC)
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		if (nChar == KEY_L) {
			level += 1;
			if (level == 11) {
				level = 1;
			}
		}
	}


	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (point.x > 418 && point.y > 100 && point.x < 702 && point.y < 260) {
			CAudio::Instance()->Play(AUDIO_MENUTOGAME, false);
			GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
		}
	}

	void CGameStateInit::OnShow()
	{
		mainmenu.SetTopLeft(0, 0);
		mainmenu.ShowBitmap();

		adventure0.SetTopLeft(418, 100);
		adventure0.ShowBitmap();

		if (all_victory_flag) {
			all_level_done.SetTopLeft(45, 150);
			all_level_done.ShowBitmap();
		}
		
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(130, "微軟正黑體");
		fp = pDC->SelectObject(&f);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(174, 225, 174));
		if (level == 1)
			pDC->TextOut(710, 10, "level: 1");
		else if (level == 2)
			pDC->TextOut(710, 10, "level: 2");
		else if (level == 3)
			pDC->TextOut(710, 10, "level: 3");
		else if (level == 4)
			pDC->TextOut(710, 10, "level: 4");
		else if (level == 5)
			pDC->TextOut(710, 10, "level: 5");
		else if (level == 6)
			pDC->TextOut(710, 10, "level: 6");
		else if (level == 7)
			pDC->TextOut(710, 10, "level: 7");
		else if (level == 8)
			pDC->TextOut(710, 10, "level: 8");
		else if (level == 9)
			pDC->TextOut(710, 10, "level: 9");
		else if (level == 10)
			pDC->TextOut(710, 10, "level: 10");

		pDC->SetTextColor(RGB(204, 255, 204));
		pDC->TextOut(440, 260, "點擊 \"冒險模式\" 開始 !");
		pDC->SetTextColor(RGB(197, 229, 210));
		pDC->TextOut(470, 295, "L: level += 1");
		pDC->TextOut(470, 325, "S: sun = 500");
		pDC->TextOut(465, 355, "Z: zombie fast");
		pDC->TextOut(460, 385, "D: zombie all die");
		
		pDC->SetTextColor(RGB(185, 229, 255));
		pDC->TextOut(5, 516, "Use mouse to plant your plants and beat all zombies!");
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(5, 543, "Ctrl-Q: pause the Game.  Alt-F4 or ESC: Quit.");
		pDC->TextOut(5, 570, "Ctrl-F: switch between windows / full screen mode.");
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (!victoryflag && counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (victoryflag && point.x > 363 && point.y > 501 && point.x < 538 && point.y < 545) {
			if (CGameState::level == 11) {
				CGameState::level = 1;
				all_victory_flag = true;
			}
			GotoGameState(GAME_STATE_INIT);
			CAudio::Instance()->Stop(AUDIO_VICTORY);
		}
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		loose.LoadBitmap("Bitmaps/GameLoose.bmp");
		loose_night.LoadBitmap("Bitmaps/GameLoose_night.bmp");
		newplant.LoadBitmap("Bitmaps/almanac/newplant.bmp");
		bucket.LoadBitmap("Bitmaps/almanac/bucket.bmp");
		cherrybomb.LoadBitmap("Bitmaps/almanac/cherrybomb.bmp");
		conehead.LoadBitmap("Bitmaps/almanac/conehead.bmp");
		flag.LoadBitmap("Bitmaps/almanac/flag.bmp");
		potatomine.LoadBitmap("Bitmaps/almanac/potatomine.bmp");
		puff_shroom.LoadBitmap("Bitmaps/almanac/puff_shroom.bmp");
		snowpea.LoadBitmap("Bitmaps/almanac/snowpea.bmp");
		wallnut.LoadBitmap("Bitmaps/almanac/wallnut.bmp");
		squash.LoadBitmap("Bitmaps/almanac/squash.bmp");
		newspaper.LoadBitmap("Bitmaps/almanac/newspaper.bmp");
		victory.LoadBitmap("Bitmaps/almanac/victory.bmp");

		ShowInitProgress(66);

		ShowInitProgress(85);

		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		if (victoryflag) {
			newplant.SetTopLeft(0, 0);
			newplant.ShowBitmap();
			if (CGameState::level == 2) {
				wallnut.SetTopLeft(232, 91);
				wallnut.ShowBitmap();
			}
			else if (CGameState::level == 3) {
				cherrybomb.SetTopLeft(232, 91);
				cherrybomb.ShowBitmap();
			}
			else if (CGameState::level == 4) {
				conehead.SetTopLeft(232, 91);
				conehead.ShowBitmap();
			}
			else if (CGameState::level == 5) {
				snowpea.SetTopLeft(232, 91);
				snowpea.ShowBitmap();
			}
			else if (CGameState::level == 6) {
				bucket.SetTopLeft(232, 91);
				bucket.ShowBitmap();
			}
			else if (CGameState::level == 7) {
				potatomine.SetTopLeft(232, 91);
				potatomine.ShowBitmap();
			}
			else if (CGameState::level == 8) {
				newspaper.SetTopLeft(232, 91);
				newspaper.ShowBitmap();
			}
			else if (CGameState::level == 9) {
				squash.SetTopLeft(0, 0);
				squash.ShowBitmap();
			}
			else if (CGameState::level == 10) {
				puff_shroom.SetTopLeft(232, 91);
				puff_shroom.ShowBitmap();
			}
			else if (CGameState::level == 11) {
				victory.SetTopLeft(232, 91);
				victory.ShowBitmap();
			}
		}
		else {
			if (night_mode) {
				loose_night.SetTopLeft(0, 0);
				loose_night.ShowBitmap();
			}
			else {
				loose.SetTopLeft(0, 0);
				loose.ShowBitmap();
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28)
	{
		picX = picY = 0;
	}


	CGameStateRun::~CGameStateRun()
	{
	}

	void CGameStateRun::OnInit()
	{

		ShowInitProgress(33);

		chooser.LoadBitmap("Bitmaps/ChooserBackground.bmp");
		background.LoadBitmap("Bitmaps/Background.bmp");
		background_night.LoadBitmap("Bitmaps/Background_1.bmp");
		shovel_card.LoadBitmap();
		ShowInitProgress(50);

		sun.LoadBitmap();
		sun_flower_card.LoadBitmap();
		pea_shooter_card.LoadBitmap();
		wallnut_card.LoadBitmap();
		cherrybomb_card.LoadBitmap();
		ice_shooter_card.LoadBitmap();
		potatomine_card.LoadBitmap();
		shooter_card.LoadBitmap();
		squash_card.LoadBitmap();


		CAudio::Instance()->Load(AUDIO_START, "sounds\\startgame.mp3");
		CAudio::Instance()->Load(AUDIO_START_NIGHT, "sounds\\night_bgm.mp3");
		CAudio::Instance()->Load(AUDIO_BOMB, "sounds\\bomb.mp3");
		CAudio::Instance()->Load(AUDIO_VICTORY, "sounds\\victory.mp3");

		//CGameState::level = 1;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitTest(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		normalzombie_vector.push_back(make_shared<YNormalZombie>(150, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(260, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(500, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 1));
		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel1(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1250, 0));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1560, 4));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1850, 2, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1900, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2000, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2050, 4));
		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel2(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// wallnut morning
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 4));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1550, 1, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1600, 0));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1650, 2));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2190, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2270, 4));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2320, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2390, 1));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel3(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// cherrybomb morning
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1150, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 0));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1550, 4, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1650, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1860, 0));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2270, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2320, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2350, 4));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2420, 0));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel4(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// cone zombie night
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1150, 1, "conehead"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 0));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1500, 4, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1650, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1900, 0));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2350, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2350, 1, "conehead"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2400, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2550, 0));
		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel5(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// ice shooter morning
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1000, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 3));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 2, "conehead"));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1950, 4, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2100, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2350, 3, "conehead"));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2850, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2900, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2900, 4, "conehead"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3050, 1));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel6(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// bucket night
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1000, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 4));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1460, 2, "bucket"));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1950, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2100, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2370, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2430, 0, "bucket"));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2850, 2, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2950, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3200, 3));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel7(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// potatomine morning
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 0, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1520, 4));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1750, 1, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1800, 3, "conehead"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1870, 2));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2150, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2230, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2250, 0, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2370, 4));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel8(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// newspaper night
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 1, "newspaper"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1460, 3));


		normalzombie_vector.push_back(make_shared<YNormalZombie>(1850, 2, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1950, 0, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2100, 4));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2250, 3));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2850, 4, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2920, 3, "newspaper"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3000, 0));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3120, 2));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel9(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// squash morning
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 4, "newspaper"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1460, 1));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(1680, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1750, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1750, 4, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1870, 0));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2480, 2));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2550, 3));

		return normalzombie_vector;
	}

	std::vector<shared_ptr<YNormalZombie>> zombieInitLevel10(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
		// shooter night
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1270, 4, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1480, 1));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(1600, 2));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(2250, 0, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2300, 3, "bucket"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2470, 0));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(2650, 1, "newspaper"));

		normalzombie_vector.push_back(make_shared<YNormalZombie>(3150, 3, "flag"));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3170, 4));
		normalzombie_vector.push_back(make_shared<YNormalZombie>(3320, 2));

		return normalzombie_vector;
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 0;
		const int ANIMATION_SPEED = 15;

		CAudio::Instance()->Stop(AUDIO_MAIN);

		flag = 0;
		sun_amount = 50;
		generateSunFlowerFlag = false;
		generatePeaShooterFlag = false;
		generateWallNutFlag = false;
		generateCherryBombFlag = false;
		generateIceShooterFlag = false;
		generatePotatomineFlag = false;
		generateShooterFlag = false;
		generateSquashFlag = false;


		sun_flower_card.SetIsAlive(false);
		pea_shooter_card.SetIsAlive(false);
		wallnut_card.SetIsAlive(false);
		cherrybomb_card.SetIsAlive(false);
		ice_shooter_card.SetIsAlive(false);
		potatomine_card.SetIsAlive(false);
		shooter_card.SetIsAlive(false);
		squash_card.SetIsAlive(false);

		shovelFlag = false;
		sun_flower_card_delay_flag = 0;
		peashooter_card_delay_flag = 0;
		wallnut_card_delay_flag = 0;
		cherrybomb_card_delay_flag = 0;
		iceshooter_card_delay_flag = 0;
		potatomine_card_delay_flag = 0;
		shooter_card_delay_flag = 0;
		squash_card_delay_flag = 0;

		car0 = YCar(0);
		car1 = YCar(1);
		car2 = YCar(2);
		car3 = YCar(3);
		car4 = YCar(4);
		car0.LoadBitmap();
		car1.LoadBitmap();
		car2.LoadBitmap();
		car3.LoadBitmap();
		car4.LoadBitmap();
		car0_flag = true;
		car1_flag = true;
		car2_flag = true;
		car3_flag = true;
		car4_flag = true;
		car0_sound_flag = true;
		car1_sound_flag = true;
		car2_sound_flag = true;
		car3_sound_flag = true;
		car4_sound_flag = true;
		zombie_home_flag = true;
		normalzombie_vector.clear();
		sunflower_vector.clear();
		peashooter_vector.clear();
		wallnut_vector.clear();
		iceshooter_vector.clear();
		shooter_vector.clear();
		squash_vector.clear();

		map.clear();
		zombie_fast_mode = false;
		sun.SetY(-200);

		if (CGameState::level == 0) {
			night_mode = false;
			normalzombie_vector = zombieInitTest(normalzombie_vector);
		}
		else if (CGameState::level == 1) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel1(normalzombie_vector);
		}
		else if (CGameState::level == 2) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel2(normalzombie_vector);
		}
		else if (CGameState::level == 3) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel3(normalzombie_vector);
		}
		else if (CGameState::level == 4) {
			night_mode = true;
			normalzombie_vector = zombieInitLevel4(normalzombie_vector);
		}
		else if (CGameState::level == 5) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel5(normalzombie_vector);
		}
		else if (CGameState::level == 6) {
			night_mode = true;
			normalzombie_vector = zombieInitLevel6(normalzombie_vector);
		}
		else if (CGameState::level == 7) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel7(normalzombie_vector);
		}
		else if (CGameState::level == 8) {
			night_mode = true;
			normalzombie_vector = zombieInitLevel8(normalzombie_vector);
		}
		else if (CGameState::level == 9) {
			night_mode = false;
			normalzombie_vector = zombieInitLevel9(normalzombie_vector);
		}
		else if (CGameState::level == 10) {
			night_mode = true;
			normalzombie_vector = zombieInitLevel10(normalzombie_vector);
		}

		if (night_mode) {
			CAudio::Instance()->Play(AUDIO_START_NIGHT, true);
			sun.SetIsAlive(false);
		}
		else {
			CAudio::Instance()->Play(AUDIO_START, true);
			sun.SetIsAlive(true);
		}

		for (auto normalzombie_sp : normalzombie_vector) {
			normalzombie_sp->LoadBitmap();
		}
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_Z = 90;
		const char KEY_S = 83;
		const char KEY_D = 68;

		if (nChar == KEY_Z) {
			zombie_fast_mode = true;
		}
		if (nChar == KEY_S) {
			sun_amount = 500;
		}
		if (nChar == KEY_D) {
			for (auto z : normalzombie_vector) {
				z->SetIsAlive(false);
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_Z = 90;

		if (nChar == KEY_Z) {
			zombie_fast_mode = false;
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		if (generateSunFlowerFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YSunFlower>(tx, ty);
			sp->LoadBitmap();
			sunflower_vector.push_back(sp);
			generateSunFlowerFlag = false;
		}
		else if (generatePeaShooterFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YPeaShooter>(tx, ty);
			sp->LoadBitmap();
			peashooter_vector.push_back(sp);
			generatePeaShooterFlag = false;
		}
		else if (CGameState::level > 1 && generateWallNutFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YWallNut>(tx, ty);
			sp->LoadBitmap();
			wallnut_vector.push_back(sp);
			generateWallNutFlag = false;
		}
		else if (CGameState::level > 2 && generateCherryBombFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_BOMB, false);
			auto sp = make_shared<YCherryBomb>(point.x, point.y);
			sp->LoadBitmap();
			cherrybomb_vector.push_back(sp);
			generateCherryBombFlag = false;
		}
		else if (CGameState::level > 4 && generateIceShooterFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YIceShooter>(tx, ty);
			sp->LoadBitmap();
			iceshooter_vector.push_back(sp);
			generateIceShooterFlag = false;
		}
		else if (CGameState::level > 6 && generatePotatomineFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YPotatoMine>(tx, ty);
			sp->LoadBitmap();
			potatomine_vector.push_back(sp);
			generatePotatomineFlag = false;
		}
		else if (CGameState::level > 8 && generateSquashFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YSquash>(tx, ty);
			sp->LoadBitmap();
			squash_vector.push_back(sp);
			generateSquashFlag = false;
		}
		else if (CGameState::level > 9 && generateShooterFlag && !map.checkmyMap(point.x, point.y) && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			CAudio::Instance()->Play(AUDIO_PLANTS, false);
			int tx = map.getXmyMapLocation(point.x, point.y);
			int ty = map.getYmyMapLocation(point.x, point.y);
			map.setmyMap(point.x, point.y);

			auto sp = make_shared<YShooter>(tx, ty);
			sp->LoadBitmap();
			shooter_vector.push_back(sp);
			generateShooterFlag = false;
		}

		else if (shovelFlag && point.x > 30 && point.x < 770 && point.y>78 && point.y < 571) {
			map.unsetmyMap(point.x, point.y);
			shovelFlag = false;
		}

		// sun
		if (point.x > sun.GetX() && point.y > sun.GetY() &&
			point.x < sun.GetX() + 75 && point.y < sun.GetY() + 75 && sun.IsAlive()) {
			CAudio::Instance()->Play(AUDIO_SUNPICK, false);
			sun.SetIsAlive(false);
			sun_amount += 25;
			sun.SetY(-400);
		}

		for (size_t i = 0; i < sunflower_vector.size(); i++) {
			if (sunflower_vector.at(i)->GetSunIsAlive() &&
				point.x > sunflower_vector.at(i)->GetSunX() &&
				point.x < sunflower_vector.at(i)->GetSunX() + 75 &&
				point.y > sunflower_vector.at(i)->GetSunY() &&
				point.y < sunflower_vector.at(i)->GetSunY() + 75
				) {
				CAudio::Instance()->Play(AUDIO_SUNPICK, false);
				sun_amount += 25;
				sunflower_vector.at(i)->initSun();
			}
		}
		// card
		if (point.x > sun_flower_card.GetX() && point.y > sun_flower_card.GetY() && point.x < sun_flower_card.GetX() + 65 && point.y < sun_flower_card.GetY() + 90 && sun_flower_card.IsAlive()) {
			sun_flower_card.SetIsAlive(false);
			sun_amount -= sun_flower_card.GetSunCost();
			generateSunFlowerFlag = true;
			sun_flower_card_delay_flag = 150;
		}
		else if (point.x > pea_shooter_card.GetX() && point.y > pea_shooter_card.GetY() && point.x < pea_shooter_card.GetX() + 65 && point.y < pea_shooter_card.GetY() + 90 && pea_shooter_card.IsAlive()) {
			pea_shooter_card.SetIsAlive(false);
			sun_amount -= pea_shooter_card.GetSunCost();
			generatePeaShooterFlag = true;
			peashooter_card_delay_flag = 150;
		}
		else if (CGameState::level > 1 && point.x > wallnut_card.GetX() && point.y > wallnut_card.GetY() && point.x < wallnut_card.GetX() + 65 && point.y < wallnut_card.GetY() + 90 && wallnut_card.IsAlive()) {
			wallnut_card.SetIsAlive(false);
			sun_amount -= wallnut_card.GetSunCost();
			generateWallNutFlag = true;
			wallnut_card_delay_flag = 150;
		}
		else if (CGameState::level > 2 && point.x > cherrybomb_card.GetX() && point.y > cherrybomb_card.GetY() && point.x < cherrybomb_card.GetX() + 65 && point.y < cherrybomb_card.GetY() + 90 && cherrybomb_card.IsAlive()) {
			cherrybomb_card.SetIsAlive(false);
			sun_amount -= cherrybomb_card.GetSunCost();
			generateCherryBombFlag = true;
			cherrybomb_card_delay_flag = 150;
		}
		else if (CGameState::level > 4 && point.x > ice_shooter_card.GetX() && point.y > ice_shooter_card.GetY() && point.x < ice_shooter_card.GetX() + 65 && point.y < ice_shooter_card.GetY() + 90 && ice_shooter_card.IsAlive()) {
			ice_shooter_card.SetIsAlive(false);
			sun_amount -= ice_shooter_card.GetSunCost();
			generateIceShooterFlag = true;
			iceshooter_card_delay_flag = 150;
		}
		else if (CGameState::level > 6 && point.x > potatomine_card.GetX() && point.y > potatomine_card.GetY() && point.x < potatomine_card.GetX() + 65 && point.y < potatomine_card.GetY() + 90 && potatomine_card.IsAlive()) {
			potatomine_card.SetIsAlive(false);
			sun_amount -= potatomine_card.GetSunCost();
			generatePotatomineFlag = true;
			potatomine_card_delay_flag = 150;
		}
		else if (CGameState::level > 8 && point.x > squash_card.GetX() && point.y > squash_card.GetY() && point.x < squash_card.GetX() + 65 && point.y < squash_card.GetY() + 90 && squash_card.IsAlive()) {
			squash_card.SetIsAlive(false);
			sun_amount -= squash_card.GetSunCost();
			generateSquashFlag = true;
			squash_card_delay_flag = 150;
		}
		else if (CGameState::level > 9 && point.x > shooter_card.GetX() && point.y > shooter_card.GetY() && point.x < shooter_card.GetX() + 65 && point.y < shooter_card.GetY() + 90 && shooter_card.IsAlive()) {
			shooter_card.SetIsAlive(false);
			sun_amount -= shooter_card.GetSunCost();
			generateShooterFlag = true;
			shooter_card_delay_flag = 150;
		}
		else if (point.x > shovel_card.GetX() && point.y > shovel_card.GetY() && point.x < shovel_card.GetX() + 82 && point.y < shovel_card.GetY() + 82) {
			shovelFlag = true;
			shovel_card.SetIsAlive(false);
		}

		if (sun_flower_card.GetSunCost() > sun_amount) {
			sun_flower_card.SetIsAlive(false);
		}
		if (pea_shooter_card.GetSunCost() > sun_amount) {
			pea_shooter_card.SetIsAlive(false);
		}
		if (CGameState::level > 1 && wallnut_card.GetSunCost() > sun_amount) {
			wallnut_card.SetIsAlive(false);
		}
		if (CGameState::level > 2 && cherrybomb_card.GetSunCost() > sun_amount) {
			cherrybomb_card.SetIsAlive(false);
		}
		if (CGameState::level > 4 && ice_shooter_card.GetSunCost() > sun_amount) {
			ice_shooter_card.SetIsAlive(false);
		}
		if (CGameState::level > 6 && potatomine_card.GetSunCost() > sun_amount) {
			potatomine_card.SetIsAlive(false);
		}
		if (CGameState::level > 8 && squash_card.GetSunCost() > sun_amount) {
			squash_card.SetIsAlive(false);
		}
		if (CGameState::level > 9 && shooter_card.GetSunCost() > sun_amount) {
			shooter_card.SetIsAlive(false);
		}
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnMove()
	{
		chooser.SetTopLeft(0, 0);

		if (picX > -500 && flag == 0) {
			picX -= 8;
		}
		else if (flag == 0) {
			Sleep(1000);
			flag = 1;
		}
		else if (picX < -220) {
			picX += 8;
		}
		else if (flag == 4 && picX == 0) {
			picX = 0;
		}
		else if (flag == 4) {
			picX += 2;
		}
		else {
			flag = 2;
			picX = -220;
		}
		if (night_mode) {
			background_night.SetTopLeft(picX, picY);
		}
		else {
			background.SetTopLeft(picX, picY);
		}


		if (flag == 2) {
			if (!night_mode) {
				sun.OnMove();
			}
			// card
			if (sun_flower_card_delay_flag > 0) {
				sun_flower_card_delay_flag--;
			}
			if (peashooter_card_delay_flag > 0) {
				peashooter_card_delay_flag--;
			}
			if (CGameState::level > 1 && wallnut_card_delay_flag > 0) {
				wallnut_card_delay_flag--;
			}
			if (CGameState::level > 2 && cherrybomb_card_delay_flag > 0) {
				cherrybomb_card_delay_flag--;
			}
			if (CGameState::level > 4 && iceshooter_card_delay_flag > 0) {
				iceshooter_card_delay_flag--;
			}
			if (CGameState::level > 6 && potatomine_card_delay_flag > 0) {
				potatomine_card_delay_flag--;
			}
			if (CGameState::level > 8 && squash_card_delay_flag > 0) {
				squash_card_delay_flag--;
			}
			if (CGameState::level > 9 && shooter_card_delay_flag > 0) {
				shooter_card_delay_flag--;
			}
			// shovel the plant
			for (size_t i = 0; i < sunflower_vector.size(); i++) {
				if (!map.checkmyMap(sunflower_vector.at(i)->GetX(), sunflower_vector.at(i)->GetY())) {
					sunflower_vector.erase(sunflower_vector.begin() + i);	//if map is zero, delete the plant
				}
				else {
					sunflower_vector.at(i)->OnMove();
				}
			}
			for (size_t i = 0; i < peashooter_vector.size(); i++) {
				if (!map.checkmyMap(peashooter_vector.at(i)->GetX(), peashooter_vector.at(i)->GetY())) {
					peashooter_vector.erase(peashooter_vector.begin() + i);	//if map is zero, delete the plant
				}
				else {
					peashooter_vector.at(i)->OnMove();
				}
			}
			if (CGameState::level > 1) {
				for (size_t i = 0; i < wallnut_vector.size(); i++) {
					if (!map.checkmyMap(wallnut_vector.at(i)->GetX(), wallnut_vector.at(i)->GetY())) {
						wallnut_vector.erase(wallnut_vector.begin() + i);	//if map is zero, delete the plant
					}
					else {
						wallnut_vector.at(i)->OnMove();
					}
				}
			}
			if (CGameState::level > 2) {
				for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
					cherrybomb_vector.at(i)->OnMove();
				}
			}
			if (CGameState::level > 4) {
				for (size_t i = 0; i < iceshooter_vector.size(); i++) {
					if (!map.checkmyMap(iceshooter_vector.at(i)->GetX(), iceshooter_vector.at(i)->GetY())) {
						iceshooter_vector.erase(iceshooter_vector.begin() + i);	//if map is zero, delete the plant
					}
					else {
						iceshooter_vector.at(i)->OnMove();
					}
				}
			}
			if (CGameState::level > 6) {
				for (size_t i = 0; i < potatomine_vector.size(); i++) {
					if (!map.checkmyMap(potatomine_vector.at(i)->GetX(), potatomine_vector.at(i)->GetY())) {
						potatomine_vector.erase(potatomine_vector.begin() + i);	//if map is zero, delete the plant
					}
					else {
						potatomine_vector.at(i)->OnMove();
					}
				}
			}
			if (CGameState::level > 8) {
				for (size_t i = 0; i < squash_vector.size(); i++) {
					if (!map.checkmyMap(squash_vector.at(i)->GetX(), squash_vector.at(i)->GetY())) {
						squash_vector.erase(squash_vector.begin() + i);	//if map is zero, delete the plant
					}
					else {
						squash_vector.at(i)->OnMove();
					}
				}
			}
			if (CGameState::level > 9) {
				for (size_t i = 0; i < shooter_vector.size(); i++) {
					if (!map.checkmyMap(shooter_vector.at(i)->GetX(), shooter_vector.at(i)->GetY())) {
						shooter_vector.erase(shooter_vector.begin() + i);	//if map is zero, delete the plant
					}
					else {
						shooter_vector.at(i)->OnMove();
					}
				}
			}

			// zombie
			for (size_t i = 0; i < normalzombie_vector.size(); i++) {
				// zombie eat plant
				for (size_t j = 0; j < sunflower_vector.size(); j++) {
					if (sunflower_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
						sunflower_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
						if (sunflower_vector.at(j)->GetBlood() < 1) {
							sunflower_vector.at(j)->SetIsAlive(false);
							map.unsetmyMap(sunflower_vector.at(j)->GetX(), sunflower_vector.at(j)->GetY());
							sunflower_vector.erase(sunflower_vector.begin() + j);
						}
					}
				}

				for (size_t j = 0; j < peashooter_vector.size(); j++) {
					if (peashooter_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
						peashooter_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
						if (peashooter_vector.at(j)->GetBlood() < 1) {
							peashooter_vector.at(j)->SetIsAlive(false);
							map.unsetmyMap(peashooter_vector.at(j)->GetX(), peashooter_vector.at(j)->GetY());
							peashooter_vector.erase(peashooter_vector.begin() + j);
						}
					}
				}
				if (CGameState::level > 1) {
					for (size_t j = 0; j < wallnut_vector.size(); j++) {
						if (wallnut_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
							wallnut_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
							if (wallnut_vector.at(j)->GetBlood() < 1) {
								wallnut_vector.at(j)->SetIsAlive(false);
								map.unsetmyMap(wallnut_vector.at(j)->GetX(), wallnut_vector.at(j)->GetY());
								wallnut_vector.erase(wallnut_vector.begin() + j);
							}
						}
					}
				}
				if (CGameState::level > 2) {
					if (!cherrybomb_vector.empty() && cherrybomb_vector.at(0)->Bomb()
						&& cherrybomb_vector.at(0)->checkNearbyZombies(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY())) {
						normalzombie_vector.at(i)->SetBombFlag();
						normalzombie_vector.at(i)->OnMove(std::string("bomb"));
					}
					//else if (CGameState::level > 6 && !potatomine_vector.empty() && potatomine_vector.at(0)->Bomb()
					//	&& potatomine_vector.at(0)->checkNearbyZombies(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY())) {
					//	normalzombie_vector.at(i)->SetBombFlag();
					//	normalzombie_vector.at(i)->OnMove(std::string("bomb"));
					//}
					if (CGameState::level > 6 && !potatomine_vector.empty()) {
						for (size_t j = 0; j < potatomine_vector.size(); j++) {
							if (potatomine_vector.at(j)->Bomb()
								&& potatomine_vector.at(j)->checkNearbyZombies(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY())) {
								normalzombie_vector.at(i)->SetBombFlag();
								normalzombie_vector.at(i)->OnMove(std::string("bomb"));
							}
						}
					}

					if (map.checkmyMap(normalzombie_vector.at(i)->GetX() + 80, normalzombie_vector.at(i)->GetY() + 35)
						&& !map.checkmyMap(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 35)
						&& normalzombie_vector.at(i)->IsAlive()) {
						normalzombie_vector.at(i)->OnMove(std::string("attack"));
					}
					else if (!normalzombie_vector.at(i)->IsAlive()) {
						normalzombie_vector.at(i)->OnMove(std::string("die"));
					}
					else {
						if (zombie_fast_mode)
							normalzombie_vector.at(i)->OnMove(std::string("walk"), true);
						else
							normalzombie_vector.at(i)->OnMove(std::string("walk"));
					}

					if (CGameState::level > 4) {
						for (size_t j = 0; j < iceshooter_vector.size(); j++) {
							if (iceshooter_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
								iceshooter_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
								if (iceshooter_vector.at(j)->GetBlood() < 1) {
									iceshooter_vector.at(j)->SetIsAlive(false);
									map.unsetmyMap(iceshooter_vector.at(j)->GetX(), iceshooter_vector.at(j)->GetY());
									iceshooter_vector.erase(iceshooter_vector.begin() + j);
								}
							}
						}
					}

					if (CGameState::level > 6) {
						for (size_t j = 0; j < potatomine_vector.size(); j++) {
							if (potatomine_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
								potatomine_vector.at(j)->SetZombieChecked();
								potatomine_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
								if (potatomine_vector.at(j)->GetBlood() < 1) {
									potatomine_vector.at(j)->SetIsAlive(false);
									map.unsetmyMap(potatomine_vector.at(j)->GetX(), potatomine_vector.at(j)->GetY());
									potatomine_vector.erase(potatomine_vector.begin() + j);
								}
							}
						}
					}
					if (CGameState::level > 8) {
						for (size_t j = 0; j < squash_vector.size(); j++) {
							if (squash_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
								squash_vector.at(j)->SetZombieChecked();
								normalzombie_vector.at(i)->SetIsAlive(false);
								if (!squash_vector.at(j)->IsAlive()) {
									map.unsetmyMap(squash_vector.at(j)->GetX(), squash_vector.at(j)->GetY());
									squash_vector.erase(squash_vector.begin() + j);
								}
							}
						}
					}

					if (CGameState::level > 9) {
						for (size_t j = 0; j < shooter_vector.size(); j++) {
							if (normalzombie_vector.at(i)->IsAlive() && shooter_vector.at(j)->isClose(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
								shooter_vector.at(j)->SetClose(true);
							}
							else if (!normalzombie_vector.at(i)->IsAlive()) {
								shooter_vector.at(j)->SetClose(false);
							}
							if (shooter_vector.at(j)->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX() + 70, normalzombie_vector.at(i)->GetY() + 30)) {
								shooter_vector.at(j)->LostBlood(normalzombie_vector.at(i)->GetAttackPower());
								if (shooter_vector.at(j)->GetBlood() < 1) {
									shooter_vector.at(j)->SetIsAlive(false);
									map.unsetmyMap(shooter_vector.at(j)->GetX(), shooter_vector.at(j)->GetY());
									shooter_vector.erase(shooter_vector.begin() + j);
								}
							}
						}
					}

				}
				else {
					if (map.checkmyMap(normalzombie_vector.at(i)->GetX() + 80, normalzombie_vector.at(i)->GetY() + 35)
						&& !map.checkmyMap(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 35)
						&& normalzombie_vector.at(i)->IsAlive()) {
						normalzombie_vector.at(i)->OnMove(std::string("attack"));
					}
					else if (!normalzombie_vector.at(i)->IsAlive()) {
						normalzombie_vector.at(i)->OnMove(std::string("die"));
					}
					else {
						if (zombie_fast_mode)
							normalzombie_vector.at(i)->OnMove(std::string("walk"), true);
						else
							normalzombie_vector.at(i)->OnMove(std::string("walk"));
					}
				}

				if (CGameState::level > 2) {
					for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
						if (!cherrybomb_vector.at(i)->IsAlive()) {
							cherrybomb_vector.erase(cherrybomb_vector.begin() + i);
						}
					}
				}
				if (CGameState::level > 6) {
					for (size_t i = 0; i < potatomine_vector.size(); i++) {
						if (!potatomine_vector.at(i)->IsAlive()) {
							map.unsetmyMap(potatomine_vector.at(i)->GetX(), potatomine_vector.at(i)->GetY());
							potatomine_vector.erase(potatomine_vector.begin() + i);
						}
					}
				}

				// zombie walk to car -> car move
				if (car0.IsAlive() && (normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() + 10) || !car0_flag) {
					if (car0_sound_flag) {
						CAudio::Instance()->Play(AUDIO_CAR, false);
						car0_sound_flag = false;
					}
					car0_flag = false;
					car0.OnMove();
				}
				if (car1.IsAlive() && (normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 10) || !car1_flag) {
					if (car1_sound_flag) {
						CAudio::Instance()->Play(AUDIO_CAR, false);
						car1_sound_flag = false;
					}
					car1_flag = false;
					car1.OnMove();
				}
				if (car2.IsAlive() && (normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 10) || !car2_flag) {
					if (car2_sound_flag) {
						CAudio::Instance()->Play(AUDIO_CAR, false);
						car2_sound_flag = false;
					}
					car2_flag = false;
					car2.OnMove();
				}
				if (car3.IsAlive() && (normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 10) || !car3_flag) {
					if (car3_sound_flag) {
						CAudio::Instance()->Play(AUDIO_CAR, false);
						car3_sound_flag = false;
					}
					car3_flag = false;
					car3.OnMove();
				}
				if (car4.IsAlive() && (normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 10) || !car4_flag) {
					if (car4_sound_flag) {
						CAudio::Instance()->Play(AUDIO_CAR, false);
						car4_sound_flag = false;
					}
					car4_flag = false;
					car4.OnMove();
				}
				// car hits zombies
				if (car0.IsAlive() && (normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() - 10)) {
					normalzombie_vector.at(i)->SetIsAlive(false);
				}
				if (car1.IsAlive() && (normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 10)) {
					normalzombie_vector.at(i)->SetIsAlive(false);
				}
				if (car2.IsAlive() && (normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 10)) {
					normalzombie_vector.at(i)->SetIsAlive(false);
				}
				if (car3.IsAlive() && (normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 10)) {
					normalzombie_vector.at(i)->SetIsAlive(false);
				}
				if (car4.IsAlive() && (normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 10)) {
					normalzombie_vector.at(i)->SetIsAlive(false);
				}

				for (auto p : peashooter_vector) {
					int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
					if (p->checkBulletCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
						normalzombie_vector.at(i)->LostBlood(1);
					}
				}

				if (CGameState::level > 4) {
					for (auto p : iceshooter_vector) {
						int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
						if (p->checkBulletCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
							normalzombie_vector.at(i)->LostBlood(2);
							normalzombie_vector.at(i)->freezen();
						}
					}
				}
				if (CGameState::level > 8) {
					for (auto p : squash_vector) {
						int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
						if (p->checkPlantCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
							normalzombie_vector.at(i)->LostBlood(10000);
						}
					}
				}
				if (CGameState::level > 9) {
					for (auto p : shooter_vector) {
						int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
						if (p->checkBulletCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
							normalzombie_vector.at(i)->LostBlood(1);
						}
					}
				}

				if (normalzombie_vector.at(i)->GetX() > 900 && !normalzombie_vector.at(i)->IsAlive()) {
					normalzombie_vector.erase(normalzombie_vector.begin() + i);
				}

			}

			for (size_t i = 0; i < normalzombie_vector.size(); i++) {
				if (normalzombie_vector.at(i)->GetX() < -70 && normalzombie_vector.at(i)->IsAlive()) {
					CAudio::Instance()->Stop(AUDIO_START);
					flag = 4;
				}
			}

			// card
			if (sun_amount >= sun_flower_card.GetSunCost() && sun_flower_card_delay_flag == 0) {
				sun_flower_card.SetIsAlive(true);
			}
			if (sun_amount >= pea_shooter_card.GetSunCost() && peashooter_card_delay_flag == 0) {
				pea_shooter_card.SetIsAlive(true);
			}
			if (CGameState::level > 1 && sun_amount >= wallnut_card.GetSunCost() && wallnut_card_delay_flag == 0) {
				wallnut_card.SetIsAlive(true);
			}
			if (CGameState::level > 2 && sun_amount >= cherrybomb_card.GetSunCost() && cherrybomb_card_delay_flag == 0) {
				cherrybomb_card.SetIsAlive(true);
			}
			if (CGameState::level > 4 && sun_amount >= ice_shooter_card.GetSunCost() && iceshooter_card_delay_flag == 0) {
				ice_shooter_card.SetIsAlive(true);
			}
			if (CGameState::level > 6 && sun_amount >= potatomine_card.GetSunCost() && potatomine_card_delay_flag == 0) {
				potatomine_card.SetIsAlive(true);
			}
			if (CGameState::level > 8 && sun_amount >= squash_card.GetSunCost() && squash_card_delay_flag == 0) {
				squash_card.SetIsAlive(true);
			}
			if (CGameState::level > 9 && sun_amount >= shooter_card.GetSunCost() && shooter_card_delay_flag == 0) {
				shooter_card.SetIsAlive(true);
			}
			if (!shovelFlag) {
				shovel_card.SetIsAlive(true);
			}

			// go to game state over
			if (normalzombie_vector.empty()) {
				CAudio::Instance()->Stop(AUDIO_START);
				CAudio::Instance()->Stop(AUDIO_START_NIGHT);
				CAudio::Instance()->Play(AUDIO_VICTORY, false);
				victoryflag = 1;
				CGameState::level += 1;
				GotoGameState(GAME_STATE_OVER);
			}
		}

		if (flag == 4) {
			if (zombie_home_flag) {
				normalzombie_vector.at(0)->SetX(10);
				normalzombie_vector.at(0)->SetY(300);
				zombie_home_flag = false;
			}
			normalzombie_vector.at(0)->OnMove(std::string("walk"));
			if (normalzombie_vector.at(0)->GetX() < -35) {
				CAudio::Instance()->Play(AUDIO_MENUTOGAME, false);
				victoryflag = 0;
				GotoGameState(GAME_STATE_OVER);
			}
		}


		// 修改cursor樣式
		//if (generateSunFlowerFlag) {
		//	SetCursor(AfxGetApp()->LoadCursor(".\\bitmaps\\SunFlower\\SunFlower_0.bmp"));
		//}

	}

	void CGameStateRun::OnShow()
	{
		if (night_mode) {
			background_night.ShowBitmap();
		}
		else {
			background.ShowBitmap();
		}

		if (flag == 4) {
			normalzombie_vector.at(0)->OnShow(std::string("walk"));
		}

		if (flag == 2) {

			for (size_t i = 0; i < sunflower_vector.size(); i++) {
				sunflower_vector.at(i)->OnShow();
			}
			if (CGameState::level > 1) {
				for (size_t i = 0; i < wallnut_vector.size(); i++) {
					wallnut_vector.at(i)->OnShow();
				}
			}
			if (CGameState::level > 2) {
				for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
					cherrybomb_vector.at(i)->OnShow();
				}
			}
			if (CGameState::level > 4) {
				for (size_t i = 0; i < iceshooter_vector.size(); i++) {
					iceshooter_vector.at(i)->OnShow();
				}
			}
			if (CGameState::level > 6) {
				for (size_t i = 0; i < potatomine_vector.size(); i++) {
					potatomine_vector.at(i)->OnShow();
				}
			}
			if (CGameState::level > 8) {
				for (size_t i = 0; i < squash_vector.size(); i++) {
					squash_vector.at(i)->OnShow();
				}
			}
			if (CGameState::level > 9) {
				for (size_t i = 0; i < shooter_vector.size(); i++) {
					shooter_vector.at(i)->OnShow();
				}
			}
			for (size_t i = 0; i < peashooter_vector.size(); i++) {
				peashooter_vector.at(i)->OnShow();
			}
			for (auto normalzombie : normalzombie_vector) {
				if (normalzombie->GetX() < 950) {
					if (map.checkmyMap(normalzombie->GetX() + 80, normalzombie->GetY() + 35)
						&& !map.checkmyMap(normalzombie->GetX() + 90, normalzombie->GetY() + 35)
						&& normalzombie->IsAlive())
					{
						normalzombie->OnShow(std::string("attack"));
					}
					else if (!normalzombie->IsAlive()) {
						normalzombie->OnShow(std::string("die"));
					}
					else {
						normalzombie->OnShow(std::string("walk"));
					}
				}
			}

			sun.OnShow();
			chooser.ShowBitmap();
			shovel_card.OnShow();
			sun_flower_card.OnShow();
			pea_shooter_card.OnShow();
			if (CGameState::level > 1) {
				wallnut_card.OnShow();
			}
			if (CGameState::level > 2) {
				cherrybomb_card.OnShow();
			}
			if (CGameState::level > 4) {
				ice_shooter_card.OnShow();
			}
			if (CGameState::level > 6) {
				potatomine_card.OnShow();
			}
			if (CGameState::level > 8) {
				squash_card.OnShow();
			}
			if (CGameState::level > 9) {
				shooter_card.OnShow();
			}
			car0.OnShow();
			car1.OnShow();
			car2.OnShow();
			car3.OnShow();
			car4.OnShow();

		}

		// sun amount
		if (flag == 2) {
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f, *fp;
			f.CreatePointFont(90, "微軟正黑體");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkMode(TRANSPARENT);

			pDC->SetTextColor(RGB(0, 0, 0));

			if (sun_amount == 50)
				pDC->TextOut(30, 62, "50");
			else if (sun_amount == 0)
				pDC->TextOut(34, 62, "0");
			else if (sun_amount == 25)
				pDC->TextOut(30, 62, "25");
			else if (sun_amount == 75)
				pDC->TextOut(30, 62, "75");
			else if (sun_amount == 100)
				pDC->TextOut(26, 62, "100");
			else if (sun_amount == 125)
				pDC->TextOut(26, 62, "125");
			else if (sun_amount == 150)
				pDC->TextOut(26, 62, "150");
			else if (sun_amount == 175)
				pDC->TextOut(26, 62, "175");
			else if (sun_amount == 200)
				pDC->TextOut(26, 62, "200");
			else if (sun_amount == 225)
				pDC->TextOut(26, 62, "225");
			else if (sun_amount == 250)
				pDC->TextOut(26, 62, "250");
			else if (sun_amount == 275)
				pDC->TextOut(26, 62, "275");
			else if (sun_amount == 300)
				pDC->TextOut(26, 62, "300");
			else if (sun_amount == 325)
				pDC->TextOut(26, 62, "325");
			else if (sun_amount == 350)
				pDC->TextOut(26, 62, "350");
			else if (sun_amount == 375)
				pDC->TextOut(26, 62, "375");
			else if (sun_amount == 400)
				pDC->TextOut(26, 62, "400");
			else if (sun_amount == 425)
				pDC->TextOut(26, 62, "425");
			else if (sun_amount == 450)
				pDC->TextOut(26, 62, "450");
			else if (sun_amount == 475)
				pDC->TextOut(26, 62, "475");
			else if (sun_amount == 500)
				pDC->TextOut(26, 62, "500");
			else if (sun_amount == 525)
				pDC->TextOut(26, 62, "525");
			else if (sun_amount == 550)
				pDC->TextOut(26, 62, "550");
			else if (sun_amount == 575)
				pDC->TextOut(26, 62, "575");
			else if (sun_amount == 600)
				pDC->TextOut(26, 62, "600");
			else if (sun_amount == 625)
				pDC->TextOut(26, 62, "625");
			else if (sun_amount == 650)
				pDC->TextOut(26, 62, "650");
			else if (sun_amount == 675)
				pDC->TextOut(26, 62, "675");
			else if (sun_amount == 700)
				pDC->TextOut(26, 62, "700");
			else {
				pDC->TextOut(26, 62, "###");
			}
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}

		// zombie amount
		if (flag == 2) {
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f, *fp;
			f.CreatePointFont(100, "微軟正黑體");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkMode(TRANSPARENT);

			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->TextOut(650, 580, "left zombie: ");

			int zombie_amount = normalzombie_vector.size();
			if (zombie_amount == 0)
				pDC->TextOut(755, 580, "0");
			else if (zombie_amount == 1)
				pDC->TextOut(755, 580, "1");
			else if (zombie_amount == 2)
				pDC->TextOut(755, 580, "2");
			else if (zombie_amount == 3)
				pDC->TextOut(755, 580, "3");
			else if (zombie_amount == 4)
				pDC->TextOut(755, 580, "4");
			else if (zombie_amount == 5)
				pDC->TextOut(755, 580, "5");
			else if (zombie_amount == 6)
				pDC->TextOut(755, 580, "6");
			else if (zombie_amount == 7)
				pDC->TextOut(755, 580, "7");
			else if (zombie_amount == 8)
				pDC->TextOut(755, 580, "8");
			else if (zombie_amount == 9)
				pDC->TextOut(755, 580, "9");
			else if (zombie_amount == 10)
				pDC->TextOut(755, 580, "10");
			else if (zombie_amount == 11)
				pDC->TextOut(755, 580, "11");
			else if (zombie_amount == 12)
				pDC->TextOut(755, 580, "12");
			else if (zombie_amount == 13)
				pDC->TextOut(755, 580, "13");
			else if (zombie_amount == 14)
				pDC->TextOut(755, 580, "14");
			else if (zombie_amount == 15)
				pDC->TextOut(755, 580, "15");
			else if (zombie_amount == 16)
				pDC->TextOut(755, 580, "16");
			else if (zombie_amount == 17)
				pDC->TextOut(755, 580, "17");
			else if (zombie_amount == 18)
				pDC->TextOut(755, 580, "18");
			else if (zombie_amount == 19)
				pDC->TextOut(755, 580, "19");
			else if (zombie_amount == 20)
				pDC->TextOut(755, 580, "20");
			else if (zombie_amount == 21)
				pDC->TextOut(755, 580, "21");
			else if (zombie_amount == 22)
				pDC->TextOut(755, 580, "22");
			else if (zombie_amount == 23)
				pDC->TextOut(755, 580, "23");
			else {
				pDC->TextOut(755, 580, "###");
			}
			pDC->SelectObject(fp);
			CDDraw::ReleaseBackCDC();
		}
	}


}