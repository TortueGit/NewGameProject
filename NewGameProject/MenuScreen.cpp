#include "MenuScreen.h"
#include "ScreenManager.h"
#include "ParticleSystem.h"
#include "GUIConstants.h"

MenuScreen::MenuScreen() : Screen() {
	m_screenSpriteBackground = sf::Sprite((*g_resourceManager->getTexture(GlobalResource::TEX_SPLASH_BG)));
	m_screenSpriteForeground = sf::Sprite((*g_resourceManager->getTexture(GlobalResource::TEX_SPLASH_FG)));

	float scale = 4.f;
	sf::Texture* tex = g_resourceManager->getTexture(GlobalResource::TEX_SPLASH_LOGO);
	m_logoSprite = sf::Sprite(*tex);
	m_logoSprite.setScale(sf::Vector2f(scale, scale));
	m_logoSprite.setPosition(0.5f * (WINDOW_WIDTH - scale * tex->getSize().x), 30.f);
}

MenuScreen::~MenuScreen() {
	delete m_ps_left;
	delete m_ps_right;
}

void MenuScreen::setFireParticles(particles::TextureParticleSystem* ps_left, particles::TextureParticleSystem* ps_right) {
	delete m_ps_left;
	delete m_ps_right;
	m_ps_left = ps_left;
	m_ps_right = ps_right;
}

void MenuScreen::execUpdate(const sf::Time& frameTime) {
	if ((g_inputController->isKeyJustPressed(Key::Escape))) {
		// end the game
		m_screenManager->requestQuit();
		return;
	}
	if (g_inputController->isKeyJustPressed(Key::Escape)) {
		// resume game
		m_screenManager->resumeBackupScreen();
		return;
	}

	updateTooltipText(frameTime);

	updateObjects(_Button, frameTime);
	updateObjects(_Form, frameTime);
	m_ps_left->update(frameTime);
	m_ps_right->update(frameTime);
}

void MenuScreen::setAllButtonsEnabled(bool value) {
	Screen::setAllButtonsEnabled(value);
	m_saveGameButton->setEnabled(value);
}

void MenuScreen::render(sf::RenderTarget& renderTarget) {
	renderTarget.setView(renderTarget.getDefaultView());
	renderTarget.draw(m_screenSpriteBackground);
	m_ps_left->render(renderTarget);
	m_ps_right->render(renderTarget);
	renderTarget.draw(m_screenSpriteForeground);
	renderTarget.draw(m_versionText);
	renderTarget.draw(m_logoSprite);
	renderObjects(_Button, renderTarget);
	renderObjects(_Form, renderTarget);
	renderTooltipText(renderTarget);
}

void MenuScreen::execOnEnter() {
	loadNewestSave();

	// add fire particles
	if (m_ps_left == nullptr && m_ps_right == nullptr) {
		g_resourceManager->getTexture(GlobalResource::TEX_PARTICLE_FLAME)->setSmooth(true);
		m_ps_right = new particles::TextureParticleSystem(1000, g_resourceManager->getTexture(GlobalResource::TEX_PARTICLE_FLAME));
		m_ps_left = new particles::TextureParticleSystem(1000, g_resourceManager->getTexture(GlobalResource::TEX_PARTICLE_FLAME));
		SplashScreen::loadFireParticles(m_ps_left, sf::Vector2f(155.f, 330.f));
		SplashScreen::loadFireParticles(m_ps_right, sf::Vector2f(1130.f, 330.f));
	}
	// add version nr
	m_versionText.setString("NewGameProject v" + std::string(NEW_GAME_PROJECT_VERSION_NR));
	m_versionText.setCharacterSize(GUIConstants::CHARACTER_SIZE_S);
	m_versionText.setColor(COLOR_WHITE);
	m_versionText.setPosition(
		(WINDOW_WIDTH - m_versionText.getLocalBounds().width) / 2,
		WINDOW_HEIGHT - 18.f);

	float buttonHeight = 50.f;
	float buttonWidth = 300.f;
	float xOffset = (WINDOW_WIDTH - buttonWidth) / 2.f;
	float yOffset = 200.f;
	float addYOffset = 55.f;

	// add buttons
	Button* button;

	button = new Button(sf::FloatRect(xOffset, yOffset, buttonWidth, buttonHeight), GUIOrnamentStyle::MEDIUM);
	button->setText("NewGame");
	button->setOnClick(std::bind(&MenuScreen::onNewGame, this));
	addObject(button);
	yOffset += addYOffset;

	button = new Button(sf::FloatRect(xOffset, yOffset, buttonWidth, buttonHeight), GUIOrnamentStyle::MEDIUM);
	button->setText("Options");
	button->setOnClick(std::bind(&MenuScreen::onOptions, this));
	addObject(button);
	yOffset += addYOffset;

	button = new Button(sf::FloatRect(xOffset, yOffset, buttonWidth, buttonHeight), GUIOrnamentStyle::MEDIUM);
	button->setText("Exit");
	button->setOnClick(std::bind(&MenuScreen::onExit, this));
	addObject(button);
}

void MenuScreen::loadNewestSave() {

}

void MenuScreen::execOnExit() {
	g_resourceManager->deleteUniqueResources(this);
}

// <<< agents for the yes or no form and other buttons >>>

void MenuScreen::onStartNewGame() {
	m_yesOrNoForm->setDisposed();
	m_yesOrNoForm = nullptr;
	onNewGame();
}

void MenuScreen::onNo() {
	m_yesOrNoForm = nullptr;
	setAllButtonsEnabled(true);
}

void MenuScreen::onExit() {
	m_screenManager->requestQuit();
}

void MenuScreen::onResume() {
	m_screenManager->resumeBackupScreen();
}

void MenuScreen::onNewGame() {
	/*Screen* nextScreen = nullptr;
	setNextScreen(nextScreen);*/
}

void MenuScreen::onLoadGame() {
	
}

void MenuScreen::onSaveGame() {
	
}

void MenuScreen::onOptions() {
	
}

void MenuScreen::onKeybindings() {
	
}

void MenuScreen::onCredits() {
	
}