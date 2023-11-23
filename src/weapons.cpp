#include "weapons.hpp"
#include "item_slot.hpp"

BulletClip* BulletWeapon::clip() {
    const auto contents = clip_slot->peek();

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

Action* BulletWeapon::insert(Thing& actor, ID<ItemSlot> source) {
    try {
        const auto clip = source->take_as<BulletClip>();

        clip_slot->trash();
        clip_slot->insert(clip);

        return new Noop;
    } catch (const TakeFailed&) {
        return nullptr;
    }
}
