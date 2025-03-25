#pragma once
#include <vector>

class Wave {
public:
	Wave(int p_slime, int p_mikuSlime, int p_golem, int p_iceSlime, int p_fireSlime);
	bool getIsWaveEnd();
	void setIsWaveEnd(bool p_bool);
	void update();
	int slimeSpawnCount;
	int golemSpawnCount;
	int iceSlimeSpawnCount;
	int fireSlimeSpawnCount;
	int mikuSpawnCount;
	std::vector<int> enemyCount;
private:
	bool isWaveEnd = false;
};
