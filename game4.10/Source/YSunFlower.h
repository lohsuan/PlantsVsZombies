namespace game_framework {

	class YSunFlower : public YPlants
	{
	public:
		YSunFlower();
		~YSunFlower() override;
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;
		void SetBlood(int attack_blood);
		int  GetBlood();
		void SetUp();
	private:
		int blood;
		int sun_make_time;
		bool already_set_up;
	};
}