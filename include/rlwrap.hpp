/// The main header for importing raylib. DO NOT include raylib.h directly!

#pragma once

#ifdef RAYLIB_H
#error Could you please remove #include "raylib.h"?
#endif

// Fixes an EXTREMELY weird error related to __gnu_va_args or alike.
#include <stdarg.h>

namespace RL {
extern "C" {
#include "raylib.h"
}
} // namespace RL

// Prevent further re-includes.
#define RAYLIB_H
