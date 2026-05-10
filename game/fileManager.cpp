#include "fileManager.h"
#include "player.h"
#include "dummy.h"
#include "weaponItem.h"
#include "bulletItem.h"
#include "healItem.h"
#include "enemy.h"

#include "globalData.h"

#include <algorithm>
#include <iomanip>

bool FileManager::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {

        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream iss(line);
        std::string type;
        int x, y;

        if (iss >> type >> x >> y)
        {
            std::shared_ptr<GameObject> obj;
            if (type == "tile") {
                obj = ObjectManager::getInstance().addObject<TileFactory>();
            }
            else if (type == "player") {
                obj = ObjectManager::getInstance().addObject<PlayerFactory>();
                obj->setPosition(sf::Vector2f(x * tileSize, y * tileSize));
                Camera::getActive()->setTarget(obj);
            }
            else if (type == "dummy") {
                obj = ObjectManager::getInstance().addObject<DummyFactory>();
            }
            else if (type == "knifeEnemy") {
                obj = ObjectManager::getInstance().addObject<KnifeEnemyFactory>();
            }
            else if (type == "pistolEnemy") {
                obj = ObjectManager::getInstance().addObject<PistolEnemyFactory>();
            }
            else if (type == "rifleEnemy") {
                obj = ObjectManager::getInstance().addObject<RifleEnemyFactory>();
            }
            else if (type == "shotgunEnemy") {
                obj = ObjectManager::getInstance().addObject<ShotgunEnemyFactory>();
            }
            else if (type == "knifeItem") {
                obj = ObjectManager::getInstance().addObject<KnifeItemFactory>();
            }
            else if (type == "pistolItem") {
                obj = ObjectManager::getInstance().addObject<PistolItemFactory>();
            }
            else if (type == "rifleItem") {
                obj = ObjectManager::getInstance().addObject<RifleItemFactory>();
            }
            else if (type == "shotgunItem") {
                obj = ObjectManager::getInstance().addObject<ShotgunItemFactory>();
            }
            else if (type == "pistolAmmoItem") {
                obj = ObjectManager::getInstance().addObject<PistolAmmoItemFactory>();
            }
            else if (type == "rifleAmmoItem") {
                obj = ObjectManager::getInstance().addObject<RifleAmmoItemFactory>();
            }
            else if (type == "shotgunAmmoItem") {
                obj = ObjectManager::getInstance().addObject<ShotgunAmmoItemFactory>();
            }
            else if (type == "healItem") {
                obj = ObjectManager::getInstance().addObject<HealItemFactory>();
            }

            if (obj) {
                obj->setPosition(sf::Vector2f(x * tileSize, y * tileSize));
                //std::cout << type << " pos: (" << obj->getPosition().x << ", " << obj->getPosition().y << ")" << std::endl;
            }
        }
    }

    file.close();
    return true;
}

void FileManager::saveData() {
 std::ofstream file("data.txt");
    if (!file.is_open())
        return;

    file << std::setprecision(2) << globalData::difficultyMultiplier << "\n";
    for (size_t i = 0; i < globalData::completedMaps.size(); i++) {
        file << globalData::completedMaps[i] << " ";
    }
    file << "\n";
}

void FileManager::loadData() {
 std::ifstream file("data.txt");
    if (!file.is_open()) {
        saveData();
        return;
    }

    globalData::difficultyMultiplier = 1.f;
    globalData::completedMaps.clear();

    std::string difficultyLine;
    if (std::getline(file, difficultyLine)) {
        std::stringstream iss(difficultyLine);
        float loadedMultiplier;
        if (iss >> loadedMultiplier)
            globalData::difficultyMultiplier = loadedMultiplier;
    }

    std::string mapsLine;
    if (std::getline(file, mapsLine)) {
        std::stringstream iss(mapsLine);
        std::string map;
        while (iss >> map)
            globalData::completedMaps.push_back(map);
    }
}

void FileManager::addCompletedMap(const std::string& map) {
    for (auto& existingMap : globalData::completedMaps) {
        if (map == existingMap)
            return;
    }
    globalData::completedMaps.push_back(map);
    saveData();
}
