#pragma once

#include "global.h"
#include "InputController.h"
#include "ResourceManager.h"
#include "Window.h"
#include "TexturedTabBar.h"
#include "GUIConstants.h"

class WeaponWindow;
class SlotClone;
class WorldInterface;

// the market, as displayed in a level or a map
// it takes its information about ???learned spells and modifiers directly from the character core???=> TODO: To change
// it is only clickable when ???in a map.???=> TODO: To change
class Market final {
public:
	Market(WorldInterface* _interface, bool modifiable);
	~Market();

	void show();
	void hide();

	bool isVisible() const;

	void render(sf::RenderTarget& target);
	void update(const sf::Time& frameTime);

	// reloads the market, depending on ???the core???=> TODO: To change
	void reload();

	static float WIDTH;

private:
	WorldInterface* m_interface;
	bool m_isVisible = false;
	bool m_isModifiable;

	void init();

	Window* m_window = nullptr;

	BitmapText m_selectedTabText;
	std::vector<BitmapText> m_modifierTexts;

	BitmapText m_emptyText;

	static const sf::Vector2f BUTTON_SIZE;
	const float MARGIN = 5.f;
};