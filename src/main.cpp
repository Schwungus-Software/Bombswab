#include <memory>
#include <vector>

#include "raylib.h"

#include "audio.hpp"
#include "camera.hpp"
#include "gamestate.hpp"
#include "grid.hpp"
#include "particles.hpp"
#include "spritesheet.tpp"
#include "things.hpp"

int main(int argc, char* argv[]) {
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Bombswab");
    SetTargetFPS(60);

    EnableCursor();

    InitAudioDevice();
    load_sounds();

    while (!WindowShouldClose()) {
        BeginDrawing();

        gsm.tick();

        BeginMode2D(get_camera());
        {
            ClearBackground({69, 42, 16, 255});

            draw_grid();
            draw_things();
            draw_particles();
        }
        EndMode2D();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
