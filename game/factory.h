#pragma once

#include <memory>
#include "gameObject.h"

namespace Factory
{
    std::shared_ptr<GameObject> createPistolBullet();
    std::shared_ptr<GameObject> createRifleBullet();
    std::shared_ptr<GameObject> createShotgunBullet();

    std::shared_ptr<GameObject> createKnifeEnemy();
    std::shared_ptr<GameObject> createPistolEnemy();
    std::shared_ptr<GameObject> createRifleEnemy();
    std::shared_ptr<GameObject> createShotgunEnemy();

    std::shared_ptr<GameObject> createPlayer();

    std::shared_ptr<GameObject> createTile();

    std::shared_ptr<GameObject> createDummy();

    std::shared_ptr<GameObject> createKnifeItem();
    std::shared_ptr<GameObject> createPistolItem();
    std::shared_ptr<GameObject> createRifleItem();
    std::shared_ptr<GameObject> createShotgunItem();

    std::shared_ptr<GameObject> createPistolAmmoItem();
    std::shared_ptr<GameObject> createRifleAmmoItem();
    std::shared_ptr<GameObject> createShotgunAmmoItem();

    std::shared_ptr<GameObject> createHealItem();

    std::shared_ptr<GameObject> createKnifeEffect();
}
