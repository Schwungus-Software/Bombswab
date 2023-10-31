#include "weapons.hpp"

BulletWeapon rifle(30, 10, 8);

AbstractWeapon::~AbstractWeapon() = default;

Projectile* BulletWeapon::spawn_projectile(RL::Vector2 destination) {
    return new Bullet(destination.x, destination.y, range, damage);
}
