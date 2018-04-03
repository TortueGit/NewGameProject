#include "AnimatedGameObject.h"
#include "ResourceManager.h"

AnimatedGameObject::~AnimatedGameObject() {
	for (auto& it : m_animations) {
		delete it.second;
	}
	m_animations.clear();
}

void AnimatedGameObject::setCurrentAnimation(const Animation* animation, bool isFlippedX, bool force) {
	if (animation == nullptr || (m_isAnimationLocked && !force)) return;
	m_animatedSprite.setFlippedX(isFlippedX);
	m_animatedSprite.setAnimation(animation);
	if (force)
		m_isAnimationLocked = true;
}

void AnimatedGameObject::unlockAnimation() {
	m_isAnimationLocked = false;
}

void AnimatedGameObject::addAnimation(GameObjectState state, Animation* animation) {
	if (animation->getAnimationTime() == sf::Time::Zero) {
		delete animation;
		g_logger->logError("AnimatedGameObject", "Can't add an animation with no frames or 0 duration!");
		return;
	}
	if (contains(m_animations, state)) {
		delete m_animations.at(state);
		m_animations[state] = animation;
		return;
	}
	m_animations.insert({ state, animation });
}

const Animation* AnimatedGameObject::getAnimation(GameObjectState state) const {
	if (!contains(m_animations, state))
		return nullptr;
	return m_animations.at(state);
}

bool AnimatedGameObject::isAnimationLocked() const {
	return m_isAnimationLocked;
}

void AnimatedGameObject::render(sf::RenderTarget& renderTarget) {
	renderTarget.draw(m_animatedSprite);
	GameObject::render(renderTarget);
}

void AnimatedGameObject::update(const sf::Time& frameTime) {
	m_animatedSprite.update(frameTime);
	if (m_coloredTime > sf::Time::Zero) {
		updateTime(m_coloredTime, frameTime);
		if (m_coloredTime == sf::Time::Zero) {
			m_animatedSprite.setColor(COLOR_WHITE);
			m_currentSpriteColor = COLOR_WHITE;
		}
	}

	GameObject::update(frameTime);
}

void AnimatedGameObject::setPosition(const sf::Vector2f& position) {
	GameObject::setPosition(position);
	// origin is set to the center for rotation + flipping
	sf::Vector2f spriteCenter(sf::Vector2f(m_boundingBox.width / 2, m_boundingBox.height / 2) - m_spriteOffset);
	m_animatedSprite.setOrigin(spriteCenter);
	m_animatedSprite.setPosition(position + m_spriteOffset + spriteCenter);
}

void AnimatedGameObject::setSpriteRotation(float angle) {
	// SFML uses degrees, not radian, hence the conversion here. 
	m_animatedSprite.setRotation(radToDeg(angle));
}

void AnimatedGameObject::playCurrentAnimation(bool play) {
	if (play) {
		m_animatedSprite.play();
	}
	else {
		m_animatedSprite.pause();
	}
}

void AnimatedGameObject::loopCurrentAnimation(bool loop) {
	m_animatedSprite.setLooped(loop);
}

void AnimatedGameObject::setSpriteOffset(const sf::Vector2f& spriteOffset) {
	m_spriteOffset = spriteOffset;
}

void AnimatedGameObject::setState(GameObjectState state) {
	setState(state, true);
}

void AnimatedGameObject::setState(GameObjectState state, bool updateAnimation) {
	if (m_state == state) return;
	GameObject::setState(state);
	if (updateAnimation)
		setCurrentAnimation(getAnimation(m_state), false);
}

const sf::Vector2f& AnimatedGameObject::getSpriteOffset() const {
	return m_spriteOffset;
}

const sf::Color& AnimatedGameObject::getCurrentSpriteColor() const {
	return m_currentSpriteColor;
}

void AnimatedGameObject::setSpriteColor(const sf::Color& color, const sf::Time& time) {
	if (time <= sf::Time::Zero) return;
	m_animatedSprite.setColor(color);
	m_coloredTime = time;
	m_currentSpriteColor = color;
}