#include "TriggerContent.h"
#include "WorldScreen.h"

void TriggerContent::executeTrigger(const TriggerContent& content, WorldScreen* screen) {
	if (!content.isValid() || screen == nullptr) return;
	switch (content.type) {
	/*case TriggerContentType::ConditionProgress: {
		Condition cond;
		cond.type = content.s1;
		cond.name = content.s2;
		screen->notifyConditionAdded(cond);
		break;
	}	*/
		
	/*case TriggerContentType::SetMap:
		screen->getCharacterCore()->setMap(sf::Vector2f(static_cast<float>(content.i1), static_cast<float>(content.i2)), content.s1);
		break;
	case TriggerContentType::SetForcedMap:
		screen->getCharacterCore()->setForcedMap(sf::Vector2f(static_cast<float>(content.i1), static_cast<float>(content.i2)), content.s1);
		break;*/
	case TriggerContentType::Music:
		g_resourceManager->playMusic(content.s1);
		break;
	case TriggerContentType::Sound:
		g_resourceManager->playSound(content.s1);
		break;
	default:
		break;
	}
}

TriggerContent TriggerContent::startLevel(const std::string& levelID, int x, int y) {
	if (levelID.empty() || x <= 0 || y <= 0) {
		g_logger->logError("TriggerContent", "Level ID cannot be empty and the spawn position (x and y) must be > 0");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::LevelEntry);
	content.s1 = levelID;
	content.i1 = x;
	content.i2 = y;
	return content;
}

TriggerContent TriggerContent::startMap(const std::string& mapID, int x, int y) {
	if (mapID.empty() || x <= 0 || y <= 0) {
		g_logger->logError("TriggerContent", "Map ID cannot be empty and the spawn position (x and y) must be > 0");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::MapEntry);
	content.s1 = mapID;
	content.i1 = x;
	content.i2 = y;
	return content;
}

TriggerContent TriggerContent::setLevel(const std::string& levelID, int x, int y) {
	if (levelID.empty() || x <= 0 || y <= 0) {
		g_logger->logError("TriggerContent", "Level ID cannot be empty and the spawn position (x and y) must be > 0");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::SetLevel);
	content.s1 = levelID;
	content.i1 = x;
	content.i2 = y;
	return content;
}

TriggerContent TriggerContent::setMap(const std::string& mapID, int x, int y) {
	if (mapID.empty() || x <= 0 || y <= 0) {
		g_logger->logError("TriggerContent", "Map ID cannot be empty and the spawn position (x and y) must be > 0");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::SetMap);
	content.s1 = mapID;
	content.i1 = x;
	content.i2 = y;
	return content;
}

TriggerContent TriggerContent::setForcedMap(const std::string& mapID, int x, int y) {
	if (mapID.empty() || x <= 0 || y <= 0) {
		g_logger->logError("TriggerContent", "Map ID cannot be empty and the spawn position (x and y) must be > 0");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::SetForcedMap);
	content.s1 = mapID;
	content.i1 = x;
	content.i2 = y;
	return content;
}

TriggerContent TriggerContent::setMusic(const std::string& musicPath) {
	if (musicPath.empty()) {
		g_logger->logError("TriggerContent", "Music path cannot be empty");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::Music);
	content.s1 = musicPath;
	return content;
}

TriggerContent TriggerContent::playSound(const std::string& soundPath) {
	if (soundPath.empty()) {
		g_logger->logError("TriggerContent", "sound path cannot be empty");
		return TriggerContent();
	}
	TriggerContent content(TriggerContentType::Sound);
	content.s1 = soundPath;
	return content;
}

bool TriggerContent::isValid() const {
	return type > TriggerContentType::VOID && type < TriggerContentType::MAX;
}

