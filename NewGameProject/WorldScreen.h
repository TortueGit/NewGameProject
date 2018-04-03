#pragma once

#include "global.h"
#include "Screen.h"
#include "ResourceManager.h"
#include "WorldInterface.h"

// ancestor for level or map screen
class WorldScreen : public virtual Screen {
public:
	WorldScreen();
	virtual ~WorldScreen();

	// the part of the world that can be loaded safely async.
	virtual void loadAsync() = 0;
	// the rest, that cannot be loaded async
	virtual void loadSync() = 0;

	//void execUpdate(const sf::Time& frameTime) override;
	void execOnExit() override;
	void render(sf::RenderTarget& renderTarget) override;
	void renderAfterForeground(sf::RenderTarget& renderTarget);

	// and for the world
	//virtual const World* getWorld() const = 0;
	// and for the world data
	//virtual const WorldData* getWorldData() const = 0;
	// do everything thats needed before leaving the world screen and entering a new level / world. 
	// Return whether this is possible (it's not possible on a game over, for example)
	virtual bool exitWorld() = 0;
	// a return from the menu. reload a part of the configuration, restart music, etc.
	virtual void notifyBackFromMenu() = 0;

protected:
	// handle quicksave
	virtual void quicksave();
	// handle quickload 
	virtual void quickload();

protected:
	WorldInterface* m_interface = nullptr;

	// For lighting
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_sprite;
	sf::Shader m_lightLayerShader;
	sf::Shader m_foregroundLayerShader;
	static const std::string VERTEX_SHADER;	
	
private:
};