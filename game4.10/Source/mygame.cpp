/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

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
	int CGameState::level = 0;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{	

	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	flag_menutogame = 0;
	ShowInitProgress(0);	// 一開始的loading進度為0%
	
	Sleep(300);
	//
	// 開始載入資料
	//
	mainmenu.LoadBitmap("Bitmaps/MainMenu.bmp");
	adventure0.LoadBitmap("Bitmaps/Adventure0.bmp", RGB(255,255,255));
	adventure1.LoadBitmap("Bitmaps/Adventure1.bmp", RGB(255,255,255));
	CAudio::Instance()->Load(AUDIO_MAIN, "sounds\\mainmenu.mp3");
	CAudio::Instance()->Play(AUDIO_MAIN, true);
	CAudio::Instance()->Load(AUDIO_MENUTOGAME, "sounds\\menutogame.mp3");
	CAudio::Instance()->Load(AUDIO_SUNPICK, "sounds\\sun_pick.mp3");
	CAudio::Instance()->Load(AUDIO_PLANTS, "sounds\\plants_sound.mp3");
	CAudio::Instance()->Load(AUDIO_CAR, "sounds\\car.mp3");

	Sleep(500);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
	
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	//const char KEY_SPACE = ' ';
	//if (nChar == KEY_SPACE)
	//	GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

//void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {
//	adventure1.SetTopLeft(470, 100);
//	adventure1.ShowBitmap();
//}

//void CGameStateInit::OnMouseHover(UINT nFlags, CPoint point) {
//	adventure1.SetTopLeft(470, 100);
//	adventure1.ShowBitmap();
//}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (point.x > 470 && point.y > 100 && point.x < 790 && point.y < 260) {
		//adventure1.ShowBitmap();
		flag_menutogame = 1;

		CAudio::Instance()->Play(AUDIO_MENUTOGAME, false);
		//Sleep(6000);

		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::OnShow()
{
	//
	// 貼上mainmenu
	//
	mainmenu.SetTopLeft(0,0);
	mainmenu.ShowBitmap();

	adventure0.SetTopLeft(470, 100);
	adventure1.SetTopLeft(470, 100);
	
	if (flag_menutogame == 0) {
		adventure0.ShowBitmap();
	} else {
		adventure1.ShowBitmap();
	}
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(170,"微軟正黑體");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	// pDC->SetBkColor(RGB(0,0,0));
	pDC->SetBkMode(TRANSPARENT);
	
	pDC->SetTextColor(RGB(0,0,0));
	pDC->TextOut(500, 270, "~ 19XX-XX-XX ~");
	pDC->SetTextColor(RGB(204, 255, 204));
	pDC->TextOut(480,320,"點擊 \"冒險模式\" 開始 !");
	// pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(5,530,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,565,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
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
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%


	Sleep(100);
	ShowInitProgress(85);	// 接個前一個狀態的進度，此處進度視為66%


	Sleep(100);
	//
	// 開始載入資料
	//
	// Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	
	if (victoryflag) {
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(350, "Algerian");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		// pDC->SetBkColor(RGB(0,0,0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 128, 66));
		pDC->TextOut(270, 220, "You beats");
		pDC->TextOut(220, 320, "All Zombies !!!");

		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	else {
		loose.SetTopLeft(0, 0);
		loose.ShowBitmap();
	}
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
	picX = picY = 0;
}


CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 開始載入資料

	chooser.LoadBitmap("Bitmaps/ChooserBackground.bmp");
	background.LoadBitmap("Bitmaps/Background.bmp");
	shovel_card.LoadBitmap();
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
	//corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	//corner.ShowBitmap(background);							// 將corner貼到background
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();
	sun.LoadBitmap();
	sun_flower_card.LoadBitmap();
	pea_shooter_card.LoadBitmap();
	wallnut_card.LoadBitmap();
	cherrybomb_card.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_START, "sounds\\startgame.mp3");	// 載入編號0的聲音ding.wav
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
	level = 3;
}
std::vector<shared_ptr<YNormalZombie>> zombieInitTest(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector);
std::vector<shared_ptr<YNormalZombie>> zombieInitLevel1(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector);
std::vector<shared_ptr<YNormalZombie>> zombieInitLevel2(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector);
std::vector<shared_ptr<YNormalZombie>> zombieInitLevel3(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector);

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

	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Stop(AUDIO_MAIN);
	CAudio::Instance()->Play(AUDIO_START, true);		
	
	flag = 0;
	sun_amount = 500;			// 一開始50個sun
	generateSunFlowerFlag = false;
	generatePeaShooterFlag = false;
	generateWallNutFlag = false;
	generateCherryBombFlag = false;
	sun_flower_card.SetIsAlive(false);
	pea_shooter_card.SetIsAlive(false);
	wallnut_card.SetIsAlive(false);
	cherrybomb_card.SetIsAlive(false);
	shovelFlag = false;
	sun_flower_card_delay_flag = 0;
	peashooter_card_delay_flag = 0;
	wallnut_card_delay_flag = 0;
	cherrybomb_card_delay_flag = 0;

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
	map.clear();
	if (level == 0) {
		normalzombie_vector = zombieInitTest(normalzombie_vector);
	}
	else if (level == 1) {
		normalzombie_vector = zombieInitLevel1(normalzombie_vector);
	}
	else if (level == 2) {
		normalzombie_vector = zombieInitLevel2(normalzombie_vector);
	}
	else if (level == 3) {
		normalzombie_vector = zombieInitLevel3(normalzombie_vector);
	}
	for (auto normalzombie_sp : normalzombie_vector) {
		normalzombie_sp->LoadBitmap();
	}
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
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1150, 2));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(1400, 3));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(1500, 2));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(1550, 0));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(1670, 1));

	//normalzombie_vector.push_back(make_shared<YNormalZombie>(1950, 4));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(2000, 2));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(2050, 3));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(2150, 1));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(2350, 4));
	//normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 2));
	return normalzombie_vector;
}
std::vector<shared_ptr<YNormalZombie>> zombieInitLevel2(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1150, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 2));

	normalzombie_vector.push_back(make_shared<YNormalZombie>(1500, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1650, 0));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1670, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1850, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1900, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2000, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2050, 1));

	normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2500, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2550, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2650, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2850, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(3050, 2));
	return normalzombie_vector;
}

