#include "OptionsScreen.h"
#include "MenuScreen.h"
#include "KeyBindingsScreen.h"
#include "ScreenManager.h"
#include "ConfigurationWriter.h"

OptionsScreen::OptionsScreen() : Screen() {
}

void OptionsScreen::execUpdate(const sf::Time& frameTime) {
	if (g_inputController->isKeyActive(Key::Escape)) {
		onBack();
		return;
	}

	updateObjects(_Button, frameTime);
	updateTooltipText(frameTime);

	updateMusicVolume();
}

void OptionsScreen::render(sf::RenderTarget& renderTarget) {
	renderTarget.setView(renderTarget.getDefaultView());
	renderTarget.draw(*m_title);
	renderObjects(_Button, renderTarget);
	renderTooltipText(renderTarget);
}

void OptionsScreen::updateMusicVolume() {
	if (m_onBackPressed) return;
	auto& config = g_resourceManager->getConfiguration();
	if (m_volumeMusicSlider->getSliderPosition() != config.volumeMusic) {
		config.volumeMusic = m_volumeMusicSlider->getSliderPosition();
		g_resourceManager->notifyVolumeChanged();
	}
	if (m_soundCheckbox->isChecked() != config.isSoundOn) {
		config.isSoundOn = m_soundCheckbox->isChecked();
		g_resourceManager->notifyVolumeChanged();
	}
}

void OptionsScreen::execOnEnter() {
	// title
	m_title = new BitmapText(g_textProvider->getText("Options"), TextStyle::Shadowed);
	m_title->setCharacterSize(GUIConstants::CHARACTER_SIZE_XXXL);
	m_title->setPosition(sf::Vector2f((WINDOW_WIDTH - m_title->getLocalBounds().width) / 2.f, 50.f));

	float distFromTop = 150.f;
	float distFromLeft = 150.f;

	// language
	m_languageSelector = new ArrowSelector();
	m_languageSelector->setLabelText("Language");
	// TODO [If Spanish is there] replace with Language::MAX again.
	for (int language = 1; language < static_cast<int>(Language::LANG_ES); ++language) {
		m_languageSelector->addOption(EnumNames::getLanguageName(static_cast<Language>(language)));
	}
	m_languageSelector->setOptionIndex(static_cast<int>(g_resourceManager->getConfiguration().language) - 1);
	m_languageSelector->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	addObject(m_languageSelector);

	distFromTop = distFromTop + 75;

	// displayMode
	m_displayModeSelector = new ArrowSelector();
	m_displayModeSelector->setLabelText("DisplayMode");
	for (int mode = 1; mode < static_cast<int>(DisplayMode::MAX); ++mode) {
		m_displayModeSelector->addOption(EnumNames::getDisplayModeName(static_cast<DisplayMode>(mode)));
	}
	m_displayModeSelector->setOptionIndex(static_cast<int>(g_resourceManager->getConfiguration().displayMode) - 1);
	m_displayModeSelector->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	addObject(m_displayModeSelector);

	distFromTop = distFromTop + 120;

	// sound	
	m_soundCheckbox = new Checkbox();
	m_previousSoundOn = g_resourceManager->getConfiguration().isSoundOn;
	m_soundCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_soundCheckbox->setChecked(m_previousSoundOn);
	m_soundCheckbox->setText("Sound");
	m_soundCheckbox->setOnClick(std::bind(&OptionsScreen::checkSoundSlider, this));
	addObject(m_soundCheckbox);

	distFromTop = distFromTop + 80;

	m_volumeSoundSlider = new Slider(0, 100);
	std::string volumeText = g_textProvider->getText("SoundVolume");
	m_volumeSoundSlider->setTextRaw(volumeText);
	m_volumeSoundSlider->setUnit("%");
	m_volumeSoundSlider->setSliderPosition(g_resourceManager->getConfiguration().volumeSound);
	m_volumeSoundSlider->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	addObject(m_volumeSoundSlider);

	distFromTop = distFromTop + 100;

	m_volumeMusicSlider = new Slider(0, 100);
	m_previousMusicVolume = g_resourceManager->getConfiguration().volumeMusic;
	volumeText = g_textProvider->getText("MusicVolume");
	m_volumeMusicSlider->setTextRaw(volumeText);
	m_volumeMusicSlider->setUnit("%");
	m_volumeMusicSlider->setSliderPosition(m_previousMusicVolume);
	m_volumeMusicSlider->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	addObject(m_volumeMusicSlider);

	checkSoundSlider();

	distFromTop = 150.f;
	distFromLeft = WINDOW_WIDTH / 2.f + 150.f;

	// quickcast
	m_quickCastCheckbox = new Checkbox();
	m_quickCastCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_quickCastCheckbox->setChecked(g_resourceManager->getConfiguration().isQuickcast);
	m_quickCastCheckbox->setText("Quickcast");
	addObject(m_quickCastCheckbox);

	distFromTop = distFromTop + 50;

	// autotarget
	m_autotargetCheckbox = new Checkbox();
	m_autotargetCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_autotargetCheckbox->setChecked(g_resourceManager->getConfiguration().isAutotarget);
	m_autotargetCheckbox->setText("Autotarget");
	addObject(m_autotargetCheckbox);

	distFromTop = distFromTop + 50;

	// display hints
	m_displayHintsCheckbox = new Checkbox();
	m_displayHintsCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_displayHintsCheckbox->setChecked(g_resourceManager->getConfiguration().isDisplayHints);
	m_displayHintsCheckbox->setText("DisplayHints");
	addObject(m_displayHintsCheckbox);

	distFromTop = distFromTop + 50;

	// display quest markers
	m_displayQuestMarkersCheckbox = new Checkbox();
	m_displayQuestMarkersCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_displayQuestMarkersCheckbox->setChecked(g_resourceManager->getConfiguration().isDisplayQuestMarkers);
	m_displayQuestMarkersCheckbox->setText("DisplayQuestMarkers");
	addObject(m_displayQuestMarkersCheckbox);

	distFromTop = distFromTop + 50;

	// smoothing
	m_smoothingCheckbox = new Checkbox();
	m_smoothingCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_smoothingCheckbox->setChecked(g_resourceManager->getConfiguration().isSmoothing);
	m_smoothingCheckbox->setText("Smoothing");
	addObject(m_smoothingCheckbox);

	distFromTop = distFromTop + 50;

	// vsync
	m_vSyncCheckbox = new Checkbox();
	m_vSyncCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_vSyncCheckbox->setChecked(g_resourceManager->getConfiguration().isVSyncEnabled);
	m_vSyncCheckbox->setText("VSync");
	addObject(m_vSyncCheckbox);

	distFromTop = distFromTop + 50;

	// limit fps 
	m_limitFPSCheckbox = new Checkbox();
	m_limitFPSCheckbox->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	m_limitFPSCheckbox->setChecked(g_resourceManager->getConfiguration().isFPSLimited);
	m_limitFPSCheckbox->setOnClick(std::bind(&OptionsScreen::checkFPSSlider, this));
	m_limitFPSCheckbox->setText("LimitFPS");
	addObject(m_limitFPSCheckbox);

	distFromTop = distFromTop + 80;

	m_maxFPSSlider = new Slider(30, 100);
	m_maxFPSSlider->setText("MaxFPS");
	m_maxFPSSlider->setSliderPosition(g_resourceManager->getConfiguration().maxFPS);
	m_maxFPSSlider->setPosition(sf::Vector2f(distFromLeft, distFromTop));
	addObject(m_maxFPSSlider);

	checkFPSSlider();

	// back
	Button* button = new Button(sf::FloatRect(60, WINDOW_HEIGHT - 80, 200, 50), GUIOrnamentStyle::SMALL);
	button->setText("Back");
	button->setOnClick(std::bind(&OptionsScreen::onBack, this));
	addObject(button);

	// apply
	button = new Button(sf::FloatRect(WINDOW_WIDTH - 260, WINDOW_HEIGHT - 80, 200, 50), GUIOrnamentStyle::SMALL);
	button->setText("Apply");
	button->setOnClick(std::bind(&OptionsScreen::onApply, this));
	addObject(button);
}

