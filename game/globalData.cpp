#include "globalData.h"

namespace globalData {
    std::string currentMap = "map";
    EndState endState = lose;
    float difficultyMultiplier = 1.f;
    std::vector<std::string> completedMaps = {};
}
