#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "audio.hpp"
#include "items.hpp"
#include "line.hpp"
#include "spritesheet.hpp"
#include "spritesheets.hpp"

class Action;
class AbstractWeapon;

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

enum class HandSlot {
    LEFT,
    RIGHT,
};

const std::size_t POCKET_COUNT = 4;

class Thing {
  public:
    using Sprite = TintedSprite<ThingSprite>;

    // Movement.

    int x, y;
    Direction walk_dir, action_dir;

    // Actions.

    std::unique_ptr<Action> ongoing;

    ItemSlot lh_slot, rh_slot;
    std::array<ItemSlot, POCKET_COUNT> pockets;

    // Health.

    int max_health, cur_health;

    // Main flags.

    // Phases through walls.
    bool ghost;

    // Misc. flags.

    bool deletion_mark;
    bool stepped;

    Thing(int, int);

    void tick();

    /// Called every turn.
    virtual void think() {}

    /// Called every time an action can be taken.
    virtual void act() {}

    /// Called whenever a collision with a wall occurs.
    virtual void collide();

    /// Draw this thing in multiple layers.
    virtual std::vector<Sprite> draw() = 0;

    SpriteFlip action_dir_to_flip();

    /// Deal damage and return `true` if it was fatal.
    bool damage(int);

    bool collides_with(const Thing&, bool = false);
    Thing* collide_at(bool = false);

    void play_sound(const RL::Sound&);
    void play_sound_local(const RL::Sound&);

    ItemSlot& hand_slot(HandSlot);

    RL::Vector2 pos();

    virtual void step() {}
    virtual void pain() {}
    virtual void before_death() {}

    virtual ~Thing();
};

extern std::vector<std::unique_ptr<Thing>> things;
extern std::vector<Thing*> spawn_queue;

void tick_things();
void draw_things();

class Humanoid : public Thing {
  public:
    RL::Color body_color;

  protected:
    bool can_reveal_tiles;

  public:
    Humanoid(int, int, RL::Color, bool);

    std::vector<Sprite> draw() override;

    void step() override;

    void collide() override;

    void pain() override;

    void before_death() override;
};

class Player : public Humanoid {
  public:
    Player(int x, int y) : Humanoid(x, y, RL::BLUE, true) {}

    void act() override;
};

class Enemy : public Humanoid {
  public:
    Enemy(int x, int y) : Humanoid(x, y, RL::RED, false) {}

    void act() override;
};

class Corpse : public Thing {
  public:
    Corpse(int x, int y) : Thing(x, y) {
        ghost = true;
    }

    std::vector<Sprite> draw() override;

    // TODO: override `before_death` to add blood splatters.
};

class Projectile : public Thing {
  public:
    int range, damage;
    int dest_x, dest_y;

    std::vector<Point> trajectory;
    std::size_t cur_point;

    Projectile(int dest_x, int dest_y, int range, int damage)
        : Thing(0, 0), range(range), damage(damage), dest_x(dest_x), dest_y(dest_y), cur_point(0) {}

    void act() override;
};

class Bullet : public Projectile {
  public:
    Bullet(int dest_x, int dest_y, int range, int damage)
        : Projectile(dest_x, dest_y, range, damage) {}

    std::vector<Sprite> draw() override;
};
