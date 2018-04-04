#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AnimatedTileData.h"
#include "TriggerData.h"

struct WorldData {
	virtual ~WorldData() {};

	std::string id;
	sf::Vector2i mapSize;
	std::string tileSetPath;
	std::string musicPath;
	bool isTeleportLocked = false;
	std::vector<std::vector<int>> backgroundTileLayers;
	std::vector<std::vector<int>> lightedForegroundTileLayers;
	std::vector<std::vector<int>> foregroundTileLayers;

	std::vector<AnimatedTileData> animatedTiles;
	std::vector<bool> collidableTiles;
	std::vector<std::vector<bool>> collidableTilePositions;

	std::vector<TriggerData> triggers;

	sf::FloatRect mapRect;
};