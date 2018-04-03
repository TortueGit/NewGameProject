#pragma once

#include "global.h"
#include "Screen.h"
#include "ErrorScreen.h"

class ScreenManager final {
public:
	ScreenManager(Screen* initialScreen);
	~ScreenManager();

	void update(const sf::Time& frameTime);
	void render(sf::RenderTarget& renderTarget) const;
	void setNextScreen(Screen* nextScreen, bool backupCurrentScreen);
	void resumeBackupScreen();
	void clearBackupScreen();
	void setErrorScreen();
	void requestQuit();

	bool isQuitRequested() const { return m_isQuitRequested; }

private:
	Screen* m_currentScreen = nullptr;
	Screen* m_nextScreen = nullptr;
	Screen* m_backUpScreen = nullptr;
	bool m_isErrorScreen = false;
	bool m_isQuitRequested = false;
	bool m_isBackupRequested = false;
	bool m_isResumeBackupScreen = false;
};