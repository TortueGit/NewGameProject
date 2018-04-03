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
	{ Key::Inventory, sf::Keyboard::I },
	{ Key::CharacterInfo, sf::Keyboard::C },
	{ Key::Map, sf::Keyboard::M },
	{ Key::Journal, sf::Keyboard::J },
	{ Key::Spellbook, sf::Keyboard::K },
	{ Key::Interact, sf::Keyboard::E },
	{ Key::Confirm, sf::Keyboard::Return },
	{ Key::Left, sf::Keyboard::A },
	{ Key::Right, sf::Keyboard::D },
	{ Key::Up, sf::Keyboard::W },
	{ Key::Down, sf::Keyboard::S },
	{ Key::Jump, sf::Keyboard::Space },
	{ Key::Chop, sf::Keyboard::F },
	{ Key::FirstSpell, sf::Keyboard::Num1 },
	{ Key::SecondSpell, sf::Keyboard::Num2 },
	{ Key::ThirdSpell, sf::Keyboard::Num3 },
	{ Key::FourthSpell, sf::Keyboard::Num4 },
	{ Key::FifthSpell, sf::Keyboard::Num5 },
	{ Key::QuickSlot1, sf::Keyboard::Num6 },
	{ Key::QuickSlot2, sf::Keyboard::Num7 },
	{ Key::ToggleTooltips, sf::Keyboard::LAlt },
	{ Key::SwitchTarget, sf::Keyboard::Tab },
	{ Key::Screenshot, sf::Keyboard::F10 },
	{ Key::Debug, sf::Keyboard::F11 },
	{ Key::BackToCheckpoint, sf::Keyboard::B },
	{ Key::ToggleAutotarget, sf::Keyboard::P },
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
	{ Key::Inventory, sf::Keyboard::KeyCount },
	{ Key::CharacterInfo, sf::Keyboard::KeyCount },
	{ Key::Map, sf::Keyboard::KeyCount },
	{ Key::Journal, sf::Keyboard::KeyCount },
	{ Key::Spellbook, sf::Keyboard::KeyCount },
	{ Key::Interact, sf::Keyboard::KeyCount },
	{ Key::Confirm, sf::Keyboard::KeyCount },
	{ Key::Left, sf::Keyboard::Left },
	{ Key::Right, sf::Keyboard::Right },
	{ Key::Up, sf::Keyboard::Up },
	{ Key::Down, sf::Keyboard::Down },
	{ Key::Jump, sf::Keyboard::KeyCount },
	{ Key::Chop, sf::Keyboard::KeyCount },
	{ Key::FirstSpell, sf::Keyboard::Numpad1 },
	{ Key::SecondSpell, sf::Keyboard::Numpad2 },
	{ Key::ThirdSpell, sf::Keyboard::Numpad3 },
	{ Key::FourthSpell, sf::Keyboard::Numpad4 },
	{ Key::FifthSpell, sf::Keyboard::Numpad5 },
	{ Key::QuickSlot1, sf::Keyboard::Numpad6 },
	{ Key::QuickSlot2, sf::Keyboard::Numpad7 },
	{ Key::ToggleTooltips, sf::Keyboard::KeyCount },
	{ Key::SwitchTarget, sf::Keyboard::KeyCount },
	{ Key::Screenshot, sf::Keyboard::KeyCount },
	{ Key::Debug, sf::Keyboard::KeyCount },
	{ Key::BackToCheckpoint, sf::Keyboard::KeyCount },
	{ Key::ToggleAutotarget, sf::Keyboard::KeyCount },
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
