#pragma once

#include "global.h"
#include "ResourceManager.h"
#include "Screen.h"
#include "SplashScreen.h"
#include "Button.h"
#include "BitmapText.h"
#include "YesOrNoForm.h"

class MainMapScreen : public virtual Screen {
public:
	MainMapScreen();
	virtual ~MainMapScreen();

	// the part of the world that can be loaded safely async.
	virtual void loadAsync() = 0;
	// the rest, that cannot be loaded async
	virtual void loadSync() = 0;

	void execOnEnter() override;
	void execUpdate(const sf::Time& frameTime) override;
	void execOnExit() override;
	void render(sf::RenderTarget& renderTarget) override;
	void renderAfterForeground(sf::RenderTarget& renderTarget);
	void updateProgressLog(const sf::Time& frameTime);

	// do everything thats needed before leaving the world screen and entering a new level / world. 
	// Return whether this is possible (it's not possible on a game over, for example)
	virtual bool exitWorld() = 0;
	// a return from the menu. reload a part of the configuration, restart music, etc.
	virtual void notifyBackFromMenu() = 0;
	
private:
	sf::Sprite m_screenSpriteBackground;
	sf::Sprite m_screenSpriteForeground;
	sf::Sprite m_logoSprite;

	void setAllButtonsEnabled(bool value) override;
	
	Button* m_avatarButton = nullptr;
	Button* m_endOfTurnButton = nullptr;
	Button* m_recapTurnButton = nullptr;

	Button* m_globalMarketButton = nullptr;
	Button* m_globalTradeButton = nullptr;
	Button* m_globalMercenariesButton = nullptr;
	Button* m_globalPoliticsButton = nullptr;

	Button* m_specialStructsButton = nullptr;
	Button* m_specialResourcesButton = nullptr;
	Button* m_specialAgentsButton = nullptr;
	Button* m_specialDevelopmentButton = nullptr;
	Button* m_specialOccultButton = nullptr;

	// agents for other buttons
	void onExit();
	void onAvatar();
	void onEndOfTurn();
	void onRecapTurn();
	void onMarket();
	void onTrade();
	void onMercenaries();
	void onPolitics();
	void onStructs();
	void onResources();
	void onAgents();
	void onDevelopment();
	void onOccult();
};