void OptionsScreen::execOnExit() {
	// delete texts (buttons are deleted automatically by the screen)
	delete m_title;
}

void OptionsScreen::onBack() {
	m_onBackPressed = true;
	g_resourceManager->getConfiguration().volumeMusic = m_previousMusicVolume;
	g_resourceManager->getConfiguration().isSoundOn = m_previousSoundOn;
	g_resourceManager->notifyVolumeChanged();
	setNextScreen(new MenuScreen());
}

void OptionsScreen::onApply() {
	ConfigurationData& config = g_resourceManager->getConfiguration();
	DisplayMode mode = static_cast<DisplayMode>(m_displayModeSelector->getChosenOptionIndex() + 1);

	bool screenChanged = config.displayMode != mode;
	screenChanged = screenChanged || config.isVSyncEnabled != m_vSyncCheckbox->isChecked();
	screenChanged = screenChanged || config.isSmoothing != m_smoothingCheckbox->isChecked();
	screenChanged = screenChanged || config.isFPSLimited != m_limitFPSCheckbox->isChecked();
	screenChanged = screenChanged || config.maxFPS != m_maxFPSSlider->getSliderPosition();
	Language language = static_cast<Language>(m_languageSelector->getChosenOptionIndex() + 1);
	bool languageChanged = config.language != language;

	config.language = language;
	config.displayMode = mode;
	config.isSoundOn = m_soundCheckbox->isChecked();
	config.isQuickcast = m_quickCastCheckbox->isChecked();
	config.isDisplayHints = m_displayHintsCheckbox->isChecked();
	config.isDisplayQuestMarkers = m_displayQuestMarkersCheckbox->isChecked();
	config.isAutotarget = m_autotargetCheckbox->isChecked();
	config.isSmoothing = m_smoothingCheckbox->isChecked();
	config.isVSyncEnabled = m_vSyncCheckbox->isChecked();
	config.isFPSLimited = m_limitFPSCheckbox->isChecked();
	config.maxFPS = m_maxFPSSlider->getSliderPosition();
	config.volumeMusic = m_volumeMusicSlider->getSliderPosition();
	config.volumeSound = m_volumeSoundSlider->getSliderPosition();

	m_previousMusicVolume = config.volumeMusic;
	m_previousSoundOn = config.isSoundOn;

	ConfigurationWriter writer;
	writer.saveToFile(config);
	g_textProvider->reload();
	setTooltipText("ConfigurationSaved", COLOR_GOOD, true);
	if (screenChanged) {
		config.isWindowReload = true;
	}
	if (languageChanged) {
		setNextScreen(new OptionsScreen());
		m_screenManager->clearBackupScreen();
	}
	g_resourceManager->notifyVolumeChanged();
}

void OptionsScreen::checkSoundSlider() {
	m_volumeSoundSlider->setEnabled(m_soundCheckbox->isChecked());
	m_volumeMusicSlider->setEnabled(m_soundCheckbox->isChecked());
}

void OptionsScreen::checkFPSSlider() {
	m_maxFPSSlider->setEnabled(m_limitFPSCheckbox->isChecked());
}
