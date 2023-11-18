#include "camera.hpp"
#include "spritesheet.tpp"

Vector2 camera_center;

const Camera2D& get_camera() {
    static Camera2D camera;

    camera.offset.x = GetScreenWidth() / 2.0 - SPRITE_DIM;
    camera.offset.y = GetScreenHeight() / 2.0 - SPRITE_DIM;

    camera.target = camera_center;
    camera.zoom = 2.0;
    camera.rotation = 0.0;

    return camera;
}
