//
//namespace game_framework {
//	class YSun
//	{
//	public:
//		CBall();
//		void OnLButtonDown(UINT nFlags, CPoint point);
//		bool IsAlive();											// 是否活著
//		void LoadBitmap();										// 載入圖形
//		void OnMove();											// 移動
//		void OnShow();											// 將圖形貼到畫面
//		void SetXY(int nx, int ny);								// 設定圓心的座標
//		void SetIsAlive(bool alive);							// 設定是否活著
//		void SetDelay(int d);									// 設定下降的速度
//	protected:
//		CMovingBitmap sun;			// 球的圖
//		int x, y;					// 圓心的座標
//		int delay_time;				// 多久一次
//		bool is_alive;				// 是否活著
//
//	};
//}