std::vector<shared_ptr<YNormalZombie>> zombieInitLevel3(std::vector<shared_ptr<YNormalZombie>> normalzombie_vector) {
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1050, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1150, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1360, 2));

	normalzombie_vector.push_back(make_shared<YNormalZombie>(1500, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1650, 0));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1670, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1850, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(1900, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2000, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2050, 1));

	normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2450, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2500, 2));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2550, 3));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2650, 1));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(2850, 4));
	normalzombie_vector.push_back(make_shared<YNormalZombie>(3050, 2));
	return normalzombie_vector;
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{	
	if (generateSunFlowerFlag && !map.checkmyMap(point.x, point.y) && point.x > 100 && point.x < 840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		int tx = map.getXmyMapLocation(point.x, point.y);
		int ty = map.getYmyMapLocation(point.x, point.y);
		map.setmyMap(point.x, point.y);

		auto sp = make_shared<YSunFlower>(tx, ty);
		sp->LoadBitmap();
		sunflower_vector.push_back(sp);
		generateSunFlowerFlag = false;
	}
	else if (generatePeaShooterFlag && !map.checkmyMap(point.x, point.y) && point.x >100 && point.x<840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		int tx = map.getXmyMapLocation(point.x, point.y);
		int ty = map.getYmyMapLocation(point.x, point.y);
		map.setmyMap(point.x, point.y);
		
		auto sp = make_shared<YPeaShooter>(tx, ty);
		sp->LoadBitmap();
		peashooter_vector.push_back(sp);
		generatePeaShooterFlag = false;
	}
	else if (level > 1 && generateWallNutFlag && !map.checkmyMap(point.x, point.y) && point.x > 100 && point.x < 840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		int tx = map.getXmyMapLocation(point.x, point.y);
		int ty = map.getYmyMapLocation(point.x, point.y);
		map.setmyMap(point.x, point.y);

		auto sp = make_shared<YWallNut>(tx, ty);
		sp->LoadBitmap();
		wallnut_vector.push_back(sp);
		generateWallNutFlag = false;
	}
	else if (level > 2 && generateCherryBombFlag && !map.checkmyMap(point.x, point.y) && point.x > 100 && point.x < 840 && point.y>78 && point.y < 571) {
		CAudio::Instance()->Play(AUDIO_PLANTS, false);
		//int tx = map.getXmyMapLocation(point.x, point.y);
		//int ty = map.getYmyMapLocation(point.x, point.y);
		//map.setmyMap(point.x, point.y);

		auto sp = make_shared<YCherryBomb>(point.x, point.y);
		sp->LoadBitmap();
		cherrybomb_vector.push_back(sp);
		generateCherryBombFlag = false;
	}
	else if (shovelFlag /*&& map.checkmyMap(point.x, point.y)*/ && point.x > 100 && point.x < 840 && point.y>78 && point.y < 571) {
		//CAudio::Instance()->Play(AUDIO_PLANTS, false);
		//int tx = map.getXmyMapLocation(point.x, point.y);
		//int ty = map.getYmyMapLocation(point.x, point.y);
		map.unsetmyMap(point.x, point.y);

		shovelFlag = false;
	}

	// sun
	if (point.x > sun.GetX() && point.y > sun.GetY() && 
		point.x < sun.GetX() + 75 && point.y < sun.GetY() + 75 && sun.IsAlive()) {
		CAudio::Instance()->Play(AUDIO_SUNPICK, false);
		sun.SetIsAlive(false);
		sun_amount += 25;
		sun.SetY(-500);
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
	else if (level > 1 && point.x > wallnut_card.GetX() && point.y > wallnut_card.GetY() && point.x < wallnut_card.GetX() + 65 && point.y < wallnut_card.GetY() + 90 && wallnut_card.IsAlive()) {
		wallnut_card.SetIsAlive(false);
		sun_amount -= wallnut_card.GetSunCost();
		generateWallNutFlag = true;
		wallnut_card_delay_flag = 150;
	}
	else if (level > 2 && point.x > cherrybomb_card.GetX() && point.y > cherrybomb_card.GetY() && point.x < cherrybomb_card.GetX() + 65 && point.y < cherrybomb_card.GetY() + 90 && cherrybomb_card.IsAlive()) {
		cherrybomb_card.SetIsAlive(false);
		sun_amount -= cherrybomb_card.GetSunCost();
		generateCherryBombFlag = true;
		cherrybomb_card_delay_flag = 150;
	}
	else if (point.x > shovel_card.GetX() && point.y > shovel_card.GetY() && point.x < shovel_card.GetX() + 82 && point.y < shovel_card.GetY() + 82) {
		shovelFlag = true;
		shovel_card.SetIsAlive(false);
	}

	if (sun_flower_card.GetSunCost() > sun_amount) {
		sun_flower_card.SetIsAlive(false);
	}
	else if (pea_shooter_card.GetSunCost() > sun_amount) {
		pea_shooter_card.SetIsAlive(false);
	}
	else if (level > 1 && wallnut_card.GetSunCost() > sun_amount) {
		wallnut_card.SetIsAlive(false);
	}
	else if (level > 2 && cherrybomb_card.GetSunCost() > sun_amount) {
		cherrybomb_card.SetIsAlive(false);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	chooser.SetTopLeft(0, 0);

	if (picX > -400 && flag == 0) {
		picX -= 4;
	}// (-400,0)
	else if (flag == 0) {
		Sleep(1000);
		flag = 1;
	}
	else if (picX < -150) {
		//flag = 1;
		picX += 4;
	}
	else if (flag == 4 && picX == 0) {
		picX = 0;
	}
	else if (flag == 4) {
		picX += 2;
	}
	else {
		flag = 2;
		picX = -150;
	}
	background.SetTopLeft(picX, picY);



	if (flag==2) {
		sun.OnMove();

		if (sun_flower_card_delay_flag > 0) {
			sun_flower_card_delay_flag--;
		}
		if (peashooter_card_delay_flag > 0) {
			peashooter_card_delay_flag--;
		}
		if (level > 1 && wallnut_card_delay_flag > 0) {
			wallnut_card_delay_flag--;
		}
		if (level > 2 && cherrybomb_card_delay_flag > 0) {
			cherrybomb_card_delay_flag--;
		}
		for (size_t i = 0; i < sunflower_vector.size(); i++) {
			if (!map.checkmyMap(sunflower_vector.at(i)->GetX(), sunflower_vector.at(i)->GetY())) {
				sunflower_vector.erase(sunflower_vector.begin() + i);	//if map is zero, delete the plant
			}else{
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
		if (level > 1) {
			for (size_t i = 0; i < wallnut_vector.size(); i++) {
				if (!map.checkmyMap(wallnut_vector.at(i)->GetX(), wallnut_vector.at(i)->GetY())) {
					wallnut_vector.erase(wallnut_vector.begin() + i);	//if map is zero, delete the plant
				}
				else {
					wallnut_vector.at(i)->OnMove();
				}
			}
		}
		if (level > 2) {
			for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
				cherrybomb_vector.at(i)->OnMove();
			}
		}

		for (size_t i = 0; i < normalzombie_vector.size(); i++) {

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
			if (level > 1) {
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
			
			if (level > 2) {
				if (!cherrybomb_vector.empty() && cherrybomb_vector.at(0)->Bomb() 
					&& cherrybomb_vector.at(0)->checkNearbyZombies(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY())) {
					normalzombie_vector.at(i)->SetBombFlag();
					normalzombie_vector.at(i)->OnMove(std::string("bomb"));
				}
				else if (map.checkmyMap(normalzombie_vector.at(i)->GetX() + 80, normalzombie_vector.at(i)->GetY() + 35)
					&& !map.checkmyMap(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 35)
					&& normalzombie_vector.at(i)->IsAlive()) {
					//int t = normalzombie_vector.at(i)->GetX() + 70;
					normalzombie_vector.at(i)->OnMove(std::string("attack"));
				}
				else if (!normalzombie_vector.at(i)->IsAlive()) {
					normalzombie_vector.at(i)->OnMove(std::string("die"));
				}
				else {
					normalzombie_vector.at(i)->OnMove(std::string("walk"));
				}
			}
			else {
				if (map.checkmyMap(normalzombie_vector.at(i)->GetX() + 80, normalzombie_vector.at(i)->GetY() + 35)
					&& !map.checkmyMap(normalzombie_vector.at(i)->GetX() + 90, normalzombie_vector.at(i)->GetY() + 35)
					&& normalzombie_vector.at(i)->IsAlive()) {
					//int t = normalzombie_vector.at(i)->GetX() + 70;
					normalzombie_vector.at(i)->OnMove(std::string("attack"));
				}
				else if (!normalzombie_vector.at(i)->IsAlive()) {
					normalzombie_vector.at(i)->OnMove(std::string("die"));
				}
				else {
					normalzombie_vector.at(i)->OnMove(std::string("walk"));
				}
			}
			if (level > 2) {
				for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
					if (!cherrybomb_vector.at(i)->IsAlive()) {
						cherrybomb_vector.erase(cherrybomb_vector.begin() + i);	//if map is zero, delete the plant
					}
				}
			}

			// zombie walk to car -> car move
			if (car0.IsAlive() && (normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() - 30) || !car0_flag) {
				if (car0_sound_flag) {
					CAudio::Instance()->Play(AUDIO_CAR, false);
					car0_sound_flag = false;
				}
				car0_flag = false;
				car0.OnMove();
			}
			if (car1.IsAlive() && (normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 30) || !car1_flag) {
				if (car1_sound_flag) {
					CAudio::Instance()->Play(AUDIO_CAR, false);
					car1_sound_flag = false;
				}
				car1_flag = false;
				car1.OnMove();
			}
			if (car2.IsAlive() && (normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 30) || !car2_flag) {
				if (car2_sound_flag) {
					CAudio::Instance()->Play(AUDIO_CAR, false);
					car2_sound_flag = false;
				}
				car2_flag = false;
				car2.OnMove();
			}
			if (car3.IsAlive() && (normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 30) || !car3_flag) {
				if (car3_sound_flag) {
					CAudio::Instance()->Play(AUDIO_CAR, false);
					car3_sound_flag = false;
				}
				car3_flag = false;
				car3.OnMove();
			}
			if (car4.IsAlive() && (normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 30) || !car4_flag) {
				if (car4_sound_flag) {
					CAudio::Instance()->Play(AUDIO_CAR, false);
					car4_sound_flag = false;
				}
				car4_flag = false;
				car4.OnMove();
			}
			// car hits zombies
			if (car0.IsAlive() && (normalzombie_vector.at(i)->GetY() == 48 && normalzombie_vector.at(i)->GetX() < car0.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if (car1.IsAlive() && (normalzombie_vector.at(i)->GetY() == 152 && normalzombie_vector.at(i)->GetX() < car1.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if (car2.IsAlive() && (normalzombie_vector.at(i)->GetY() == 240 && normalzombie_vector.at(i)->GetX() < car2.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if (car3.IsAlive() && (normalzombie_vector.at(i)->GetY() == 338 && normalzombie_vector.at(i)->GetX() < car3.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			if (car4.IsAlive() && (normalzombie_vector.at(i)->GetY() == 434 && normalzombie_vector.at(i)->GetX() < car4.GetX() - 30)) {
				normalzombie_vector.at(i)->SetIsAlive(false);
			}
			for (auto p : peashooter_vector) {
				int temp_y = map.getYmyMapLocation(normalzombie_vector.at(i)->GetX(), normalzombie_vector.at(i)->GetY() + 30);
				if (p->checkBulletCollideWithZombie(normalzombie_vector.at(i)->GetX(), temp_y)) {
					normalzombie_vector.at(i)->LostBlood(1);
				}
			}

			if (normalzombie_vector.at(i)->GetX() > 900 && !normalzombie_vector.at(i)->IsAlive()) {
				normalzombie_vector.erase(normalzombie_vector.begin() + i);
			}
			
		}

		for (size_t i = 0; i < normalzombie_vector.size(); i++) {
			if (normalzombie_vector.at(i)->GetX() < 0 && normalzombie_vector.at(i)->IsAlive()) {
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
		if (level>1 && sun_amount >= wallnut_card.GetSunCost() && wallnut_card_delay_flag == 0) {
			wallnut_card.SetIsAlive(true);
		}
		if (level > 2 && sun_amount >= cherrybomb_card.GetSunCost() && cherrybomb_card_delay_flag == 0) {
			cherrybomb_card.SetIsAlive(true);
		}
		if (!shovelFlag) {
			shovel_card.SetIsAlive(true);
		}

		// go to game state over
		if (normalzombie_vector.empty()) {
			CAudio::Instance()->Stop(AUDIO_START);
			victoryflag = 1;
			level += 1;
			GotoGameState(GAME_STATE_OVER);
		}
	}

	if (flag == 4) {
		if (zombie_home_flag) {
			normalzombie_vector.at(0)->SetX(30);
			normalzombie_vector.at(0)->SetY(300);
			zombie_home_flag = false;
		}
		normalzombie_vector.at(0)->OnMove(std::string("walk"));
		if (normalzombie_vector.at(0)->GetX() < -5) {
			CAudio::Instance()->Play(AUDIO_MENUTOGAME, false);
			victoryflag = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}

	
	// 修改cursor樣式
	//if (generateSunFlowerFlag) {
	//	SetCursor(AfxGetApp()->LoadCursor(".\\bitmaps\\SunFlower\\SunFlower_0.bmp"));
	//}

	// gamemap.OnMove();
	//
	// 移動球
	//
	//for (int i = 0; i < NUMBALLS; i++)
	//	ball[i].OnMove();
	//

	// 判斷擦子是否碰到球
	//
	//for (int i = 0; i < NUMBALLS; i++)
	//	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
	//		ball[i].SetIsAlive(false);
	//		hits_left.Add(-1);
	//		//
	//		// 若剩餘碰撞次數為0，則跳到Game Over狀態
	//		//
	//		if (hits_left.GetInteger() <= 0) {
	//			CAudio::Instance()->Stop(AUDIO_START);
	//			GotoGameState(GAME_STATE_OVER);
	//		}
	//	}

}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	
	if (flag == 4) {
		normalzombie_vector.at(0)->OnShow(std::string("walk"));
	}
	
	if (flag == 2 ) {

		for (size_t i = 0; i < sunflower_vector.size(); i++) {
			sunflower_vector.at(i)->OnShow();
		}
		if (level > 1) {
			for (size_t i = 0; i < wallnut_vector.size(); i++) {
				wallnut_vector.at(i)->OnShow();
			}
		}
		if (level > 2) {
			for (size_t i = 0; i < cherrybomb_vector.size(); i++) {
				cherrybomb_vector.at(i)->OnShow();
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
		if (level > 1) {
			wallnut_card.OnShow();
		}
		if (level > 2) {
			cherrybomb_card.OnShow();
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
		else {
			pDC->TextOut(26, 62, "###");
		}
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	
}



//CPractice::CPractice() {
//	x = y = 0;
//}
//
//void CPractice::OnMove() {
//	if (y <= SIZE_Y) {
//		x += 3;
//		y += 3;
//	}
//	else {
//		x = y = 0;
//	}
//}
//
//void CPractice::LoadBitmap() {
//	pic.LoadBitmap(IDB_SNOWGIE);
//}
//
//void CPractice::OnShow() {
//	pic.SetTopLeft(x, y);
//	pic.ShowBitmap();
//}

//CGameMap::CGameMap()
//	:X(20), Y(40), MW(120), MH(100)			// 給予地圖左上角座標及每張小圖寬高
//{
//	int map_init[4][5] = { {0, 0, 1, 0, 0},		// 給予地圖陣列初值
//						  {0, 1, 2, 1, 0},
//						  {1, 2, 1, 2, 1},
//						  {2, 1, 2, 1, 2} };
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 5; j++) {
//			map[i][j] = map_init[i][j];		// 依序填入map內
//		}
//	}
//	random_num = 0;
//	bballs = NULL;
//}
//
//void CGameMap::LoadBitmap() {
//	blue.LoadBitmap(IDB_BLUE);
//	green.LoadBitmap(IDB_GREEN);
//}
//
//void CGameMap::OnShow() {
//	for (int i = 0; i < 5; i++) {			// 往右顯示五張圖
//		for (int j = 0; j < 4; j++) {		// 往下顯示四張圖
//			switch (map[j][i]) {
//				case 0:
//					break;
//				case 1:
//					blue.SetTopLeft(X + (MW*i), Y + (MH*j));	// 設定每張圖的座標
//					blue.ShowBitmap();							// 顯示設定完的座標
//					break;
//				case 2:
//					green.SetTopLeft(X + (MW*i), Y + (MH*j));	// 設定每張圖的座標
//					green.ShowBitmap();							// 顯示設定完的座標
//					break;
//				default:
//					ASSERT(0);									// map陣列不該出現0, 1, 2 之外的值
//			}
//	
//		}
//	}
//	for (int i = 0; i < random_num; i++)
//	{	
//		bballs[i].OnShow();
//	}
//}

void CBouncingBall::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void CBouncingBall::SetFloor(int floor) {
	this->floor = floor;
}

void CBouncingBall::SetVelocity(int velocity) {
	this->velocity = velocity;
	this->initial_velocity = velocity;
}

//void CGameMap::InitializeBouncingBall(int ini_index, int row, int col) {
//	const int VELOCITY = 10;							// 球的起始上升高度	
//	const int BALL_PIC_HEIGHT = 15;						// 球圖片的高度
//	int floor = Y + (row + 1)*MH - BALL_PIC_HEIGHT;		// 設定球的落下點為Map的下方
//
//	bballs[ini_index].LoadBitmap();						// 載入彈跳球的動畫
//	bballs[ini_index].SetFloor(floor);					// 設定彈跳球的起始水平面
//	bballs[ini_index].SetVelocity(VELOCITY+col);		// 設定彈跳球的初始速度，越右邊的彈越高
//	bballs[ini_index].SetXY(X+col*MW + MW/2, floor);	// 設定彈跳球的起始位置X座標為該Map一半的位置
//}
//
//void CGameMap::RandomBouncingBall() {
//	const int MAX_RAND_NUM = 10;
//	random_num = (rand() % MAX_RAND_NUM) + 1;			// 隨機1~MAX_RAND_NUM
//
//	delete[] bballs;													// 先刪掉之前所配置的空間
//	bballs = new CBouncingBall[random_num];				// 動態配置CBouncingBall 陣列
//	int ini_index = 0;								
//	for (int row = 0; row < 4; row++) {
//		for (int col = 0; col < 5; col++) {
//			if (map[row][col] != 0 && ini_index < random_num) {		// 只放球在有色的地圖且初始化的陣列索引必小於隨機的個數
//				InitializeBouncingBall(ini_index, row, col);
//				ini_index++;										
//			}
//		}
//	}
//}
//
//void CGameMap::OnKeyDown(UINT nChar) {
//	const int KEY_SPACE = 0x20;
//	if (nChar == KEY_SPACE)
//		RandomBouncingBall();	// 當空白鍵按下後隨機彈跳球
//}
//
//void CGameMap::OnMove() {
//	for (int i = 0; i < random_num; i++) {
//		bballs[i].OnMove();
//	}
//}
//
//CGameMap::~CGameMap() {
//	delete[] bballs;
//}

}