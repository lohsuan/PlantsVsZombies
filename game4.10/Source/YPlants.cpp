#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
//#include "audio.h"
#include "gamelib.h"
#include "YPlants.h"

namespace game_framework {
	/////////////////////////////////////////////////////
	// YPlants: Plants class
	/////////////////////////////////////////////////////

	YPlants::YPlants(int x, int y) {
		is_alive = true;
		this->x = x;
		this->y = y;
	}


	bool YPlants::IsAlive() {
		return is_alive;
	}

	void YPlants::SetIsAlive(bool alive) {
		is_alive = alive;
	}

	int YPlants::GetX() {
		return x;
	}

	int YPlants::GetY() {
		return y;
	}
}
	