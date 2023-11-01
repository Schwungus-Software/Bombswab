#include "weapons.hpp"

BulletClip* BulletWeapon::clip() {
    const auto contents = clip_slot.contents.get();

    if (contents == nullptr) {
        return nullptr;
    }

    return dynamic_cast<BulletClip*>(contents);
}

bool BulletWeapon::has_ammo() {
    const auto clip = this->clip();

    if (clip == nullptr) {
        return false;
    }

    return clip->ammo_count > 0;
}

Projectile* BulletWeapon::spawn_projectile(RL::Vector2 destination) {
    const auto clip = this->clip();

    if (clip == nullptr) {
        return nullptr;
    }

    clip->ammo_count--;

    return new Bullet(destination.x, destination.y, range, damage);
}

void BulletWeapon::reload(BulletClip* clip) {
    const auto old = clip_slot.contents.release();
    clip_slot.contents.reset(clip);

    // TODO: drop `old` on the ground.
    delete old;
}
