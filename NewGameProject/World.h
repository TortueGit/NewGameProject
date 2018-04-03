#pragma once

#include "global.h"
#include "TileMap.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "WorldData.h"
#include "WorldScreen.h"

// a level or a map in the cendric world
class World {

public:
	World();
	virtual ~World();

	// updates all tilemaps
	virtual void update(const sf::Time& frameTime);

	virtual bool load(const std::string& id, WorldScreen* screen) = 0;
	// loads lights. this happens AFTER everything else and is because of our nice RENDERTEXTURE PROBLEM >:(
	virtual void loadForRenderTexture() = 0;
	// sets the target view to the correct world view with the focus center focus.
	virtual void setWorldView(sf::RenderTarget& target, const sf::Vector2f& focus) const = 0;
	// draws the world. background tilelayers.
	void drawBackground(sf::RenderTarget& target, const sf::RenderStates& states) const;
	// draws the world. lighted foreground tilelayers
	void drawLightedForeground(sf::RenderTarget& target, const sf::RenderStates& states) const;
	// draws the world. foreground tilelayers
	void drawForeground(sf::RenderTarget& target, const sf::RenderStates& states) const;

	const TileMap* getBackgroundTileMap() const;
	const TileMap* getLightedForegroundTileMap() const;
	const TileMap* getForegroundTileMap() const;

	// deletes the world resources
	virtual void dispose();

	const sf::FloatRect& getWorldRect() const;
	const std::string& getID() const;
	const std::string& getMusicPath() const;
	std::string getName() const;
	static std::string getNameFromId(const std::string id);
	virtual const WorldData* getWorldData() const = 0;

protected:
	// this pointer is set by the descendants (map and level)
	WorldData* m_worldData;

	TileMap m_backgroundTileMap;
	TileMap m_lightedForegroundTileMap;
	TileMap m_foregroundTileMap;

	Screen* m_screen;

public:
	// line direction from p1 to p2
	static bool lineBoxIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& bb, sf::Vector2f& intersection);
	static bool lineIntersection(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2, sf::Vector2f& intersection);
};