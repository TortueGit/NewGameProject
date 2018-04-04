#pragma once

// this enum is used for animations and used by all game objects
enum class GameObjectState {
	VOID,
	Idle, // used by nearly every game object
	Active, // used by checkpoint tiles and resource tiles
};