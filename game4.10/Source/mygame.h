/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include <vector>
#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "YSun.h"
#include "YCard.h"
#include "YPlants.h"
//#include "YMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_START,				// 0
		AUDIO_MAIN,
		AUDIO_MENUTOGAME,
		AUDIO_SUNPICK
	};

	
	class CPractice {
	public:
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int			  x, y;
	};
	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		//void OnMouseMove(UINT nFlags, CPoint point);
		//void OnMouseHover(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	mainmenu;								// mainmenu picture
		CMovingBitmap	loadtext;						// Loading... picture
		CMovingBitmap	adventure0;
		CMovingBitmap	adventure1;
		int				flag_menutogame;
	};


	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖的構成
	// 看懂就可以改寫自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	// class CBouncingBall;

	
	//class CGameMap {
	//public:
	//	CGameMap();
	//	void LoadBitmap();			// 載入地圖
	//	void OnShow();				// 顯示地圖
	//	void OnMove();									// 播放彈跳球的動畫
	//	void OnKeyDown(UINT);							// 處理按鍵按下後CGaneMap的反應
	//	void RandomBouncingBall();						// 隨機彈跳球的個數加入到Map中
	//	void InitializeBouncingBall(int, int, int);		// 初始化彈跳球
	//	~CGameMap();									// 解構子
	//protected:
	//	CMovingBitmap blue, green;	// 建立藍色和綠色地圖
	//	//int map[4][5];				// 建立一個地圖矩陣的index
	//	const int X, Y;				// 大地圖的左上角x, y座標
	//	const int MW, MH;			// 每張地圖的寬高度
	//	CBouncingBall* bballs;		// CBouncingBall指標
	//	int random_num;				// 隨機個數
	//};
	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
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
		//CGameMap		gamemap;	// 地圖 
		CPractice		c_practice;	// 移動物件
		
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background;	// 背景圖
		
		CMovingBitmap	help;		// 說明圖
		CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bball;		// 反覆彈跳的球
		CMovingBitmap	chooser; // practice;
		
		int				picX, picY;
		int				flag;
		YSun			sun;
		int				sun_amount;			// show on the board
		int				sun_interval_time;
		bool			generateSunFlowerFlag;
		bool			generatePeaShooterFlag;
		YSunFlowerCard  sun_flower_card;
		YPeaShooterCard  pea_shooter_card;
		int sun_flower_card_delay_flag;
		int peashooter_card_delay_flag;
		std::vector<YSunFlower>	sunflower_vector;
		std::vector<YPeaShooter>	peashooter_vector;


	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};


}