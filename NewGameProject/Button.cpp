#include "Button.h"
#include "GlobalResource.h"

Button::Button(const sf::FloatRect& box, GUIOrnamentStyle style) :
	GameObject(),
	m_backLayerColor(COLOR_DARK_GREY),
	m_mainLayerColor(COLOR_BLACK),
	m_ornamentLayerColor(COLOR_WHITE),
	m_mouseOverColor(COLOR_PURPLE) {
	// using default values for constructor.
	setBoundingBox(box);
	setInputInDefaultView(true);

	m_mainLayer = SlicedSprite(g_resourceManager->getTexture(GlobalResource::TEX_GUI_ROUNDED_RECTANGLE), m_mainLayerColor, box.width, box.height);

	m_backLayer = SlicedSprite(g_resourceManager->getTexture(GlobalResource::TEX_GUI_ROUNDED_RECTANGLE), m_backLayerColor, box.width, box.height);
	m_backLayerOffset = sf::Vector2f(0, 2);

	m_ornamentLayer = SlicedSprite(getOrnamentStyleTexture(style), m_ornamentLayerColor, box.width, box.height);

	m_positionDefault = sf::Vector2f(box.left, box.top);
	setPosition(m_positionDefault);
}

void Button::onLeftClick() {
	if (m_isEnabled && m_isPressed) {
		m_isClicked = true;
		m_isPressed = false;
		m_mainLayer.move(0, 1);
		m_ornamentLayer.move(0, 1);
		m_text.move(0, 1);
		m_textureLayer.move(0, 1);
		m_mainLayer.setColor(m_mainLayerColor);
		g_inputController->lockAction();
	}
}

void Button::onLeftJustPressed() {
	if (m_isEnabled) {
		m_isPressed = true;
		m_mainLayer.setPosition(m_positionDefault);
		m_ornamentLayer.setPosition(m_positionDefault);
		m_mainLayer.move(0, 1);
		m_ornamentLayer.move(0, 1);
		m_text.move(0, 1);
		m_textureLayer.move(0, 1);
		m_mainLayer.setColor(m_mainLayerColor);
		g_inputController->lockAction();
	}
}

void Button::onMouseOver() {
	m_isMouseOver = true;
	if (m_isEnabled && !m_isPressed) {
		m_mainLayer.setColor(m_mouseOverColor);
	}
}

void Button::render(sf::RenderTarget& renderTarget) {
	if (!m_isVisible) return;
	renderTarget.draw(m_backLayer);
	renderTarget.draw(m_mainLayer);
	renderTarget.draw(m_ornamentLayer);
	renderTarget.draw(m_text);
	if (m_hasTexture) renderTarget.draw(m_textureLayer);
}

void Button::setPosition(const sf::Vector2f& pos) {
	GameObject::setPosition(pos);
	m_mainLayer.setPosition(pos);
	m_backLayer.setPosition(pos + m_backLayerOffset);
	m_ornamentLayer.setPosition(pos);
	m_text.setPosition(pos + m_textOffset);
	m_textureLayer.setPosition(pos + m_textureOffset);
	m_positionDefault = pos;
}

void Button::setSize(const sf::Vector2f& size) {
	GameObject::setSize(size);
	m_ornamentLayer.setSize(size);
	m_backLayer.setSize(size);
	m_mainLayer.setSize(size);

	// this re-centers the text
	setCharacterSize(m_text.getCharacterSize());
}

void Button::update(const sf::Time& frameTime) {
	if (!m_isVisible) return;

	if (m_isMouseOver && !(g_inputController->isMouseOver(getBoundingBox(), true))) {
		m_isMouseOver = false;
		m_isPressed = false;
		m_mainLayer.setColor(m_mainLayerColor);
		setPosition(m_positionDefault);
	}
	if (!m_isPressed && m_isClicked) {
		setPosition(m_positionDefault);
	}
	m_isClicked = false;
	GameObject::update(frameTime);
	if (m_isClicked) {
		m_executeOnClick();
		g_inputController->lockAction();
	}
}

