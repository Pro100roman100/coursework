#include "inventoryManager.h"

InventoryManager::InventoryManager()
{
}

void InventoryManager::addWeapon(std::shared_ptr<Weapon> weapon)
{
    addAmmo(weapon->getType(), weapon->getStartAmmo());
    for (auto& existingWeapon : weapons) {
        if (existingWeapon->getType() == weapon->getType()) {
            return;
        }
    }
    weapons.push_back(weapon);
    switchWeapon(weapons.size() - 1);
}

void InventoryManager::removeWeapon(int index)
{
    if (index >= 0 && index < static_cast<int>(weapons.size())) {
        weapons.erase(weapons.begin() + index);
        if (currentWeaponIndex >= static_cast<int>(weapons.size()) && !weapons.empty())
            currentWeaponIndex = weapons.size() - 1;
    }
}

bool InventoryManager::switchWeapon(int index)
{
    if (index >= 0 && index < static_cast<int>(weapons.size())) {
        currentWeaponIndex = index;
        return true;
    }
    return false;
}

std::shared_ptr<Weapon> InventoryManager::getCurrentWeapon() const
{
    if (currentWeaponIndex >= 0 && currentWeaponIndex < static_cast<int>(weapons.size()))
        return weapons[currentWeaponIndex];
    return nullptr;
}

int InventoryManager::getCurrentWeaponIndex() const
{
    return currentWeaponIndex;
}

const std::vector<std::shared_ptr<Weapon>>& InventoryManager::getWeapons() const
{
    return weapons;
}

void InventoryManager::addAmmo(WeaponType weaponType, int amount)
{
    ammo[weaponType] += amount;
}

int InventoryManager::getAmmo(WeaponType weaponType) const
{
    auto it = ammo.find(weaponType);
    return it != ammo.end() ? it->second : 0;
}

bool InventoryManager::useAmmo(WeaponType weaponType, int amount)
{
    auto it = ammo.find(weaponType);
    if (it != ammo.end() && it->second >= amount) {
        it->second -= amount;
        return true;
    }
    return false;
}

void InventoryManager::setAmmo(WeaponType weaponType, int amount)
{
    ammo[weaponType] = amount;
}

void InventoryManager::clear()
{
    weapons.clear();
    ammo.clear();
    currentWeaponIndex = 0;
}
