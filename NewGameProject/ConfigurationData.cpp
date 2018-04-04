#include "ConfigurationData.h"

void ConfigurationData::resetToDefault() {
#ifdef FRENCH_DEFAULT_LANGUAGE
	language = Language::Lang_FR;
#else
	language = Language::Lang_EN;
#endif
	isSoundOn = true;
	volumeSound = 100;
	volumeMusic = 100;
	isVSyncEnabled = true;
	isFPSLimited = false;
	maxFPS = 60;
	mainKeyMap = DEFAULT_KEYMAP;
	alternativeKeyMap = ALTERNATIVE_KEYMAP;
	displayMode = DisplayMode::Window;
	isQuickcast = true;
	isAutotarget = true;
	isSmoothing = true;
	isDisplayHints = true;
	isDisplayQuestMarkers = true;
	isMultithreading = true;
	isGodmode = false;
	isDebugRendering = false;
	isWindowReload = false;
	isDisplayTime = false;
	logLevel = LogLevel::Debug;
}

const std::map<Key, sf::Keyboard::Key> ConfigurationData::DEFAULT_KEYMAP =
{
	{ Key::Escape, sf::Keyboard::Escape },
	{ Key::Quickload, sf::Keyboard::F9 },
	{ Key::Quicksave, sf::Keyboard::F5 },
	{ Key::Confirm, sf::Keyboard::Return },
	{ Key::Debug, sf::Keyboard::F11 },
	{ Key::Market, sf::Keyboard::P },
	{ Key::Trade, sf::Keyboard::KeyCount },
	{ Key::Mercenaries, sf::Keyboard::KeyCount },
	{ Key::Politics, sf::Keyboard::KeyCount },
	{ Key::Structs, sf::Keyboard::KeyCount },
	{ Key::Resources, sf::Keyboard::KeyCount },
	{ Key::Agents, sf::Keyboard::KeyCount },
	{ Key::Search, sf::Keyboard::KeyCount },
	{ Key::Occult, sf::Keyboard::KeyCount },
};

const std::map<Key, sf::Keyboard::Key> ConfigurationData::ALTERNATIVE_KEYMAP =
{
	// sf::Keyboard::KeyCount means "not set"
	{ Key::Escape, sf::Keyboard::KeyCount },
	{ Key::Quickload, sf::Keyboard::KeyCount },
	{ Key::Quicksave, sf::Keyboard::KeyCount },
	{ Key::Confirm, sf::Keyboard::KeyCount },
	{ Key::Debug, sf::Keyboard::KeyCount },
	{ Key::Market, sf::Keyboard::KeyCount },
	{ Key::Trade, sf::Keyboard::KeyCount },
	{ Key::Mercenaries, sf::Keyboard::KeyCount },
	{ Key::Politics, sf::Keyboard::KeyCount },
	{ Key::Structs, sf::Keyboard::KeyCount },
	{ Key::Resources, sf::Keyboard::KeyCount },
	{ Key::Agents, sf::Keyboard::KeyCount },
	{ Key::Search, sf::Keyboard::KeyCount },
	{ Key::Occult, sf::Keyboard::KeyCount },
};
