#include <memory>
#include <vector>

#include "misc.hpp"
#include "raylib.h"

#include "audio.hpp"
#include "camera.hpp"
#include "gamestate.hpp"
#include "level.hpp"
#include "particles.hpp"
#include "spritesheet.tpp"

int main(int argc, char* argv[]) {
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Bombswab");
    SetTargetFPS(FRAMERATE);

    EnableCursor();

    InitAudioDevice();
    load_sounds();

    while (!WindowShouldClose()) {
        BeginDrawing();

        try {
            gsm.tick();
        } catch (const Exit& exit) {
            // TODO: log the exit reason.
            break;
        }

        BeginMode2D(get_camera());
        {
            ClearBackground({69, 42, 16, 255});
            level.draw();
        }
        EndMode2D();

        gsm.overlay();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
