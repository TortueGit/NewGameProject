#pragma once

#include "global.h"
#include "Logger.h"
#include "tinyxml2.h"
#include "WorldData.h"

class WorldReader {
public:
	WorldReader();
	virtual ~WorldReader() {};

protected:
	virtual void logError(const std::string& error) const;

	// reads properties name, tile size, map size, tileset, dimming starting @map node
	virtual bool readMapProperties(tinyxml2::XMLElement* map, WorldData& data) const;
	bool readTilesetPath(tinyxml2::XMLElement* _property, WorldData& data) const;
	bool readMusicPath(tinyxml2::XMLElement* _property, WorldData& data) const;
	bool readTileProperties(tinyxml2::XMLElement* map, WorldData& data);
	virtual bool readBackgroundLayers(tinyxml2::XMLElement* _property, WorldData& data) const;

	bool readBackgroundTileLayer(const std::string& layer, WorldData& data) const;
	bool readForegroundTileLayer(const std::string& layer, WorldData& data) const;
	bool readCollidableLayer(const std::string& layer, WorldData& data) const;
	bool readTriggers(tinyxml2::XMLElement* objects, WorldData& data) const;

	// check map bean for validity before loading the map
	bool checkData(WorldData& data) const;

	// update data to prepare it for the map
	void updateData(WorldData& data) const;

	// returns true if all in the layer properties given layer conditions are fulfilled for that layer
	bool layerConditionsFulfilled(tinyxml2::XMLElement* layer) const;

protected:
	typedef bool (WorldReader::*TriggerPropertyFunction)(const std::string&, TriggerData&) const;
	std::map<std::string, TriggerPropertyFunction> m_triggerProperties;

private:
	bool readForcedMapTrigger(const std::string& value, TriggerData& trigger) const;
	bool readSetMapTrigger(const std::string& value, TriggerData& trigger) const;
	bool readMusicTrigger(const std::string& value, TriggerData& trigger) const;
	bool readForcedTrigger(const std::string& value, TriggerData& trigger) const;
	bool readKeyguardedTrigger(const std::string& value, TriggerData& trigger) const;
	bool readPersistentTrigger(const std::string& value, TriggerData& trigger) const;

	bool readConditionsTrigger(const std::string& value, TriggerData& trigger, bool isNotConditions) const;
	bool readWorldEntryTrigger(const std::string& value, TriggerData& trigger, TriggerContentType type) const;
};