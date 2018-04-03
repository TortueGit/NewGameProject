#include "Market.h"
#include "WorldInterface.h"
#include "GlobalResource.h"

float Market::WIDTH = 420.f;
const sf::Vector2f Market::BUTTON_SIZE = sf::Vector2f(70.f, 57.f);

Market::Market(WorldInterface* _interface, bool modifiable) {
	m_interface = _interface;
	m_isModifiable = modifiable;

	init();
}

void Market::init() {
	// init window
	sf::FloatRect box(GUIConstants::LEFT, GUIConstants::TOP, WIDTH, GUIConstants::GUI_WINDOW_HEIGHT);
	m_window = new Window(box,
		GUIOrnamentStyle::LARGE,
		GUIConstants::MAIN_COLOR,
		GUIConstants::ORNAMENT_COLOR);

	// init text
	m_selectedTabText.setPosition(sf::Vector2f(GUIConstants::LEFT + GUIConstants::TEXT_OFFSET, GUIConstants::TOP + GUIConstants::TEXT_OFFSET));
	m_selectedTabText.setColor(COLOR_WHITE);
	m_selectedTabText.setCharacterSize(GUIConstants::CHARACTER_SIZE_M);
	
	// init empty text
	m_emptyText.setCharacterSize(GUIConstants::CHARACTER_SIZE_M);
	m_emptyText.setString(g_textProvider->getText("NoMarket"));
	const sf::FloatRect bounds = m_emptyText.getBounds();
	m_emptyText.setPosition(box.left + 0.5f * (box.width - bounds.width), box.top + 0.5f * (box.height - bounds.height));

	reload();
}

Market::~Market() {
	delete m_window;
}

void Market::update(const sf::Time& frameTime) {
	if (!m_isVisible) return;
	
	if (!m_isModifiable) return;
}

bool Market::isVisible() const {
	return m_isVisible;
}

void Market::render(sf::RenderTarget& target) {
	if (!m_isVisible) return;

	m_window->render(target);

	target.draw(m_emptyText);
}

void Market::reload() {
	
	float width = BUTTON_SIZE.x;
	float height = BUTTON_SIZE.y;
	float x = GUIConstants::LEFT + 0.5f * (WIDTH - width);
	float y = GUIConstants::TOP + GUIConstants::GUI_TABS_TOP;

}

void Market::show() {
	m_isVisible = true;
}

void Market::hide() {
	m_isVisible = false;
}