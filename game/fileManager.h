#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "tile.h"
#include "camera.h"
#include "objectManager.h"
#include "consts.h"

namespace FileManager
{
    bool loadFromFile(const std::string& filename);
    void loadData();
    void saveData();
    void addCompletedMap(const std::string& map);
};
