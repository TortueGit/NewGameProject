#pragma once

#include "global.h"

class WorldScreen;

// those can be triggered by triggers, dialogues, routines, npc behavior, etc.
enum class TriggerContentType {
	VOID,
	QuestStateChange,
	QuestConditionProgress,
	QuestDescriptionProgress,
	ConditionProgress,
	ReputationProgress,
	ItemChange,
	GoldChange,
	ItemEquip,
	Hint,
	MapEntry,
	LevelEntry,
	Cutscene,
	LearnSpell,
	LearnModifier,
	Weather,
	SetGuild,
	SetLevel,
	SetMap,
	SetForcedMap,
	AchievementUnlocked,
	AchievementNotify,
	AchievementNotifyCore,
	Music,
	Sound,
	Credits,
	MAX,
};

// holds a part of the trigger content.
// the trigger content type decides which of 
// the attributes are used.
struct TriggerContent final {
	TriggerContent() = default;
	explicit TriggerContent(TriggerContentType type_) : type(type_) {};
	TriggerContentType type = TriggerContentType::VOID;
	std::string s1 = "";
	std::string s2 = "";
	int i1 = 0;
	int i2 = 0;

	bool isValid() const;

	// executes the trigger on the given world screen
	static void executeTrigger(const TriggerContent& content, WorldScreen* screen);

	// creates trigger content for the given events. 	
	static TriggerContent startLevel(const std::string& levelID, int x, int y);
	static TriggerContent startMap(const std::string& mapID, int x, int y);
	static TriggerContent setLevel(const std::string& levelID, int x, int y);
	static TriggerContent setMap(const std::string& mapID, int x, int y);
	static TriggerContent setForcedMap(const std::string& mapID, int x, int y);
	static TriggerContent setMusic(const std::string& musicPath);
	static TriggerContent playSound(const std::string& soundPath);
};
