#include "camera.hpp"
#include "spritesheet.hpp"

RL::Vector2 camera_center;

const RL::Camera2D& get_camera() {
    static RL::Camera2D camera;

    camera.offset.x = RL::GetScreenWidth() / 2.0 - SPRITE_DIM;
    camera.offset.y = RL::GetScreenHeight() / 2.0 - SPRITE_DIM;

    camera.target = camera_center;
    camera.zoom = 2.0;
    camera.rotation = 0.0;

    return camera;
}
