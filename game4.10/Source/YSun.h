#ifndef YSUN_H
#define YSUN_H

namespace game_framework {
	
	class YSun
	{
	public:
		YSun();
		YSun(int x, int y);
		YSun & operator= (const YSun & other);
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetIsAlive(bool alive);							// 設定是否活著
		int GetSunFlowerSunX();
		int GetSunFlowerSunY();
		void SetY(int y);
		int  GetX();
		int  GetY();
		int	 GetFloor();
	private:
		//CMovingBitmap sun;
		int x, y;
		bool is_alive;
		CAnimation sunanimation;	// 利用動畫作圖形
		int floor;					// where sun stop
		bool sunflowerflag;
		int velocity;
		bool rising;

	};
}

#endif