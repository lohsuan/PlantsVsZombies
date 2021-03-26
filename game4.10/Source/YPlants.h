#ifndef YPLANTS_H
#define YPLANTS_H

namespace game_framework {

	class YPlants
	{
	public:
		YPlants(int x, int y);
		virtual ~YPlants() = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;	
		bool IsAlive(); 
		void SetIsAlive(bool alive);
		int  GetX();
		int  GetY();
		

	private:
		int x, y;
		bool is_alive;
	};
}

#endif