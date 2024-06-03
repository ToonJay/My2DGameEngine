#pragma once

#include <SDL.h>
#include <unordered_set>

struct PlayerControllerComponent {
    std::unordered_set<SDL_Keycode> activeKeys;
};
using PlayerController = PlayerControllerComponent;