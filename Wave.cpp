#include "Wave.h"

Wave::Wave(int p_slime, int p_mikuSlime, int p_golem, int p_iceSlime, int p_fireSlime)
	:slimeSpawnCount(p_slime), golemSpawnCount(p_golem), iceSlimeSpawnCount(p_iceSlime), fireSlimeSpawnCount(p_fireSlime), mikuSpawnCount(p_mikuSlime) {


}

bool Wave::getIsWaveEnd() {
	return isWaveEnd;
}

void Wave::setIsWaveEnd(bool p_bool) {
	isWaveEnd = true;
}