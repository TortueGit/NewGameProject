#pragma once

// Graphic & Sound Engine SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// std library
#include <iostream>
#include <cmath>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <cassert>

// versioning
#define NEW_GAME_PROJECT_VERSION_NR_RAW "0.0.1"
#define NEW_GAME_PROJECT_VERSION_NR NEW_GAME_PROJECT_VERSION_NR_RAW " - GitHub"

// Debug version
//#define DEBUG

// max frame time (in seconds)
#define MAX_FRAME_TIME 0.05f

// const canvas size (window can be rescaled though)
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// fixed tile size (width and height) for level and map
#define TILE_SIZE_F 50.f
#define TILE_SIZE 50
