#include "ScrollBar.h"
#include "GlobalResource.h"
#include "Window.h"

using namespace std;

const float ScrollBar::WIDTH = 20.f;

ScrollBar::ScrollBar(float height, const Window* window) : GameObject() {
	m_window = window;
	m_discreteSteps = 1;

	m_height = height - ScrollBarKnob::HEIGHT;
	setScrollPosition(0.f);

	m_background.setSize(sf::Vector2f(WIDTH - 4.f, height - 4.f));
	m_background.setFillColor(COLOR_TRANS_BLACK);

	m_border = SlicedSprite(g_resourceManager->getTexture(GlobalResource::TEX_GUI_ORNAMENT_NONE), COLOR_WHITE, WIDTH, height);

	setBoundingBox(m_background.getGlobalBounds());
	setInputInDefaultView(true);
}

float ScrollBar::getScrollPosition() const {
	return m_scrollPosition;
}

int ScrollBar::getDiscreteScrollPosition() const {
	return static_cast<int>(m_scrollPosition * (m_discreteSteps - 1));
}

void ScrollBar::onLeftClick() {
	if (m_isEnabled && m_isPressed) {
		m_isPressed = false;
		g_inputController->lockAction();

		// update the position of the slider if it was clicked.
		sf::Vector2f mousePos = g_inputController->getDefaultViewMousePosition();
		int direction = 0;
		if (mousePos.y < m_knob.getPosition().y) {
			direction = -1;
		}
		else if (mousePos.y > m_knob.getPosition().y + m_knob.getSize().y) {
			direction = 1;
		}

		scroll(direction);
	}
}

void ScrollBar::setDiscreteSteps(int steps) {
	m_discreteSteps = steps;
	setEnabled(steps >= 2);
}

void ScrollBar::scroll(int direction) {
	if (m_discreteSteps >= 2) {
		float delta = 1.f / (m_discreteSteps - 1);
		setScrollPosition(m_scrollPosition + direction * delta, true);
	}
	else {
		setScrollPosition(m_scrollPosition + direction * 0.1f, true);
	}
}

void ScrollBar::setScrollPosition(float pos, bool animated) {
	if (pos <= 0.f) pos = 0.f;
	if (pos >= 1.f) pos = 1.f;

	float snappedPosition = pos;

	if (m_discreteSteps >= 2) {
		float delta = 1.f / (m_discreteSteps - 1);
		int floored = static_cast<int>(std::floor(pos / delta));
		snappedPosition = floored * delta;
		float tmp = pos - snappedPosition;
		if (tmp >= 0.5f * delta) {
			snappedPosition += delta;
		}
	}

	float oldPos = m_scrollPosition;
	m_scrollPosition = snappedPosition;
	float newPos = m_scrollPosition;
	if ((newPos != oldPos) && animated) {
		m_time = sf::Time::Zero;
	}

	// update knob
	float yPos = 0.5f * ScrollBarKnob::HEIGHT + m_scrollPosition * m_height;
	m_knob.setPosition(sf::Vector2f(getBoundingBox()->left + 0.5f * WIDTH, getBoundingBox()->top + yPos));
}

void ScrollBar::onLeftJustPressed() {
	if (m_isEnabled) {
		m_isPressed = true;
		g_inputController->lockAction();
	}
}

void ScrollBar::render(sf::RenderTarget& renderTarget) {
	if (!m_isVisible) return;
	renderTarget.draw(m_background);
	renderTarget.draw(m_border);

	if (m_isEnabled) {
		m_knob.render(renderTarget);
	}
}

void ScrollBar::handleDragAndDrop() {
	sf::Vector2f mousePos = g_inputController->getDefaultViewMousePosition();
	setScrollPosition(calculateScrollPosition(mousePos.y), true);
}

float ScrollBar::calculateScrollPosition(float mousePosY) const {

	float yOffset = mousePosY - getBoundingBox()->top - 0.5f * ScrollBarKnob::HEIGHT;
	// map the offset onto the values
	return yOffset / m_height;
}

void ScrollBar::setPosition(const sf::Vector2f& pos) {
	GameObject::setPosition(pos);
	m_background.setPosition(sf::Vector2f(pos.x + 2.f, pos.y + 2.f));
	m_border.setPosition(pos);
	setScrollPosition(m_scrollPosition);
}

void ScrollBar::update(const sf::Time& frameTime) {
	m_time += frameTime;

	if (!m_isVisible || !m_isEnabled) return;

	if (m_window == nullptr || m_window->getBoundingBox()->contains(g_inputController->getDefaultViewMousePosition())) {
		if (g_inputController->isMouseWheelScrolledUp()) {
			scroll(-1);
		}
		else if (g_inputController->isMouseWheelScrolledDown()) {
			scroll(1);
		}
	}

	m_knob.update(frameTime);
	if (m_knob.isPressed()) {
		handleDragAndDrop();
	}
	GameObject::update(frameTime);
}

void ScrollBar::setEnabled(bool enabled) {
	m_isEnabled = enabled;
}

void ScrollBar::setVisible(bool value) {
	m_isVisible = value;
}

bool ScrollBar::isEnabled() const {
	return m_isEnabled;
}

bool ScrollBar::isVisible() const {
	return m_isVisible;
}

sf::Time ScrollBar::getScrollTime() const {
	return m_time;
}

void ScrollBar::setTexture(sf::Texture* texture) {
	m_border.setTexture(texture);
}

void ScrollBar::setKnobTexture(sf::Texture* texture) {
	m_knob.setTexture(texture);
}

GameObjectType ScrollBar::getConfiguredType() const {
	return _Button;
}

// SLIDER KNOB

const float ScrollBarKnob::WIDTH = 20.f;
const float ScrollBarKnob::HEIGHT = 30.f;

ScrollBarKnob::ScrollBarKnob() : GameObject() {
	m_knob.setSize(sf::Vector2f(WIDTH, HEIGHT));
	m_knob.setTexture(g_resourceManager->getTexture(GlobalResource::TEX_GUI_KNOB));

	setBoundingBox(m_knob.getLocalBounds());
	setInputInDefaultView(true);
}

void ScrollBarKnob::onLeftJustPressed() {
	m_isPressed = true;
	g_inputController->lockAction();
}

void ScrollBarKnob::onLeftClick() {
	m_isPressed = false;
	g_inputController->lockAction();
}

bool ScrollBarKnob::isPressed() const {
	return m_isPressed;
}

void ScrollBarKnob::onMouseOver() {
}

void ScrollBarKnob::render(sf::RenderTarget& renderTarget) {
	renderTarget.draw(m_knob);
}

void ScrollBarKnob::update(const sf::Time& frameTime) {
	GameObject::update(frameTime);
	if (m_isPressed && !g_inputController->isMousePressedLeft()) {
		m_isPressed = false;
	}
}

void ScrollBarKnob::setPosition(const sf::Vector2f& pos) {
	GameObject::setPosition(pos - sf::Vector2f(0.5f * WIDTH, 0.5f * HEIGHT));
	m_knob.setPosition(pos - sf::Vector2f(0.5f * WIDTH, 0.5f * HEIGHT));
}

void ScrollBarKnob::setTexture(sf::Texture* texture) {
	m_knob.setTexture(texture);
}

GameObjectType ScrollBarKnob::getConfiguredType() const {
	return _Button;
}