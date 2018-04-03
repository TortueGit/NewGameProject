#pragma once

#include "global.h"
#include "InputController.h"
#include "ResourceManager.h"

#include "GUITabBar.h"

#include "Market.h"
//#include "GUI/Trade.h"
//#include "GUI/Mercenaries.h"
//#include "GUI/Politics.h"
//#include "GUI/Structs.h"
//#include "GUI/Resources.h"
//#include "GUI/Agents.h"
//#include "GUI/Search.h"
//#include "GUI/Occult.h"

class WorldScreen;

enum class GUIElement {
	VOID = -1,
	Avatar = 0,
	EndOfTurn,
	RecapTurn,
	Market,
	Trade,
	Mercenaries,
	Politics,
	Structs,
	Resources,
	Agents,
	Search,
	Occult
};

// abstract class for an interface in level or map
class WorldInterface {
public:
	WorldInterface(WorldScreen* screen);
	virtual ~WorldInterface();

	// reload the Market
	virtual void reloadMarket();
	//// reload the Trade
	//virtual void reloadTrade();
	//// reload the Mercenaries
	//virtual void reloadMercenaries();
	//// reload the Politics
	//virtual void reloadPolitics();
	//// reload the Structs
	//virtual void reloadStructs();
	//// reload the Resources
	//virtual void reloadResources();
	//// reload the Agents
	//virtual void reloadAgents();
	//// reload the Search
	//virtual void reloadSearch();
	//// reload the Occult
	//virtual void reloadOccult();

	virtual void render(sf::RenderTarget& target);
	virtual void renderAfterForeground(sf::RenderTarget& target);
	virtual void update(const sf::Time& frameTime);
	virtual void hideAll();
	// returns whether any gui overlay is open (market, trade, etc.)
	virtual bool isGuiOverlayVisible() const;

	virtual WorldScreen* getScreen() const;

protected:
	void loadGuiSidebar();

protected:
	WorldScreen* m_screen;

	GUITabBar* m_guiSidebar = nullptr;
	GUITabBar* m_mapSidebar = nullptr;
	
	/*Avatar* m_avatar = nullptr;
	EndOfTurn* m_endOfTurn = nullptr;
	RecapTurn* m_recapTurn = nullptr;*/
	Market* m_market = nullptr;
	/*Trade* m_trade = nullptr;
	Mercenaries* m_mercenaries = nullptr;
	Politics* m_politics = nullptr;
	Structs* m_structs = nullptr;
	Resources* m_resources = nullptr;
	Agents* m_agents = nullptr;
	Search* m_search = nullptr;
	Occult* m_occult = nullptr;*/
	
	template<typename G>
	void updateGuiElement(const sf::Time& frameTime, G* guiElement, GUIElement type);

	template<typename G>
	void showGuiElement(G* guiElement, GUIElement type);

	static Key getKeyFromGuiElement(GUIElement e);
};