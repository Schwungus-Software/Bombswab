/// The main header for importing raylib. DO NOT include raylib.h directly!

#pragma once

#ifdef RAYLIB_H
#error Could you please remove #include "raylib.h"?
#endif

namespace RL {
extern "C" {
#include "raylib.h"
}
} // namespace RL
