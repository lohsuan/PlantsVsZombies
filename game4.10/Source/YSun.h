
namespace game_framework {
	
	class YSun
	{
	public:
		YSun();
		void OnLButtonDown(UINT nFlags, CPoint point);
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetY(int y);
		int  GetX();
		int  GetY();
		int	 GetFloor();
	private:
		CMovingBitmap sun;
		int x, y;
		bool is_alive;
		CAnimation sunanimation;	// 利用動畫作圖形
		int floor;					// where sun stop
	};
}