void Button::setText(const std::string& text, const sf::Color& color, int charSize) {
	setTextRaw(g_textProvider->getText(text), color, charSize);
}

void Button::setText(const std::string& text) {
	setText(text, COLOR_WHITE, 16);
}

void Button::setText(const std::string& text, int charSize) {
	setText(text, COLOR_WHITE, charSize);
}

void Button::setTextRaw(const std::string& text, const sf::Color& color, int charSize) {
	m_text = BitmapText(text);
	float usedWidth = charSize * static_cast<int>(text.length()) + 30.f;
	if (usedWidth > m_boundingBox.width) {
		setSize(sf::Vector2f(usedWidth, m_boundingBox.height));
	}

	setTextColor(color);
	setCharacterSize(charSize);
}

void Button::setTextRaw(const std::string& text, int charSize) {
	setTextRaw(text, COLOR_WHITE, charSize);
}

void Button::setTextRaw(const std::string& text) {
	setTextRaw(text, COLOR_WHITE, 16);
}

void Button::setTexture(const sf::Texture* texture) {
	if (texture == nullptr) {
		m_hasTexture = false;
		return;
	}
	m_hasTexture = true;

	sf::Vector2f textureSize(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y));
	sf::Vector2f pos = getPosition();
	sf::Vector2f size = getSize();

	m_textureLayer.setTexture(*texture);
	m_textureOffset = 0.5f * (size - textureSize);
	m_textureLayer.setPosition(pos + m_textureOffset);
}

void Button::setTextureColor(const sf::Color& color) {
	m_textureLayer.setColor(color);
}

void Button::setCharacterSize(int size) {
	m_text.setCharacterSize(size);
	float xOffset = std::max((getBoundingBox()->width - m_text.getLocalBounds().width) / 2.f, 0.f);
	float yOffset = std::max((getBoundingBox()->height - m_text.getLocalBounds().height) / 2.f, 0.f);
	m_textOffset = sf::Vector2f(xOffset, yOffset);
	m_text.setPosition(getPosition() + m_textOffset);
}

void Button::setBackgroundLayerColor(const sf::Color& color) {
	m_backLayer.setColor(color);
	m_backLayerColor = color;
}

void Button::setTextColor(const sf::Color& color) {
	m_text.setColor(color);
}

void Button::setMouseOverColor(const sf::Color& color) {
	m_mouseOverColor = color;
}

void Button::setMainLayerColor(const sf::Color& color) {
	m_mainLayer.setColor(color);
	m_mainLayerColor = color;
}

void Button::setOrnamentLayerColor(const sf::Color& color) {
	m_ornamentLayer.setColor(color);
	m_ornamentLayerColor = color;
}

sf::Color Button::getBackgroundLayerColor() const {
	return m_backLayerColor;
}

sf::Color Button::getMainLayerColor() const {
	return m_mainLayerColor;
}

sf::Color Button::getOrnamentLayerColor() const {
	return m_ornamentLayerColor;
}

sf::Color Button::getMouseOverColor() const {
	return m_mouseOverColor;
}

void Button::setOrnamentLayerTexture(sf::Texture* texture) {
	m_ornamentLayer.setTexture(texture);
}

void Button::setEnabled(bool enabled) {
	m_isEnabled = enabled;
	m_text.setColor(sf::Color(m_text.getColor().r, m_text.getColor().g, m_text.getColor().b, m_isEnabled ? 255 : 100));
	m_textureLayer.setColor(sf::Color(m_text.getColor().r, m_text.getColor().g, m_text.getColor().b, m_isEnabled ? 255 : 100));
}

void Button::setVisible(bool value) {
	m_isVisible = value;
}

bool Button::isClicked() const {
	return m_isClicked;
}

bool Button::isEnabled() const {
	return m_isEnabled;
}

bool Button::isVisible() const {
	return m_isVisible;
}

GameObjectType Button::getConfiguredType() const {
	return _Button;
}

void Button::setOnClick(const std::function<void()>& agent) {
	m_executeOnClick = agent;
}