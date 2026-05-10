#pragma once

#include <string>
#include <vector>

namespace globalData {
	enum EndState {
		win,
		lose
	};
	extern std::string currentMap;
	extern EndState endState;
	extern float difficultyMultiplier;
	extern std::vector<std::string> completedMaps;
}
