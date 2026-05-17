#include "fileManager.h"
#include "factory.h"
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
    std::ifstream file("maps/" + filename + ".txt");
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
                obj = ObjectManager::getInstance().addObject(Factory::createTile());
            }
            else if (type == "player") {
                obj = ObjectManager::getInstance().addObject(Factory::createPlayer());
                obj->setPosition(sf::Vector2f(x * tileSize, y * tileSize));
                Camera::getActive()->setTarget(obj);
            }
            else if (type == "dummy") {
                obj = ObjectManager::getInstance().addObject(Factory::createDummy());
            }
            else if (type == "knifeEnemy") {
                obj = ObjectManager::getInstance().addObject(Factory::createKnifeEnemy());
                loadPath(obj, iss);
            }
            else if (type == "pistolEnemy") {
                obj = ObjectManager::getInstance().addObject(Factory::createPistolEnemy());
                loadPath(obj, iss);
            }
            else if (type == "rifleEnemy") {
                obj = ObjectManager::getInstance().addObject(Factory::createRifleEnemy());
                loadPath(obj, iss);
            }
            else if (type == "shotgunEnemy") {
                obj = ObjectManager::getInstance().addObject(Factory::createShotgunEnemy());
                loadPath(obj, iss);
            }
            else if (type == "knifeItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createKnifeItem());
            }
            else if (type == "pistolItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createPistolItem());
            }
            else if (type == "rifleItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createRifleItem());
            }
            else if (type == "shotgunItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createShotgunItem());
            }
            else if (type == "pistolAmmoItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createPistolAmmoItem());
            }
            else if (type == "rifleAmmoItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createRifleAmmoItem());
            }
            else if (type == "shotgunAmmoItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createShotgunAmmoItem());
            }
            else if (type == "healItem") {
                obj = ObjectManager::getInstance().addObject(Factory::createHealItem());
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

void FileManager::loadPath(std::shared_ptr<GameObject> enemy, std::stringstream& line)
{
    auto* enemyObj = dynamic_cast<Enemy*>(enemy.get());
    int x = 0, y = 0;
    while (line >> x >> y) {
        enemyObj->addPatrolPoint(sf::Vector2f(x * tileSize, y * tileSize));
    }
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
