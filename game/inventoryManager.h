#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "weapon.h"
#include "weaponType.h"

class InventoryManager
{
private:
    std::vector<std::shared_ptr<Weapon>> weapons;
    std::unordered_map<WeaponType, int> ammo;
    int currentWeaponIndex = 0;

public:
    InventoryManager();

    void addWeapon(std::shared_ptr<Weapon> weapon);
    void removeWeapon(int index);
    bool switchWeapon(int index);
    std::shared_ptr<Weapon> getCurrentWeapon() const;
    int getCurrentWeaponIndex() const;
    const std::vector<std::shared_ptr<Weapon>>& getWeapons() const;

    void addAmmo(WeaponType weaponType, int amount);
    int getAmmo(WeaponType weaponType) const;
    bool useAmmo(WeaponType weaponType, int amount);
    void setAmmo(WeaponType weaponType, int amount);

    void clear();
};
