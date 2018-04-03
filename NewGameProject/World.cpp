#include "World.h"

World::World() {
}

World::~World() {
	dispose();
}

void World::dispose() {
	m_foregroundTileMap.dispose();
	m_backgroundTileMap.dispose();
	m_lightedForegroundTileMap.dispose();
}

void World::update(const sf::Time& frameTime) {
	m_backgroundTileMap.update(frameTime);
	m_foregroundTileMap.update(frameTime);
	m_lightedForegroundTileMap.update(frameTime);
}

void World::drawBackground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_backgroundTileMap.draw(target, states);
}

void World::drawLightedForeground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_lightedForegroundTileMap.draw(target, states);
}

void World::drawForeground(sf::RenderTarget& target, const sf::RenderStates& states) const {
	m_foregroundTileMap.draw(target, states);
}

const TileMap* World::getBackgroundTileMap() const {
	return &m_backgroundTileMap;
}

const TileMap* World::getLightedForegroundTileMap() const {
	return &m_lightedForegroundTileMap;
}

const TileMap* World::getForegroundTileMap() const {
	return &m_foregroundTileMap;
}

const sf::FloatRect& World::getWorldRect() const {
	return m_worldData->mapRect;
}

const std::string& World::getID() const {
	return m_worldData->id;
}

const std::string& World::getMusicPath() const {
	return m_worldData->musicPath;
}

std::string World::getName() const {
	return getNameFromId(m_worldData->id);
}

std::string World::getNameFromId(const std::string id) {
	if (id.size() < 4) return "";
	std::string name = id;
	name = name.substr(0, name.size() - 4);

	std::size_t pos = name.find_last_of('/');
	if (pos == std::string::npos) return "";
	return name.substr(pos + 1);
}

bool World::lineBoxIntersection(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::FloatRect& bb, sf::Vector2f& intersection) {
	// check the impossible things
	if (p1.x < bb.left && p2.x < bb.left)
		return false;
	if (p1.x > bb.left + bb.width && p2.x > bb.left + bb.width)
		return false;
	if (p1.y < bb.top && p2.y < bb.top)
		return false;
	if (p1.y > bb.top + bb.height && p2.y > bb.top + bb.height)
		return false;

	// ray direction, no need to normalize
	sf::Vector2f dir = p2 - p1;

	// check the x lines of the box
	bool intersects;
	if (dir.x > 0.f) {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top), sf::Vector2f(bb.left, bb.top + bb.height), p1, p2, intersection);
	}
	else {
		intersects = lineIntersection(sf::Vector2f(bb.left + bb.width, bb.top), sf::Vector2f(bb.left + bb.width, bb.top + bb.height), p1, p2, intersection);
	}

	if (intersects) {
		return true;
	}

	// now y
	if (dir.y > 0.f) {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top), sf::Vector2f(bb.left + bb.width, bb.top), p1, p2, intersection);
	}
	else {
		intersects = lineIntersection(sf::Vector2f(bb.left, bb.top + bb.height), sf::Vector2f(bb.left + bb.width, bb.top + bb.height), p1, p2, intersection);
	}
	return intersects;
}

bool World::lineIntersection(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2, sf::Vector2f& intersection) {
	sf::Vector2f b = a2 - a1;
	sf::Vector2f d = b2 - b1;
	float bDotDPerp = b.x * d.y - b.y * d.x;

	if (bDotDPerp == 0)
		return false;

	sf::Vector2f c = b1 - a1;
	float t = (c.x * d.y - c.y * d.x) / bDotDPerp;
	if (t < 0 || t > 1)
		return false;

	float u = (c.x * b.y - c.y * b.x) / bDotDPerp;
	if (u < 0 || u > 1)
		return false;

	intersection = a1 + t * b;
	return true;
}