#include "weapons.hpp"

BulletClip* BulletWeapon::clip() {
    const auto contents = clip_slot.contents.get();

    if (contents == nullptr) {
        return nullptr;
    }

    return dynamic_cast<BulletClip*>(contents);
}

Projectile* BulletWeapon::shoot(Vector2 destination) {
    const auto clip = this->clip();

    if (clip == nullptr) {
        return nullptr;
    }

    if (clip->ammo_count == 0) {
        return nullptr;
    }

    clip->ammo_count--;

    return new Bullet(destination.x, destination.y, range, damage);
}

Action* BulletWeapon::insert(Thing& actor, ItemSlot& source) {
    const auto clip = source.take_as<BulletClip>();

    if (clip == nullptr) {
        return nullptr;
    }

    if (clip_slot.contents != nullptr) {
        const auto old = clip_slot.contents.release();
        // TODO: drop `old` on the ground.
        delete old;
    }

    clip_slot.contents.reset(clip);

    return new Noop;
}
